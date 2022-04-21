#include <SFML/Graphics.hpp>
#include "Texture.h"
#include "Tile.h"
#include "LetterSlots.h"
#include "EnterButton.h"
#include "Buttons.h"
#include "SelectionMenu.h"
#include "GamePlay.h"
#include "Set.cpp"
#include "Trie.h"
#include "WordleGenerator.cpp"
#include <fstream>

vector<string> readWordList(int wordLength) {
    ifstream file("word lists/" + to_string(wordLength) + "-letter-words.txt");
    vector<string> ans;
    while (file) {
        string word;
        file >> word;
        ans.push_back(word);
    }
    return ans;
}

vector<pair<char, int>> feedbackFromAns(string guess, string ans) {
    vector<pair<char, int>> feedback;
    feedback.reserve(guess.length());
    for (char & c : guess) {
        feedback.emplace_back(c, 0);
    }
    // Mark all the greens first
    for (int i = 0; i < guess.length(); i++) {
        if (guess[i] == ans[i])
            feedback[i].second = 1;
    }
    // Mark yellows
    for (int i = 0; i < guess.length(); i++) {
        if (guess[i] != ans[i]) {
            for (int j = 0; j < guess.length(); j++) {
                if (i != j && guess[i] == ans[j]) {
                    feedback[i].second = 2;
                }
            }
        }
    }
    // Mark everything else gray
    for (int i = 0; i < guess.length(); i++) {
        if (feedback[i].second == 0)
            feedback[i].second = 3;
    }
    return feedback;
}

void evaluate(int numSims, int length, const vector<string>& wordList) {
    Set set(length);
    set.generate(wordList);
    int setSumGuessesNeeded = 0, trieSumGuessesNeeded = 0;
    Trie trie(length);
    WordleGenerator wg(length);
    while (numSims-->0) {
        string answer = wg.randomWord(wordList);
        int guessCount = 0;
        string guess;
        // Use set to solve
        while (guessCount < 6) {
            guess = set.randomGuess();
            if (guess == answer)
                break;
            vector<pair<char, int>> feedback = feedbackFromAns(guess, answer);
            set.update(feedback);
            guessCount++;
        }
        setSumGuessesNeeded += guessCount;

        // Use trie to solve
        guessCount = 0;
        guess = trie.guessNoFeedback();
        while (guessCount < 6) {
            if (guess == answer)
                break;
            vector<pair<char, int>> feedback = feedbackFromAns(guess, answer);
            guess = trie.generateGuess(feedback);
            guessCount++;
        }
        trieSumGuessesNeeded += guessCount;
    }
    cout << "Average number of guesses required using Set: " << (double)setSumGuessesNeeded / (double)numSims << endl;
    cout << "Average number of guesses required using Trie: " << (double)trieSumGuessesNeeded / (double)numSims << endl;
}

int main()
{
    // UNCOMMENT THIS OUT AND COMMENT OUT EVERYTHING ELSE TO COMPARE SET VS TRIE
    // evaluate(1000, 5, readWordList(5));

    sf::RenderWindow window(sf::VideoMode(1500, 1000), "WORDLE SOLVER");
    GamePlay game = GamePlay();
    vector<string> wordList;
    Set set(5);
    Trie trie(5);
    vector<pair<char, int>> feedback;
    bool USE_SET = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event) && !game.GameOver())
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                if (game.MenuTime()) {
                    if (game.MouseOnMenu(mousePosition)) {
                        game.ChooseWordLength(mousePosition);
                        // Get wordLength here for guess generation
                        int len = game.WordLength();
                        game.FinalizeWordLength(mousePosition);

                        // Generate and display first guess
                        wordList = readWordList(len);
                        string guess;
                        if (USE_SET) {
                            set.length = len;
                            set.generate(wordList);
                            guess = set.randomGuess();
                        } else {
                            // do trie stuff here
                            trie = Trie(len);
                            guess = trie.guessNoFeedback();
                        }
                        game.SetFirstGuess(guess); //FIRST GUESS STRING GOES HERE

                    }

                }
                else {
                    // game.Play(mousePosition, "LAUREN", feedback); //SUBSEQUENT GUESSES GO HERE
                    game.SwitchColor(mousePosition);
                    if (game.MouseOnBack(mousePosition)) {
                        game.ReturnToMenu(mousePosition);
                    }
                    else if (game.MouseOnCurrentEnter(mousePosition)) {
                        if (game.GetFeedBack(mousePosition, feedback)) {
                            string nextGuess;
                            if (USE_SET) {
                                set.update(feedback);
                                nextGuess = set.randomGuess();
                            } else {
                                // do trie stuff here
                                nextGuess = trie.generateGuess(feedback);
                            }
                            game.SetNextGuess(nextGuess);
                            feedback.resize(0);
                        }
                    }
                }
            }
        }

        window.clear(sf::Color::White);

        game.Draw(window);

        window.display();
    }

    return 0;
}