#pragma once

#include "Entity.h"

class Level {

public:

	Level(std::vector<std::string> map);
	~Level();

	size_t mapPixelsHeight;
	size_t mapPixelsWidth;

	size_t mapBlockHeight;
	size_t mapBlockWidth;

	float baseEntitySize;

	std::vector<std::shared_ptr<Entity>> create();

private:

	std::vector<std::string> map;
};