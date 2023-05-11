#include <iostream>
#include "MazeGame.h"
using namespace std;

void MazeGame::DisplayWin() {
	txtTop.setFont(fnt);
	txtTop.setString("GG");
	txtTop.setCharacterSize(500);
	txtTop.setFillColor(sf::Color::Red);
	txtTop.setPosition(150.f, 0.f);
	txtBot.setFont(fnt);
	txtBot.setString("EZ");
	txtBot.setCharacterSize(500);
	txtBot.setFillColor(sf::Color::Red);
	txtBot.setPosition(225.f, 400.f);
	gameOver = 1;
}
void MazeGame::DisplayLose() {
	txtTop.setFont(fnt);
	txtTop.setString("HARD");
	txtTop.setCharacterSize(375);
	txtTop.setFillColor(sf::Color::Red);
	txtTop.setPosition(7.f, 150.f);
	txtBot.setFont(fnt);
	txtBot.setString("LUCK");
	txtBot.setCharacterSize(375);
	txtBot.setFillColor(sf::Color::Red);
	txtBot.setPosition(55.f, 430.f);
	gameOver = 1;
}
void MazeGame::Start() {
	srand(time(NULL));
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(1080, 1080), "THE MAZE GAME", sf::Style::None, settings);
	playerX = rand() % 20 + 2;
	playerY = rand() % 20 + 2;
	player = sf::Vector2i(playerX, playerY);
	playerTex.loadFromFile("player.png");	//Load player texture with a 47x47 rectangle starting from (0,0)
	playerSprite.setTexture(playerTex);
	playerSprite.setPosition(player.x * 47.f, player.y * 47.f);
	treasureX = rand() % 21 + 1;
	treasureY = rand() % 21 + 1;
	treasure = sf::Vector2i(treasureX, treasureY);
	treasureTex.loadFromFile("treasure.png");
	treasureSprite.setTexture(treasureTex);
	treasureSprite.setPosition(treasureX * 47.f, treasureY * 47.f);
	wallTex.loadFromFile("wall.jpg");

	//Random Numbers Generator
	for (int i = 0; i < 23; i++) {
		for (int j = 0; j < 23; j++) {
			BackendMaze[i][j] = rand() % 3;
		}
	}

	//Only 0's & 1's in the Map
	for (int i = 0; i < 23; i++) {
		for (int j = 0; j < 23; j++)
			if (i == 0 || j == 0 || i == 22 || j == 22)		BackendMaze[i][j] = 1;
			else if (BackendMaze[i][j] > 1)		BackendMaze[i][j] = 0;
	}

	BackendMaze[treasureX][treasureY] = -1;		//Treasure

	//Draw GRID cells
	for (int i = 0; i < 23; i++) {
		for (int j = 0; j < 23; j++) {
			DrawCells[i][j].setPosition(i * 47.f, j * 47.f);
			DrawCells[i][j].setSize(sf::Vector2f(47.f, 47.f));
			DrawCells[i][j].setOutlineThickness(0.5f);
			DrawCells[i][j].setOutlineColor(sf::Color(0, 0, 0));

			//Draw randomized WALL cells
			if (!(i == player.x && j == player.y) && BackendMaze[i][j] == 1) {
				DrawCells[i][j].setFillColor(sf::Color(125, 222, 222));
				DrawCells[i][j].setTexture(&wallTex);
			}
			//Draw Treasure
			else if (!(i == player.x && j == player.y) && BackendMaze[i][j] == -1) {
				DrawCells[i][j].setFillColor(sf::Color(255, 255, 0));
			}
		}
	}

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed && !gameOver) {
				switch (event.key.code) {
				case sf::Keyboard::Up:
					if (BackendMaze[player.x][player.y - 1] != 1)	player.y -= 1;
					else if (BackendMaze[player.x][player.y - 1] == 1 || BackendMaze[player.x][player.y + 1] == 1 || BackendMaze[player.x + 1][player.y] == 1 || BackendMaze[player.x - 1][player.y] == 1) {
						if (!fnt.loadFromFile("Valorant Font.ttf")) {
							cout << "ERROR LOADING FONT" << endl;
						}
						else {
							DisplayLose();
						}
					}
					break;

				case sf::Keyboard::Down:
					if (BackendMaze[player.x][player.y + 1] != 1)	player.y += 1;
					else if (BackendMaze[player.x][player.y - 1] == 1 || BackendMaze[player.x][player.y + 1] == 1 || BackendMaze[player.x + 1][player.y] == 1 || BackendMaze[player.x - 1][player.y] == 1) {
						if (!fnt.loadFromFile("Valorant Font.ttf")) {
							cout << "ERROR LOADING FONT" << endl;
						}
						else {
							DisplayLose();
						}
					}
					break;

				case sf::Keyboard::Right:
					if (BackendMaze[player.x + 1][player.y] != 1)	player.x += 1;
					else if (BackendMaze[player.x][player.y - 1] == 1 || BackendMaze[player.x][player.y + 1] == 1 || BackendMaze[player.x + 1][player.y] == 1 || BackendMaze[player.x - 1][player.y] == 1) {
						if (!fnt.loadFromFile("Valorant Font.ttf")) {
							cout << "ERROR LOADING FONT" << endl;
						}
						else {
							DisplayLose();
						}
					}
					break;

				case sf::Keyboard::Left:
					if (BackendMaze[player.x - 1][player.y] != 1)	player.x -= 1;
					else if (BackendMaze[player.x][player.y - 1] == 1 || BackendMaze[player.x][player.y + 1] == 1 || BackendMaze[player.x + 1][player.y] == 1 || BackendMaze[player.x - 1][player.y] == 1) {
						if (!fnt.loadFromFile("Valorant Font.ttf")) {
							cout << "ERROR LOADING FONT" << endl;
						}
						else {
							DisplayLose();
						}
					}
					break;
				}
			}
			//Draw text on winning condition
			if (player.x == treasure.x && player.y == treasure.y) {
				if (!fnt.loadFromFile("Valorant Font.ttf")) {
					cout << "ERROR LOADING FONT" << endl;
				}
				else{
					DisplayWin();
				}
			}
			playerSprite.setPosition(player.x * 47.f, player.y * 47.f);
		}

		for (int i = 0; i < 23; i++) {
			for (int j = 0; j < 23; j++) {
				window.draw(DrawCells[i][j]);
			}
			window.draw(playerSprite);
			window.draw(treasureSprite);
			window.draw(txtTop);
			window.draw(txtBot);
			window.display();
			window.setVerticalSyncEnabled(true);
		}
	}

	//Show final map's values on console
	for (int i = 0; i < 23; i++) {
		for (int j = 0; j < 23; j++) {
			cout << BackendMaze[j][i] << " ";
		}
		cout << endl;
	}
}
