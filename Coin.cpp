#include "pch.h"
#include "Coin.h"

#define COIN_TEXTURE_PATH "Media/Textures/coin.png"

Coin::Coin(){

	this->pickedUp = false;

	if (this->coinTexture.loadFromFile(COIN_TEXTURE_PATH) == false) {
		throw std::runtime_error("could not load block texture");
	}
	this->type = EntityType::COIN;
	this->sprite.setTexture(this->coinTexture);
}

Coin::~Coin(){}

bool Coin::isPickedUp(){
	return this->pickedUp;
}

void Coin::pickUp(){
	this->pickedUp = true;
}
