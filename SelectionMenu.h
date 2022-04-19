#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "MenuButton.h"
#include "EnterButton.h"
using namespace std;


struct SelectionMenu
{

	vector<MenuButton> menuButtons;
	sf::Sprite instruction;
	EnterButton enter;
	int wordLength;
	

	SelectionMenu();
	bool SelectionMade();
	bool SelectionFinalized();
	void SetPressed(int index);
	void DrawMenu(sf::RenderWindow& window);
	

};

