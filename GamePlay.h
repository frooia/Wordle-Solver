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
	

public:
	SelectionMenu menu;
	GamePlay();
	bool GameOver();
	bool MenuTime();
	void ChooseWordLength(sf::Vector2f mousePosition);
	void FinalizeWordLength(sf::Vector2f mousePosition, string guess);
	void GetFeedBack(sf::Vector2f mousePosition, vector<pair<char, int>>& feedback);
	void SetNextGuess(string guess);
	void Draw(sf::RenderWindow& window);
	int WordLength();

};

