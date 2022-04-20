#include "Tile.h"

Tile::Tile(float x, float y) {
	FillSpriteVector();
	SetTextures();
	SetPosition(x, y);
	SetScale();
	CreateMap();
	
	color = 0;			//start off empty bg
	letter = '*';		//w/ no letter
	
}

//create map spriteLog w/ key = char letter, value = corresponding sprite
void Tile::CreateMap() {
	char keyLetterLower = 'a';
	char keyLetterUpper = 'A';

	for (int i = 0; i < 26; i++) {
		spriteLog[keyLetterLower] = letterSprites.at(i);
		spriteLog[keyLetterUpper] = letterSprites.at(i);
		keyLetterLower++;
		keyLetterUpper++;
	}
}

//vector to iterate through all letter sprites
void Tile::FillSpriteVector() {
	
	sf::Sprite A;
	sf::Sprite B;
	sf::Sprite C;
	sf::Sprite D;
	sf::Sprite E;
	sf::Sprite F;
	sf::Sprite G;
	sf::Sprite H;
	sf::Sprite I;
	sf::Sprite J;
	sf::Sprite K;
	sf::Sprite L;
	sf::Sprite M;
	sf::Sprite N;
	sf::Sprite O;
	sf::Sprite P;
	sf::Sprite Q;
	sf::Sprite R;
	sf::Sprite S;
	sf::Sprite T;
	sf::Sprite U;
	sf::Sprite V;
	sf::Sprite W;
	sf::Sprite X;
	sf::Sprite Y;
	sf::Sprite Z;


	letterSprites.push_back(A);
	letterSprites.push_back(B);
	letterSprites.push_back(C);
	letterSprites.push_back(D);
	letterSprites.push_back(E);
	letterSprites.push_back(F);
	letterSprites.push_back(G);
	letterSprites.push_back(H);
	letterSprites.push_back(I);
	letterSprites.push_back(J);
	letterSprites.push_back(K);
	letterSprites.push_back(L);
	letterSprites.push_back(M);
	letterSprites.push_back(N);
	letterSprites.push_back(O);
	letterSprites.push_back(P);
	letterSprites.push_back(Q);
	letterSprites.push_back(R);
	letterSprites.push_back(S);
	letterSprites.push_back(T);
	letterSprites.push_back(U);
	letterSprites.push_back(V);
	letterSprites.push_back(W);
	letterSprites.push_back(X);
	letterSprites.push_back(Y);
	letterSprites.push_back(Z);

}

//load all sprite's textures
void Tile::SetTextures() {
	empty.setTexture(Texture::GetTexture("empty"));
	green.setTexture(Texture::GetTexture("green"));
	yellow.setTexture(Texture::GetTexture("yellow"));
	gray.setTexture(Texture::GetTexture("gray"));
	
	

	char textureLetter = 'a';

	for (int i = 0; i < letterSprites.size(); i++) {
		string s(1, textureLetter);
		letterSprites.at(i).setTexture(Texture::GetTexture(s));
		textureLetter++;
	}
}

//set all sprites to same scale
void Tile::SetScale() {
	sf::Vector2<float> scale(0.2, 0.2);

	empty.setScale(scale);
	green.setScale(scale);
	yellow.setScale(scale);
	gray.setScale(scale);
	
	for (int i = 0; i < letterSprites.size(); i++) {
		letterSprites.at(i).setScale(scale);
	}
	
}

//set all sprites to same position
void Tile::SetPosition(float x, float y) {
	empty.setPosition(x, y);
	green.setPosition(x, y);
	yellow.setPosition(x, y);
	gray.setPosition(x, y);
	
	for (int i = 0; i < letterSprites.size(); i++) {
		letterSprites.at(i).setPosition(x,y);
	}
} 

//change color int from 0 - 1 - 2 - 3 - 1 - 2 - 3 - etc
void Tile::SwitchColor() {
	color++;
	if (color > 3)
		color = 1;
} 

void Tile::SetLetter(char _letter) {
	letter = _letter;
} //changes letter based on char a-z

sf::FloatRect Tile::GetBounds() {
	return empty.getGlobalBounds();
}

//draw bg based on color int, draw letter based on letter char, letter color based on bg color int
void Tile::DrawTile(sf::RenderWindow& window) {
	//bg switch case
	switch (color) {
	case 0:
		window.draw(empty);
		break;
	case 1:
		window.draw(green);
		break;
	case 2:
		window.draw(yellow);
		break;
	case 3:
		window.draw(gray);
		break;
	}

	//draw appropriate sprite based on letter and bg color
	if (color == 0)
		spriteLog[letter].setColor(sf::Color::Black);
	else
		spriteLog[letter].setColor(sf::Color::White);

	window.draw(spriteLog[letter]);

} 

