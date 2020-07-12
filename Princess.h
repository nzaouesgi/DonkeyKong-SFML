#pragma once

#include "Entity.h"

class Princess : public Entity {

public:
	Princess();
	~Princess();

	void save();
	bool isSaved();

private:

	sf::Texture princessTexture;
	bool saved;
};