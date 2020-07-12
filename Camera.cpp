#include "pch.h"
#include "Camera.h"

Camera::Camera(sf::View view){
	this->view = view;
}

Camera::~Camera(){
}

sf::View Camera::updatePosition(sf::Vector2f mapBorders, float playerXPosition){

	this->view.setCenter(playerXPosition, this->view.getCenter().y);

	sf::Vector2f size = this->view.getSize();

	if ((playerXPosition - (size.x / 2)) <= 0) {
		this->view.move(-(playerXPosition - (size.x / 2)), 0);
	}

	else if (playerXPosition + (size.x / 2) >= mapBorders.x) {
		this->view.move(-(playerXPosition + (size.x / 2) - mapBorders.x), 0);
	}

	return this->view;
}
