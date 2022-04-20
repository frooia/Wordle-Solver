#include "SelectionMenu.h"

SelectionMenu::SelectionMenu() {	
	wordLength = 0;
	instruction.setTexture(Texture::GetTexture("selectionInstruction"));
	instruction.setPosition(400, 250);
	enter.SetPosition(850, 500);
	backButton.setTexture(Texture::GetTexture("back-button"));
	backButton.setPosition(10, 10);
	backButton.setScale(0.15, 0.15);
	
	for (int i = 5; i < 9; i++) {
		menuButtons.push_back(MenuButton(650, 80 * i, i)); //450 + 200 * i
	}

}

bool SelectionMenu::SelectionMade() {
	bool selected = false;
	for (int i = 0; i < menuButtons.size(); i++) {
		if (menuButtons[i].selected) {
			selected = true;
		}
	}
	return selected;
}

bool SelectionMenu::SelectionFinalized() {
	if (SelectionMade() && enter.buttonPressed)
		return true;
	else
		return false;
}

void SelectionMenu::SetPressed(int index) {
	wordLength = index + 5;

	for (int i = 0; i < 4; i++) {
		if (i == index)
			menuButtons[i].selected = true;
		else
			menuButtons[i].selected = false;
	}
}

void SelectionMenu::DrawMenu(sf::RenderWindow& window) {
	enter.DrawButton(window);
	window.draw(instruction);
	
	for (int i = 0; i < menuButtons.size(); i++) {
		menuButtons[i].DrawMenuButton(window);
	}
}

void SelectionMenu::DrawBack(sf::RenderWindow& window) {
	window.draw(backButton);
}

