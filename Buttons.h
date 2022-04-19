#pragma once
#include "EnterButton.h"
using namespace std;

struct Buttons
{
	vector<EnterButton> buttons;

	Buttons();
	void SetPositions(int wordLength);
	void DrawButtons(sf::RenderWindow& window);

};

