#pragma once

#include "Level.h"
#include "Mario.h"
#include "Block.h"
#include "Coin.h"
#include "Camera.h"

class Game
{
public:

	Game();
	virtual ~Game();

	void run();

	static const unsigned int windowWidth;
	static const unsigned int windowHeight;

private:

	void update(sf::Time elapsedTime);
	void updatePlayer(sf::Time elapsedTime);
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void updateCamera();
	void updateStatistics();
	void render();

	static const sf::Time frameTime;

	void processEvents();

	std::unique_ptr<Level> level;
	std::unique_ptr<Camera> camera;

	std::vector<std::shared_ptr<Block>> blocks;
	std::vector<std::shared_ptr<Coin>> coins;
	
	std::shared_ptr<Mario> mario;

	sf::RenderWindow renderWindow;
	sf::Font font;
	sf::Text stats;

	bool mIsMovingLeft;
	bool mIsMovingRight;
	bool mIsJumping;
};

