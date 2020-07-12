#pragma once
#include "pch.h"

class Camera {
public:

	Camera(sf::View view);
	~Camera();

	sf::View updatePosition(sf::Vector2f mapBorders, float playerXPosition);

private:

	sf::View view;
};