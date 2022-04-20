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

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event) && !game.GameOver())
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                Set set(5);
                vector<string> wordList;
                if (game.MenuTime()) {
                    game.ChooseWordLength(mousePosition);  
                    // Get wordLength here for guess generation
                    int len = game.WordLength();
                    wordList = readWordList(len);
                    set.length = len;
                    set.generate(wordList);
                    game.FinalizeWordLength(mousePosition, set.randomGuess()); //FIRST GUESS STRING GOES HERE
                }
                else {
                    vector<pair<char, int>> feedback;
                    // game.Play(mousePosition, "LAUREN", feedback); //SUBSEQUENT GUESSES GO HERE
                    game.GetFeedBack(mousePosition, feedback);
                    set.update(feedback);
                    game.SetNextGuess(set.randomGuess());
                }
            }
        }

        window.clear(sf::Color::White);

        game.Draw(window);

        window.display();
    }

    return 0;
}