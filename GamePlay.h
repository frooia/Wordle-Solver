#pragma once
#include <SFML/Graphics.hpp>
#include "LetterSlots.h"
#include "Buttons.h"
#include "SelectionMenu.h"

class GamePlay
{
	
	int currGuess;
	bool gameOver;
	bool menuTime;
	LetterSlots squares;
	Buttons buttons;
	SelectionMenu menu;

public:
	GamePlay();
	bool GameOver();
	bool MenuTime();
	void ChooseWordLength(sf::Vector2f mousePosition);
	void Play(sf::Vector2f mousePosition);
	void Draw(sf::RenderWindow& window);

};

