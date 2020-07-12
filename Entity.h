#pragma once

enum EntityType
{
	PLAYER,
	BLOCK,
	COIN
};

class Entity
{
public:
	Entity() { };
	virtual ~Entity() { };

public:
	sf::Sprite sprite;
	EntityType type;
	float sideLength;
};

