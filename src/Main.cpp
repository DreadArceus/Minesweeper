#include <iostream>
#include "game.hpp"
#include <catch2/catch.hpp>
using namespace std;

int main()
{
	//making sprites from the source file
	sf::Texture tex;
	tex.loadFromFile("content/tiles.jpg");
	vector<sf::Sprite> sp;
	int x = tex.getSize().x/12;
	int y = tex.getSize().y;
	sp.resize(12);
	for(int i = 0; i < 12; i++)
	{
		sp[i].setTexture(tex);
		sp[i].setTextureRect(sf::IntRect(i*x, 0, x, y));
	}

	//Setting the difficulty/size
	cout << "Welcome to Minesweeper...\n" << "Enter the grid size: ";
	int n = 0;
	cin >> n;
	while(n <= 3)
	{
		cout << "\nPlease input a size greater than 3: ";
		cin >> n;
	}

	ground g(n, sp);
	g.play();
}