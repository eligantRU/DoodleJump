#include "stdafx.h"
#include "sheet.h"

Doodle::Doodle(Assets & assets)
	:assets(&assets)
{
	body = new sf::Sprite;
	body->setTexture(assets.DOODLE_LEFT_TEXTURE);
	body->setScale(sf::Vector2f(1.f, 1.f));
	body->setPosition(260, 350);
	direction.x = DirectionX::NONE;
	lastDirection = DirectionX::LEFT;
	positionBeforeDown.y = body->getPosition().y;
	direction.y = DirectionY::DOWN;
	speedY = -50.f;
}

Doodle::~Doodle()
{
	delete body;
	body = nullptr;
}

DirectionX Doodle::getDirection(void)
{
	return direction.x;
}

DirectionX Doodle::getLastDirection(void)
{
	return lastDirection;
}

void Doodle::updateDirection(bool isLeft, bool isRight)
{
	setDirection(DirectionX::NONE);
	if (isLeft)
	{
		setDirection(DirectionX::LEFT);
		lastDirection = DirectionX::LEFT;
	}
	if (isRight)
	{
		setDirection(DirectionX::RIGHT);
		lastDirection = DirectionX::RIGHT;
	}		
}

void Doodle::setDirection(DirectionX newDirection)
{
	direction.x = newDirection;
	switch (newDirection)
	{
	case DirectionX::LEFT:
		body->setTexture(assets->DOODLE_JUMP_LEFT_TEXTURE);
		break;
	case DirectionX::RIGHT:
		body->setTexture(assets->DOODLE_JUMP_RIGHT_TEXTURE);
		break;
	case DirectionX::NONE:
		break;
	default:
		break;
	}
}