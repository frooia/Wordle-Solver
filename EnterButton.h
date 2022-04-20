#pragma once
#include <SFML/Graphics.hpp>

struct EnterButton
{
	sf::Sprite unpressed;
	sf::Sprite pressed;

	bool buttonPressed;

	EnterButton();
	void CreateSprites();
	void SetPosition(float x, float y);
	void PressButton();
	void UnpressButton();
	sf::FloatRect GetBounds();
	void DrawButton(sf::RenderWindow& window);

};

