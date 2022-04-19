#pragma once
#include <vector>
#include "Texture.h"
#include "Tile.h"
using namespace std;

struct LetterSlots
{

	sf::Sprite header;
	vector<vector<Tile>> slots; //diff sizes based on word length, (rows - CONST 6, columns - wordlength )

	LetterSlots();
	void SetSize(int wordLength);//resize slots vector, fill with tiles, 
	void SetGuess(string word, int guessNum);
	vector<pair<char, int>> Feedback(int guessNum);
	void DrawSlots(sf::RenderWindow& window);

};


