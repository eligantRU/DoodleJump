#include "stdafx.h"
#include "sheet.h"

Plate::Plate()
{	
	body = new sf::Sprite;
	type = PlateType::STATIC;
	direction.x = DirectionX::NONE;
	body->setTexture(assets->PLATE_STATIC_TEXTURE);
	fallingPlate = false;
	float x = float(rand() % (550 - PLATE_WIDTH));
	float y = float(rand() % (700 - PLATE_HEIGHT)); // —юда запилить функцию дл€ равномерной генерации плит по высоте
	body->setPosition(x, y);
}

Plate::~Plate()
{
	delete body;
	body = NULL;
}