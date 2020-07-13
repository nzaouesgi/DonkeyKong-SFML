#include "pch.h"
#include "Entity.h"
#include "Level.h"
#include "Game.h"
#include "Block.h"
#include "Mario.h"
#include "Monster.h"
#include "Princess.h"

Level::Level(std::vector<std::string> map) {
	this->map = map;

	if (this->map.size() == 0) {
		throw std::runtime_error("Bad map format");
	}

	this->mapBlockHeight = map.size();
	this->mapBlockWidth = 0;
	for (std::string line : map) {
		if (line.size() > this->mapBlockWidth) {
			this->mapBlockWidth = line.size();
		}
	}

	this->baseEntitySize = (float)(Game::windowHeight / mapBlockHeight);

	this->mapRect.left = 0.0f;
	this->mapRect.top = 0.0f;

	this->mapRect.height = (size_t)(this->mapBlockHeight * this->baseEntitySize);
	this->mapRect.width = (size_t)(this->mapBlockWidth * this->baseEntitySize);

}

Level::~Level(){}

std::vector<std::shared_ptr<Entity>> Level::create() {

	std::vector<std::shared_ptr<Entity>> entities;

	unsigned lineIndex = 0;
	unsigned columnIndex = 0;

	for (std::string line : map) {

		columnIndex = 0;

		auto scaleAndPositionEntity = [this, &columnIndex, &lineIndex](std::shared_ptr<Entity> entity) -> void {

			switch (entity->type) {
				case EntityType::PLAYER:
					entity->sideLength = (this->baseEntitySize * 0.85f);
					break;
				default:
					entity->sideLength = this->baseEntitySize;
			}

			float scale = entity->sideLength / (float)(entity->sprite.getTexture()->getSize().x);

			entity->sprite.scale(scale, scale);
			entity->sprite.setPosition(this->baseEntitySize * columnIndex, this->baseEntitySize * lineIndex);
		};

		for (char const &c : line) {

			std::shared_ptr<Entity> entity = nullptr;

			switch (c) {

				case '#':
					entity = std::make_shared<Block>();
					break;

				case 'p':
					entity = std::make_shared<Mario>();
					break;

				case 'o':
					entity = std::make_shared<Coin>();
					break;

				case 'm':
					entity = std::make_shared<Monster>();
					break;

				case 'e':
					entity = std::make_shared<Princess>();
					break;
			}

			if (entity != nullptr) {
				scaleAndPositionEntity(entity);
				entities.push_back(entity);
			}
			
			columnIndex++;
		}

		lineIndex++;
	}

	return entities;
}
