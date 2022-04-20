#include "LetterSlots.h"
#include "Tile.h"
#include <iostream>

LetterSlots::LetterSlots() {
	slots.resize(6);	
	header.setTexture(Texture::GetTexture("header"));
	header.setPosition(400, 0);
}


void LetterSlots::SetSize(int wordLength) {
	//2D vector -- slots[row][column] --> row = guess #, column = word position
	//leftAligns by wordlength --> 5 = 415; 6 = 365; 7 = 320; 8 = 255
	slots.clear();
	slots.resize(6);
	
	//left Margin determined by wordLength to center images
	int leftAlign = 0;
	if (wordLength == 5)
		leftAlign = 415;
	else if (wordLength == 6)
		leftAlign = 365;
	else if (wordLength == 7)
		leftAlign = 320;
	else if (wordLength == 8)
		leftAlign = 255;
	
	for (int i = 0; i < slots.size(); i++) {
		for (int j = 0; j < wordLength; j++) {
			slots[i].push_back(Tile(leftAlign + 108 * j, 230 + 115 * i));
		}
	}
}

//changes letter value of the slots at appropriate guess number based on input string
void LetterSlots::SetGuess(string word, int guessNum) {
	
	if (slots[guessNum].size() == word.size()) {
		for (int i = 0; i < slots[guessNum].size(); i++) {
			slots[guessNum][i].SetLetter(word[i]);
		}
	}
	else {
		std::cout << "word not same size as slots ..." << slots[guessNum].size() << " vs. " << word.size() << endl;
	}
}

//returns the feedback from user input of current guess
vector<pair<char, int>> LetterSlots::Feedback(int guessNum, vector<pair<char,int>>& feedback){
	feedback.resize(0);
	for (int i = 0; i < slots[guessNum].size(); i++) {
		pair<char, int> pair(slots[guessNum][i].letter, slots[guessNum][i].color);
		feedback.push_back(pair);
	}

	return feedback;
}


void LetterSlots::DrawSlots(sf::RenderWindow& window) {
	window.draw(header);
	for (int i = 0; i < slots.size(); i++) {
		for (int j = 0; j < slots[i].size(); j++) {
			slots[i][j].DrawTile(window);
		}
	}
}
