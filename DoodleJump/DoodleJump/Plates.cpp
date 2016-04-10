#include "stdafx.h"
#include "sheet.h"

Plate::Plate(Assets * assets)
{	
	this->assets = assets;
	body = new sf::Sprite;
	type = PlateType::STATIC;
	body->setTexture(assets->PLATE_STATIC_TEXTURE);
	fallingPlate = false;
	float x = float(rand() % (550 - PLATE_WIDTH));
	float y = float(rand() % (700 - PLATE_HEIGHT));
	body->setPosition(x, y);
	speedX = 0;
}

Plate::~Plate()
{
	delete body;
	body = NULL;
}