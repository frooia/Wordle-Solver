#include "Texture.h"

unordered_map<string, sf::Texture> Texture::textures;

void Texture::LoadTexture(string fileName) {
	string path = "images/";
	path += fileName + ".png";

	textures[fileName].loadFromFile(path);
}

sf::Texture& Texture::GetTexture(string textureName) {
	if (textures.find(textureName) == textures.end()) {
		LoadTexture(textureName);
	}

	return textures[textureName];
}

void Texture::Clear() {
	textures.clear();
}