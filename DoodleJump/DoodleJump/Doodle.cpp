#include "stdafx.h"
#include "sheet.h"

Doodle::Doodle()
{
	body = new sf::Sprite;
	body->setTexture(assets->DOODLE_LEFT_TEXTURE);
	body->setScale(sf::Vector2f(1.f, 1.f));
	body->setPosition(260, 350);
	direction.x = DirectionX::NONE;
	lastDirectionX = DirectionX::LEFT;
	sf::Vector2f doodlePosition = body->getPosition(); // TODO: внести это ниже, соптимизить
	positionBeforeDown.y = doodlePosition.y;
	direction.y = DirectionY::DOWN;
	speedY = -25.f;
}

Doodle::~Doodle()
{
	delete body;
	body = NULL;
}