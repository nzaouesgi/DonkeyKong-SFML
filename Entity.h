#pragma once

enum EntityType
{
	PLAYER,
	BLOCK,
	COIN,
	MONSTER,
	PRINCESS
};

class Entity
{
public:
	virtual ~Entity() {};

public:
	sf::Sprite sprite;
	EntityType type;
	float sideLength;
};

