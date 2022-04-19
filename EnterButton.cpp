#include "EnterButton.h"
#include "Texture.h"

EnterButton::EnterButton() {
	CreateSprites();
	buttonPressed = false;
}

void EnterButton::CreateSprites() {
	pressed.setTexture(Texture::GetTexture("enterPressed"));
	unpressed.setTexture(Texture::GetTexture("enterUnpressed"));

	pressed.setScale(0.2, 0.2);
	unpressed.setScale(0.2, 0.2);
}

//x value for each wordlength --> 5 = 1060; 6 = 1135; 7 = 1210; 8 = 1250
void EnterButton::SetPosition(float x, float y) {
	pressed.setPosition(x, y);
	unpressed.setPosition(x, y);
}

void EnterButton::PressButton() {
	buttonPressed = true;
}

sf::FloatRect EnterButton::GetBounds() {
	return pressed.getGlobalBounds();
}

void EnterButton::DrawButton(sf::RenderWindow& window) {
	if (buttonPressed)
		window.draw(pressed);
	else
		window.draw(unpressed);
}