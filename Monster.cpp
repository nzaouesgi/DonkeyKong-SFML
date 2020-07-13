#include "pch.h"

#include "Monster.h"
#include "Game.h"
#include "Block.h"

#define MONSTER_LEFT_TEXTURE "Media/Textures/bowser_left.png"
#define MONSTER_RIGHT_TEXTURE "Media/Textures/bowser_right.png"

const float Monster::mainVelocity = 0.10f * (Game::windowWidth);

Monster::Monster(){

	if (this->leftTexture.loadFromFile(MONSTER_LEFT_TEXTURE) == false) {
		throw std::runtime_error("Could not load monster texture");
	}
	if (this->rightTexture.loadFromFile(MONSTER_RIGHT_TEXTURE) == false) {
		throw std::runtime_error("Could not load monster texture");
	}

	this->xVelocity = Monster::mainVelocity;
	this->type = EntityType::MONSTER;

	this->sprite.setTexture(this->rightTexture);
}

void Monster::changeDirection() {
	if (this->xVelocity < 0) {
		this->xVelocity = Monster::mainVelocity;
		this->sprite.setTexture(this->rightTexture);
	}
	else {
		this->xVelocity = -(Monster::mainVelocity);
		this->sprite.setTexture(this->leftTexture);
	}
}

void Monster::updatePosition(sf::Time elapsedTime, std::vector<std::shared_ptr<Block>> blocks) {

	float seconds = elapsedTime.asSeconds();

	this->sprite.move(this->xVelocity * seconds, 0.0f);

	if (this->checkBlockCollision(blocks)) {
		this->sprite.move(-(this->xVelocity * seconds), 0.0f);
		this->changeDirection();
	}
}

bool Monster::killMario(std::shared_ptr<Mario> mario){

	if (this->sprite.getGlobalBounds().intersects(mario->sprite.getGlobalBounds()))
		return true;

	return false;
}

bool Monster::checkBlockCollision(std::vector<std::shared_ptr<Block>> blocks) {

	for (std::shared_ptr<Block> block : blocks) {
		if (block->sprite.getGlobalBounds().intersects(this->sprite.getGlobalBounds()))
			return true;
	}
	return false;
}

Monster::~Monster(){}
