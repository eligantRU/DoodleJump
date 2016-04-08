#include "stdafx.h"
#include "sheet.h"

Doodle::Doodle(Assets * assets)
{
	body = new sf::Sprite;
	body->setTexture(assets->DOODLE_LEFT_TEXTURE);
	body->setScale(sf::Vector2f(1.f, 1.f));
	body->setPosition(260, 350);
	direction.x = DirectionX::NONE;
	lastDirectionX = DirectionX::LEFT;
	positionBeforeDown.y = body->getPosition().y;
	direction.y = DirectionY::DOWN;
	speedY = -50.f;
}

Doodle::~Doodle()
{
	delete body;
	body = NULL;
}