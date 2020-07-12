#pragma once

#include "Entity.h"

class Level {

public:

	Level(std::vector<std::string> map);
	~Level();

	sf::FloatRect mapRect;

	size_t mapBlockHeight;
	size_t mapBlockWidth;

	float baseEntitySize;

	std::vector<std::shared_ptr<Entity>> create();

private:

	std::vector<std::string> map;
};