#pragma once
#include <SFML/Graphics.hpp>
#include "Texture.h"

struct MenuButton
{
	sf::Sprite pressed;
	sf::Sprite unpressed;
	sf::Sprite number;
	bool selected;

	MenuButton(int x, int y, int num);
	void SetPressed();
	void SetUnpressed();
	sf::FloatRect GetBounds();
	void DrawMenuButton(sf::RenderWindow& window);

};

