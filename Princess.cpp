#include "pch.h"

#include "Princess.h"
#include "Mario.h"

#define PRINCESS_TEXTURE_PATH "Media/Textures/princess.png"

Princess::Princess(){

	if (this->princessTexture.loadFromFile(PRINCESS_TEXTURE_PATH) == false) {
		throw std::runtime_error("Could not load princess texture");
	}

	this->saved = false;

	this->type = EntityType::PRINCESS;
	this->sprite.setTexture(this->princessTexture);
}

bool Princess::isSaved() {
	return this->saved;
}

void Princess::save() {
	this->saved = true;
}

Princess::~Princess(){}
