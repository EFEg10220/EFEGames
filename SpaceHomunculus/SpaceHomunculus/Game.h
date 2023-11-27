#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <fstream>

using namespace sf;
using namespace std;

class Game {
private:
	Texture player;
	Texture platform;
	Texture playScreenBackground;

	pair<int, int> plat[40];

	int x = 100;
	int y = 100;
	int h = 100;
	float dx = 0;
	float dy = 0;
	int collisionCount = 0;
	int jumpSpeed = 10;
	int jumpHeight = 300;
	const string scoreFileName = "scores.txt";
	int previousScore = 0;
	int highScore = 0;
	Font font;
	Text platformText;
	Text highScoreText;
	Text playButtonText;
	Text exitButtonText;
	int speed = 3;
	bool gameStarted = false;


public:
	bool isMouseOverButton(const RectangleShape& button, const RenderWindow& window);
	void runGame();
};