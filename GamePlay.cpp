#include "GamePlay.h"

GamePlay::GamePlay() {

	currGuess = 0;
	gameOver = false;
	menuTime = true;
	LetterSlots squares;
	Buttons buttons;
	SelectionMenu menu;
}

bool GamePlay::GameOver() {
	return gameOver;
}

bool GamePlay::MenuTime() {
	return menuTime;
}

int GamePlay::WordLength() {
	return menu.wordLength;
}

void GamePlay::ChooseWordLength(sf::Vector2f mousePosition) {
	//checks if any wordlength button has been clicked, selects if yes
	for (int i = 0; i < 4; i++) {
		if (menu.menuButtons[i].GetBounds().contains(mousePosition)) {
			menu.SetPressed(i);
		}
	}
}

void GamePlay::FinalizeWordLength(sf::Vector2f mousePosition, string guess) {
	//checks if enter has been pressed, presses button, sets up next screen and first guess
	if (menu.enter.GetBounds().contains(mousePosition)) {
		menu.enter.PressButton();

		squares.SetSize(menu.wordLength);
		squares.SetGuess(guess, currGuess);  
		buttons.SetPositions(menu.wordLength);
		menuTime = false;
	}
}

void GamePlay::Play(sf::Vector2f mousePosition, string guess, vector<pair<char,int>>& feedback) {
	//switches color of clicked slot
	for (int j = 0; j < squares.slots[currGuess].size(); j++) {
		if (squares.slots[currGuess][j].GetBounds().contains(mousePosition)) {
			squares.slots[currGuess][j].SwitchColor();
		}
	}

	//returns to word length selection menu
	if (menu.backButton.getGlobalBounds().contains(mousePosition)) {
		menuTime = true;
		menu.enter.UnpressButton();
		currGuess = 0;
	}

	
	if (buttons.buttons[currGuess].GetBounds().contains(mousePosition)) {
		//checks if all slots in current guess have received feedback
		bool feedbackChosen = true;
		for (int j = 0; j < squares.slots[currGuess].size(); j++) {
			if (squares.slots[currGuess][j].color == 0) {
				feedbackChosen = false;
			}
		}

		//if all have feedback, returns it and sets next guess
		if (feedbackChosen) {
			buttons.buttons[currGuess].PressButton();
			squares.Feedback(currGuess++, feedback); //RETURNS FEEDBACK
			if (currGuess < 6)
				squares.SetGuess(guess, currGuess);  
			else
				gameOver = true;
		}

	}
}

void GamePlay::Draw(sf::RenderWindow& window) {
	if (!(menu.SelectionFinalized())) {
		menu.DrawMenu(window);
	}

	else {
		squares.DrawSlots(window);
		buttons.DrawButtons(window);
		menu.DrawBack(window);
	}
}