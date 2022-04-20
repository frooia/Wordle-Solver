#pragma once
#include <SFML/Graphics.hpp>
#include "Texture.h"
#include <vector>
#include <unordered_map>
using namespace std;


struct Tile {

	unordered_map<char, sf::Sprite> spriteLog;

	int color; //0 - empty, 1 - green, 2 - yellow, 3 - gray
	char letter; //a-z represent a-z, * represents no letter
	
	Tile(float x, float y);
	
	void SetPosition(float x, float y); //set all sprites to same position
	void SetScale();
	void SwitchColor(); //change color int from 0 - 1 - 2 - 3
	void SetLetter(char _letter); //changes letter based on char a-z, letter color based on bg color int
	sf::FloatRect GetBounds();
	void DrawTile(sf::RenderWindow& window); //draw bg based on color int, draw letter based on letter char

private:
	void CreateMap();
	void FillSpriteVector();
	void SetTextures();

	sf::Sprite empty;
	sf::Sprite gray;
	sf::Sprite yellow;
	sf::Sprite green;
	vector<sf::Sprite> letterSprites;

};