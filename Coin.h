#pragma once

#include "Entity.h"

class Coin : public Entity {

public:
	
	Coin();
	~Coin();

	bool isPickedUp();
	void pickUp();

private:
	sf::Texture coinTexture;
	bool pickedUp;
};