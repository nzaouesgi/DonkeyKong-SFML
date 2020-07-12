#include "pch.h"
#include "Entity.h"
#include "Level.h"
#include "Game.h"
#include "Block.h"
#include "Mario.h"

Level::Level(std::vector<std::string> map) {
	this->map = map;

	if (this->map.size() == 0) {
		throw new std::runtime_error("Bad map format");
	}

	this->mapBlockHeight = map.size();
	this->mapBlockWidth = 0;
	for (std::string line : map) {
		if (line.size() > this->mapBlockWidth) {
			this->mapBlockWidth = line.size();
		}
	}

	this->baseEntitySize = (float)(Game::windowHeight / mapBlockHeight);

	this->mapPixelsHeight = (size_t)(this->mapBlockHeight * this->baseEntitySize);
	this->mapPixelsWidth = (size_t)(this->mapBlockWidth * this->baseEntitySize);

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

			std::shared_ptr<Entity> entity;

			switch (c) {

				case '#':
					entity = std::make_shared<Block>();
					scaleAndPositionEntity(entity);
					entities.push_back(entity);
					break;

				case 'p':
					entity = std::make_shared<Mario>();
					scaleAndPositionEntity(entity);
					entities.push_back(entity);
					break;

				case 'o':
					entity = std::make_shared<Coin>();
					scaleAndPositionEntity(entity);
					entities.push_back(entity);
					break;
			}
			
			columnIndex++;
		}

		lineIndex++;
	}

	return entities;
}
