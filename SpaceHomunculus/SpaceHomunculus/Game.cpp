#include "Game.h"

bool Game::isMouseOverButton(const RectangleShape& button, const RenderWindow& window) {
	Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
	return button.getGlobalBounds().contains(mousePos);
}

void Game::runGame() {
	srand(time(0));

	RenderWindow app(VideoMode(770, 477), "SpaceHomunculus");
	app.setFramerateLimit(60);

	player.loadFromFile("Resources/Player.png");
	platform.loadFromFile("Resources/PlatForm.png");
	playScreenBackground.loadFromFile("Resources/Background.png");

	Sprite playerHomunculus(player);
	Sprite platform_object(platform);
	Sprite playScreenBgSprite(playScreenBackground);

	playerHomunculus.setScale(0.2f, 0.2f);
	platform_object.setScale(0.1f, 0.1f);

	for (int i = 0; i < 10; i++) {
		plat[i].first = rand() % 650;
		plat[i].second = rand() % 750;
	}

	ifstream scoreFile(scoreFileName);
	if (scoreFile.is_open()) {
		scoreFile >> previousScore >> highScore;
		scoreFile.close();
	}

	font.loadFromFile("Resources/JOKERMAN.ttf");

	platformText.setFont(font);
	platformText.setCharacterSize(20);
	platformText.setFillColor(Color::White);

	highScoreText.setFont(font);
	highScoreText.setCharacterSize(20);
	highScoreText.setFillColor(Color::White);
	highScoreText.setPosition(600, 10);

	RectangleShape playButton(Vector2f(100, 40));
	playButton.setFillColor(Color::Green);
	playButton.setPosition(360, 200);

	playButtonText.setFont(font);
	playButtonText.setCharacterSize(20);
	playButtonText.setFillColor(Color::White);
	playButtonText.setString("Play");
	playButtonText.setPosition(380, 205);

	RectangleShape exitButton(Vector2f(100, 40));
	exitButton.setFillColor(Color::Red);
	exitButton.setPosition(670, 430);

	exitButtonText.setFont(font);
	exitButtonText.setCharacterSize(20);
	exitButtonText.setFillColor(Color::White);
	exitButtonText.setString("Exit");
	exitButtonText.setPosition(685, 440);

	while (app.isOpen()) {
		Event a;
		while (app.pollEvent(a)) {
			if (a.type == Event::Closed) {
				ofstream scoreFile(scoreFileName);
				if (scoreFile.is_open()) {
					scoreFile << previousScore << " " << highScore;
					scoreFile.close();
				}
				app.close();
			}
			else if (a.type == Event::MouseButtonPressed && a.mouseButton.button == Mouse::Left) {
				if (isMouseOverButton(playButton, app) && !gameStarted) {
					gameStarted = true;
				}
				else if (isMouseOverButton(exitButton, app) && !gameStarted) {
					ofstream scoreFile("scores.txt");
					if (scoreFile.is_open()) {
						scoreFile << previousScore << " " << highScore;
						scoreFile.close();
					}
					app.close();
				}
			}
		}

		if (gameStarted) {

			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				x += speed;
			}

			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				x -= speed;
			}

			dy += 0.15;
			y += dy;

			if (y > 500) {
				dy = -jumpSpeed;
			}

			if (y < h) {
				for (int i = 0; i < 10; i++) {
					y = h;
					plat[i].second = plat[i].second - dy;
					if (plat[i].second > 500) {
						plat[i].second = 0;
						plat[i].first = rand() % 600;

					}
				}
			}

			for (int i = 0; i < 10; i++) {
				if ((x + 50 > plat[i].first) && (x + 20 < plat[i].first + 68) && (y + 70 > plat[i].second) && (y + 70 < plat[i].second + 14) && (dy > 0)) {
					dy = -jumpSpeed;
					collisionCount++;
					if (collisionCount % 10 == 0) {
						speed += 1;
						jumpSpeed += 1;
						dy += 0.2;
					}
				}
			}
			playerHomunculus.setPosition(x, y);
			app.draw(playScreenBgSprite);

			app.draw(playerHomunculus);
			for (int i = 0; i < 10; i++) {
				platform_object.setPosition(plat[i].first, plat[i].second);
				app.draw(platform_object);
			}
			platformText.setString("Score: " + to_string(collisionCount));
			if (collisionCount > highScore) {
				highScore = collisionCount;
			}

			highScoreText.setString("High Score: " + to_string(highScore));
		}
		else {
			app.draw(playScreenBgSprite);
			app.draw(playButton);
			app.draw(playButtonText);
			app.draw(exitButton);
			app.draw(exitButtonText);

			platformText.setString("Previous Score: " + to_string(previousScore));
			highScoreText.setString("High Score: " + to_string(highScore));
		}
		app.draw(platformText);
		app.draw(highScoreText);
		app.display();
	}
}