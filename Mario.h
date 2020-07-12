#pragma once

#include "Entity.h"
#include "Block.h"
#include "Coin.h"
#include "Princess.h"

enum MarioOrientation {
	LEFT, RIGHT
};

class Mario: public Entity {

public:

	Mario();
	~Mario();

	void moveLeft();
	void moveRight();
	void stop();
	void jump();

	void updatePosition(sf::Time elapsedTime, std::vector<std::shared_ptr<Block>> blocks);
	void updateState();
	void pickCoin(std::vector<std::shared_ptr<Coin>> coins);
	void savePrincess(std::shared_ptr<Princess> princess);
	bool hasFallen(sf::FloatRect mapRect);

private:

	static const float mainVelocity;

	sf::Clock jumpClock;
	bool jumping;
	void stopJumping();

	bool checkBlockCollision(std::vector<std::shared_ptr<Block>> blocks);

	float xVelocity;
	float yVelocity;

	sf::Texture leftTexture;
	sf::Texture rightTexture;
	sf::Texture leftRunningTexture;
	sf::Texture rightRunningTexture;

	MarioOrientation orientation;
};