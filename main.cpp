#include <SFML/Graphics.hpp>
#include "Texture.h"
#include "Tile.h"
#include "LetterSlots.h"
#include "EnterButton.h"
#include "Buttons.h"
#include "SelectionMenu.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1500, 1000), "SFML works!");

    int currGuess = 0;
    bool gameOver = false;
    bool menuTime = true;
    LetterSlots squares;    
    Buttons buttons;
    SelectionMenu menu;
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event) && !gameOver)
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

                if (menuTime) {
                    for (int i = 0; i < 4; i++) {
                        if (menu.menuButtons[i].GetBounds().contains(mousePosition)) {
                            menu.SetPressed(i);
                        }
                    }

                    if (menu.enter.GetBounds().contains(mousePosition)) {
                        menu.enter.PressButton();
                        
                        squares.SetSize(menu.wordLength);
                        squares.SetGuess("LAUREN", currGuess);  //FIRST GUESS STRING HERE
                        buttons.SetPositions(menu.wordLength);
                        menuTime = false;
                    }
                }
                else {
                    for (int j = 0; j < squares.slots[currGuess].size(); j++) {
                        if (squares.slots[currGuess][j].GetBounds().contains(mousePosition)) {
                            squares.slots[currGuess][j].SwitchColor();
                        }
                    }

                    if (menu.backButton.getGlobalBounds().contains(mousePosition)) {
                        menuTime = true;
                        menu.enter.UnpressButton();
                        currGuess = 0;
                    }

                    if (buttons.buttons[currGuess].GetBounds().contains(mousePosition)) {
                        bool feedbackChosen = true;
                        for (int j = 0; j < squares.slots[currGuess].size(); j++) {
                            if (squares.slots[currGuess][j].color == 0) {
                                feedbackChosen = false;
                            }
                        }
                        if (feedbackChosen) {
                            buttons.buttons[currGuess].PressButton();
                            squares.Feedback(currGuess++); //RETURNS FEEDBACK
                            if (currGuess < 6)
                                squares.SetGuess("lauren", currGuess);  //SUBSEQUENT GUESSES
                            else
                                gameOver = true;
                        }

                    }
                }

            }
        
        }

        window.clear(sf::Color::White);
        
        if (!(menu.SelectionFinalized())) {
            menu.DrawMenu(window);
        }

        else {
            squares.DrawSlots(window);
            buttons.DrawButtons(window);
            menu.DrawBack(window);
        }

        window.display();
    }

    return 0;
}