//This class was implemented by Professor Fox at UF and shared with his COP3503 students in fall 2021 semester

#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
using std::unordered_map;
using std::string;

class Texture
{
	static unordered_map<string, sf::Texture> textures;
	static void LoadTexture(string textureName);

public:
	static sf::Texture& GetTexture(string textureName);
	static void Clear();
};

