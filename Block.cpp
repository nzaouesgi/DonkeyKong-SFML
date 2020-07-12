#include "pch.h"
#include "Block.h"

#define BLOCK_TEXTURE_PATH "Media/Textures/block.png"

Block::Block(){
	if (this->blockTexture.loadFromFile(BLOCK_TEXTURE_PATH) == false) {
		throw new std::runtime_error("could not load block texture");
	}
	this->type = EntityType::BLOCK;
	this->sprite.setTexture(this->blockTexture);
}

Block::~Block(){}
