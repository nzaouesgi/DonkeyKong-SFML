#pragma once
#include "Entity.h"

class Block: public Entity {

public:
	Block();
	~Block();

private:

	sf::Texture blockTexture;

};
