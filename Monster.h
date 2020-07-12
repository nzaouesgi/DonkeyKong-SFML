#pragma once

#include "Entity.h"
#include "Block.h"
#include "Mario.h"

class Monster : public Entity {

public:

	Monster();
	~Monster();
	
	void updatePosition(sf::Time elapsedTime, std::vector<std::shared_ptr<Block>> blocks);
	bool killMario(std::shared_ptr<Mario> mario);

private:

	bool checkBlockCollision(std::vector<std::shared_ptr<Block>> blocks);
	void changeDirection();

	static const float mainVelocity;

	float xVelocity;

	sf::Texture leftTexture;
	sf::Texture rightTexture;
};