#include "Buttons.h"

Buttons::Buttons() {
	buttons.resize(0);
}

void Buttons::SetPositions(int wordLength) {
	buttons.resize(0);
	int x = 500;
	//adjust location based on word length being showed
	if (wordLength == 5)
		x = 1060;
	else if (wordLength == 6)
		x = 1135;
	else if (wordLength == 7)
		x = 1210;
	else if (wordLength == 8)
		x = 1250;
	
	for (int i = 0; i < 6; i++) {
		buttons.push_back(EnterButton());
		buttons[i].SetPosition(x, 215 + 115 * i);
	}
}


void Buttons::DrawButtons(sf::RenderWindow& window) {
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i].DrawButton(window);
	}
}