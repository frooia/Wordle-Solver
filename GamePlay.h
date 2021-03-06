#pragma once
#include <SFML/Graphics.hpp>
#include "LetterSlots.h"
#include "Buttons.h"
#include "SelectionMenu.h"

class GamePlay
{
	
	sf::Sprite gameOverScreen;
	sf::Sprite winScreen;
	bool gameOver;
	bool menuTime;
	LetterSlots squares;
	Buttons buttons;
	

public:
    int currGuess;
	SelectionMenu menu;
	GamePlay();
	bool GameOver();
	bool MenuTime();
	void ChooseWordLength(sf::Vector2f mousePosition);
    bool MouseOnMenu(sf::Vector2f mousePosition);
    bool MouseOnEnter(sf::Vector2f mousePosition);
    void SetFirstGuess(const string& guess);
	void FinalizeWordLength(sf::Vector2f mousePosition);
    void SwitchColor(sf::Vector2f mousePosition);
    bool MouseOnBack(sf::Vector2f mousePosition);
    void ReturnToMenu(sf::Vector2f mousePosition);
    bool MouseOnCurrentEnter(sf::Vector2f mousePosition);
	bool GetFeedBack(sf::Vector2f mousePosition, vector<pair<char, int>>& feedback);
	void SetNextGuess(const string& guess, vector<pair<char,int>>& feedback);
    bool AllGreen(vector<pair<char,int>>& feedback);
	void Draw(sf::RenderWindow& window);
	int WordLength();
	void DrawWin(sf::RenderWindow& window);
	void DrawLose(sf::RenderWindow& window);

};

