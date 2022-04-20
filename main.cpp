#include <SFML/Graphics.hpp>
#include "Texture.h"
#include "Tile.h"
#include "LetterSlots.h"
#include "EnterButton.h"
#include "Buttons.h"
#include "SelectionMenu.h"
#include "GamePlay.h"

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

                if (game.MenuTime()) {
                    game.ChooseWordLength(mousePosition);  
                    //can get wordlength here for guess generation 
                    //int len = game.WordLength()
                    game.FinalizeWordLength(mousePosition, "LAUREN"); //FIRST GUESS STRING GOES HERE
                }
                else {
                    vector<pair<char, int>> feedback;
                    game.Play(mousePosition, "LAUREN", feedback); //SUBSEQUENT GUESSES GO HERE
                }
            }
        }

        window.clear(sf::Color::White);

        game.Draw(window);

        window.display();
    }

    return 0;
}