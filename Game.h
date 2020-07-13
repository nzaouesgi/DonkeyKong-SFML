#pragma once

#include "Level.h"
#include "Mario.h"
#include "Block.h"
#include "Coin.h"
#include "Camera.h"
#include "Monster.h"
#include "Princess.h"

class Game
{
public:

	Game(std::vector<std::vector<std::string>> maps);
	void init();
	virtual ~Game();

	void run();
	void run(size_t mapIndex);

	static const unsigned int windowWidth;
	static const unsigned int windowHeight;

private:

	std::vector<std::vector<std::string>> maps;

	void mainLoop();
	void render();
	void update(sf::Time elapsedTime);

	void updateMonsters(sf::Time elapsedTime);
	void updatePlayer(sf::Time elapsedTime);
	void updatePrincess();
	void updateCamera();
	void updateStatistics();
	void updateGameFinishedText();

	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	
	void customizeGameFinishedText();
	void customizeStatText();


	static const sf::Time frameTime;

	void processEvents();

	std::unique_ptr<Level> level;
	std::unique_ptr<Camera> camera;

	std::vector<std::shared_ptr<Block>> blocks;
	std::vector<std::shared_ptr<Coin>> coins;
	std::vector<std::shared_ptr<Monster>> monsters;
	
	std::shared_ptr<Mario> mario;
	std::shared_ptr<Princess> princess;

	sf::RenderWindow renderWindow;
	sf::Font font;
	sf::Text statsText;

	sf::Text gameFinishedText;

	bool isMovingLeft;
	bool isMovingRight;
	bool isJumping;
	bool isRestart;
	bool isNextLevel;

	bool gameOver;
	bool gameWon;
	bool allGamesDone;

	size_t currentMap;
};

