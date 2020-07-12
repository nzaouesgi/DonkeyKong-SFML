#include "pch.h"
#include "Mario.h"
#include "Game.h"
#include "Block.h"

const float Mario::mainVelocity = 0.2f * (Game::windowWidth);

#define MARIO_LEFT_TEXTURE_PATH "Media/Textures/mario_standing_left.png"
#define MARIO_RIGHT_TEXTURE_PATH "Media/Textures/mario_standing_right.png"
#define MARIO_LEFT_RUNNING_TEXTURE_PATH "Media/Textures/mario_running_left.png"
#define MARIO_RIGHT_RUNNING_TEXTURE_PATH "Media/Textures/mario_running_right.png"

Mario::Mario(){
	
	this->xVelocity = 0;
	this->yVelocity = Mario::mainVelocity;
	this->jumpClock.restart();
	this->jumping = false;
	this->orientation = MarioOrientation::RIGHT;

	if (this->leftTexture.loadFromFile(MARIO_LEFT_TEXTURE_PATH) == false) {
		throw new std::runtime_error("could not load player texture");
	}

	if (this->rightTexture.loadFromFile(MARIO_RIGHT_TEXTURE_PATH) == false) {
		throw new std::runtime_error("could not load player texture");
	}

	if (this->leftRunningTexture.loadFromFile(MARIO_LEFT_RUNNING_TEXTURE_PATH) == false) {
		throw new std::runtime_error("could not load player texture");
	}

	if (this->rightRunningTexture.loadFromFile(MARIO_RIGHT_RUNNING_TEXTURE_PATH) == false) {
		throw new std::runtime_error("could not load player texture");
	}

	this->type = EntityType::PLAYER;
	this->sprite.setTexture(this->rightTexture);

}

Mario::~Mario(){}


void Mario::moveLeft(){
	this->xVelocity = -(Mario::mainVelocity);
	this->sprite.setTexture(this->leftRunningTexture);
	if (!this->orientation == MarioOrientation::LEFT) {
		this->orientation = MarioOrientation::LEFT;
	}
}


void Mario::moveRight(){
	this->xVelocity = Mario::mainVelocity;
	this->sprite.setTexture(this->rightRunningTexture);
	if (!this->orientation == MarioOrientation::RIGHT) {
		this->orientation = MarioOrientation::RIGHT;
	}
}

void Mario::stop(){
	this->xVelocity = 0;
	if (this->orientation == MarioOrientation::RIGHT) {
		this->sprite.setTexture(this->rightTexture);
	}
	else {
		this->sprite.setTexture(this->leftTexture);
	}
}

void Mario::jump(){
	
	if (this->jumping == true) {
		return;
	}

	this->jumping = true;
	this->jumpClock.restart();
	
	this->yVelocity = -(Mario::mainVelocity);
}

void Mario::stopJumping() {
	this->jumping = false;
	this->yVelocity = (Mario::mainVelocity);
}

void Mario::updatePosition(sf::Time elapsedTime, std::vector<std::shared_ptr<Block>> blocks){

	float seconds = elapsedTime.asSeconds();

	this->sprite.move(0, this->yVelocity * seconds);
	
	if (this->checkBlockCollision(blocks)) {
		
		this->sprite.move(0, -(this->yVelocity * seconds));
		
		if (this->yVelocity < 0) {
			this->yVelocity = (Mario::mainVelocity);
		} else {
			this->stopJumping();
		}
	}

	this->sprite.move(this->xVelocity * seconds, 0);
	if (this->checkBlockCollision(blocks)) {
		this->sprite.move(-(this->xVelocity * seconds), 0);
	}
}

void Mario::updateState(){
	
	// Update jump state
	if (this->jumping == true && this->jumpClock.getElapsedTime().asSeconds() > 0.8) {
		this->yVelocity = (Mario::mainVelocity);
	}	
}

void Mario::pickCoin(std::vector<std::shared_ptr<Coin>> coins){
	
	for (std::shared_ptr<Coin> coin : coins) {
		if (coin->sprite.getGlobalBounds().intersects(this->sprite.getGlobalBounds())) {
			coin->pickUp();
		}
	}
}

void Mario::savePrincess(std::shared_ptr<Princess> princess) {
	if (princess->sprite.getGlobalBounds().intersects(this->sprite.getGlobalBounds())) {
		princess->save();
	}
}

bool Mario::hasFallen(sf::FloatRect mapRect)
{
	if (mapRect.intersects(this->sprite.getGlobalBounds()))
		return false;

	return true;
}

bool Mario::checkBlockCollision(std::vector<std::shared_ptr<Block>> blocks) {
	
	for (std::shared_ptr<Block> block : blocks) {
		if (block->sprite.getGlobalBounds().intersects(this->sprite.getGlobalBounds()))
			return true;
	}
	return false;
}
