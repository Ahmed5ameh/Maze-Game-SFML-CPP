#pragma once
#include <SFML/Graphics.hpp>
class MazeGame
{
	int BackendMaze[23][23], playerX, playerY, treasureX, treasureY;
	sf::RectangleShape DrawCells[23][23];
	sf::Vector2i player, treasure;
	sf::Texture playerTex, wallTex, treasureTex;
	sf::Sprite playerSprite, treasureSprite;
	sf::Font fnt;
	sf::Text txtTop, txtBot;
	bool gameOver = 0;
public:
	void Start();
	void DisplayWin();
	void DisplayLose();
};

