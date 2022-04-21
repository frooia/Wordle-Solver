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

bool GamePlay::MouseOnMenu(sf::Vector2f mousePosition) {
    for (int i = 0; i < 4; i++) {
        if (menu.menuButtons[i].GetBounds().contains(mousePosition)) {
            return true;
        }
    }
    return false;
}
bool GamePlay::MouseOnEnter(sf::Vector2f mousePosition) {
    return menu.enter.GetBounds().contains(mousePosition);
}

void GamePlay::FinalizeWordLength(sf::Vector2f mousePosition) {
	//checks if enter has been pressed, presses button, sets up next screen and first guess
		menu.enter.PressButton();
		squares.SetSize(menu.wordLength);
		buttons.SetPositions(menu.wordLength);
		menuTime = false;

}

void GamePlay::SetFirstGuess(const string& guess) {
    squares.SetGuess(guess, currGuess);
}

void GamePlay::SwitchColor(sf::Vector2f mousePosition) {
    //switches color of clicked slot
    for (int j = 0; j < squares.slots[currGuess].size(); j++) {
        if (squares.slots[currGuess][j].GetBounds().contains(mousePosition)) {
            squares.slots[currGuess][j].SwitchColor();
        }
    }
}

bool GamePlay::MouseOnBack(sf::Vector2f mousePosition) {
    return menu.backButton.getGlobalBounds().contains(mousePosition);
}

void GamePlay::ReturnToMenu(sf::Vector2f mousePosition) {
    //returns to word length selection menu
    menuTime = true;
    menu.enter.UnpressButton();
    currGuess = 0;
}

bool GamePlay::MouseOnCurrentEnter(sf::Vector2f mousePosition) {
    return buttons.buttons[currGuess].GetBounds().contains(mousePosition);
}

bool GamePlay::GetFeedBack(sf::Vector2f mousePosition, vector<pair<char, int>>& feedback) {
    //checks if all slots in current guess have received feedback
    bool feedbackChosen = true;
    for (int j = 0; j < squares.slots[currGuess].size(); j++) {
        if (squares.slots[currGuess][j].color == 0) {
            feedbackChosen = false;
        }
    }

    if (feedbackChosen) {
        buttons.buttons[currGuess].PressButton();
        squares.Feedback(currGuess++, feedback); //RETURNS FEEDBACK
    }
    return feedbackChosen;
}

void GamePlay::SetNextGuess(const string& guess, vector<pair<char,int>>& feedback) {
	//sets next guess
	if (currGuess < 6 && !AllGreen(feedback)) // TODO: check if it's not all green
		squares.SetGuess(guess, currGuess);  
	else
		gameOver = true;
}

bool GamePlay::AllGreen(vector<pair<char,int>>& feedback) {
    bool allGreen = true;
    for (auto & i : feedback) {
        if (i.second != 1)
            allGreen = false;
    }

    return allGreen;
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

void GamePlay::DrawWin(sf::RenderWindow& window) {
    window.draw(winScreen);
}

void GamePlay::DrawLose(sf::RenderWindow& window) {
    window.draw(gameOverScreen);
}