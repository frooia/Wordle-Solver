#include "MenuButton.h"



MenuButton::MenuButton(int x, int y, int num) {
	pressed.setTexture(Texture::GetTexture("pressed"));
	unpressed.setTexture(Texture::GetTexture("unpressed"));
	number.setTexture(Texture::GetTexture(std::to_string(num)));

	pressed.setScale(0.15, 0.15);
	unpressed.setScale(0.15, 0.15);
	number.setScale(0.15, 0.15);

	pressed.setPosition(x, y);
	unpressed.setPosition(x, y);
	number.setPosition(x + 50, y);



	selected = false;
}

void MenuButton::SetPressed(){
	selected = true;
}

void MenuButton::SetUnpressed() {
	selected = false;
}

sf::FloatRect MenuButton::GetBounds() {
	return pressed.getGlobalBounds();
}

void MenuButton::DrawMenuButton(sf::RenderWindow& window) {
	if (selected)
		window.draw(pressed);
	else
		window.draw(unpressed);
	window.draw(number);
}