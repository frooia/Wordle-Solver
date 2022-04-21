#include <SFML/Graphics.hpp>
#include "Texture.h"
#include "Tile.h"
#include "LetterSlots.h"
#include "EnterButton.h"
#include "Buttons.h"
#include "SelectionMenu.h"
#include "GamePlay.h"
#include "Set.cpp"
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

int main()
{
    sf::RenderWindow window(sf::VideoMode(1500, 1000), "WORDLE SOLVER");
    GamePlay game = GamePlay();
    vector<string> wordList;
    Set set(5);
    vector<pair<char, int>> feedback;
    bool USE_SET = true;

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
                            }
                            game.SetNextGuess(nextGuess);
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