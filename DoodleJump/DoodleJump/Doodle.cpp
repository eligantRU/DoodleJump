#include "stdafx.h"
#include "sheet.h"

Doodle::Doodle(Assets & assets)
	:m_assets(&assets)
{
	m_body = new sf::Sprite;
	setTexture(m_assets->DOODLE_LEFT_TEXTURE);
	setPosition(sf::Vector2f(WINDOW_WIDTH/2, WINDOW_HEIGHT/2));
	setDirection(DirectionX::NONE);
	setPositionBeforeDown(getPosition());
	m_lastDirection = DirectionX::LEFT;
	m_speedY = -50.f;
}

Doodle::~Doodle()
{
	delete m_body;
	m_body = nullptr;
}

void Doodle::draw(sf::RenderWindow & window)
{
	window.draw(*m_body);
}

void Doodle::move(sf::Vector2f deltaPosition)
{
	m_body->move(deltaPosition);
}

void Doodle::setTexture(sf::Texture & texture)
{
	m_body->setTextureRect(sf::IntRect(0, 0, int(texture.getSize().x), int(texture.getSize().y)));
	m_body->setTexture(texture);
}

sf::Vector2f Doodle::getPosition(void)
{
	return m_body->getPosition();
}

void Doodle::setPosition(sf::Vector2f position)
{
	m_body->setPosition(position);
}

void Doodle::setRotation(float degree)
{
	m_body->setRotation(degree);
}

void Doodle::rotate(float degree)
{
	m_body->rotate(degree);
}

DirectionX Doodle::getDirection(void)
{
	return m_direction;
}

DirectionX Doodle::getLastDirection(void)
{
	return m_lastDirection;
}

void Doodle::updateDirection(bool isLeft, bool isRight)
{
	setDirection(DirectionX::NONE);
	if (isLeft)
	{
		setDirection(DirectionX::LEFT);
		m_lastDirection = DirectionX::LEFT;
	}
	if (isRight)
	{
		setDirection(DirectionX::RIGHT);
		m_lastDirection = DirectionX::RIGHT;
	}
	if (isLeft && isRight)
	{
		setDirection(DirectionX::NONE);
	}
}

void Doodle::setDirection(DirectionX newDirection)
{
	m_direction = newDirection;
	switch (newDirection)
	{
	case DirectionX::LEFT:
		m_body->setTexture(m_assets->DOODLE_JUMP_LEFT_TEXTURE);
		break;
	case DirectionX::RIGHT:
		m_body->setTexture(m_assets->DOODLE_JUMP_RIGHT_TEXTURE);
		break;
	case DirectionX::NONE:
		break;
	default:
		break;
	}
}

void Doodle::setSpeedY(float speed)
{
	m_speedY = speed;
}

float Doodle::getSpeedY(void)
{
	return m_speedY;
}

sf::Vector2f Doodle::getPositionBeforeDown(void)
{
	return m_positionBeforeDown;
}

void Doodle::setPositionBeforeDown(sf::Vector2f position)
{
	m_positionBeforeDown = position;
}
