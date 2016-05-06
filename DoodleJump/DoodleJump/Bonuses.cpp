#include "stdafx.h"
#include "sheet.h"

Bonus::Bonus()
{
	m_body = std::make_unique<sf::Sprite>();
}

Bonus::~Bonus()
{

}

void Bonus::draw(sf::RenderWindow & window)
{
	window.draw(*m_body);
}

void Bonus::move(sf::Vector2f deltaPosition)
{
	m_body->move(deltaPosition);
}

void Bonus::setTexture(sf::Texture & texture)
{
	m_body->setTextureRect(sf::IntRect(0, 0, int(texture.getSize().x), int(texture.getSize().y)));
	m_body->setTexture(texture);
}

sf::Vector2f Bonus::getPosition(void)
{
	return m_body->getPosition();
}

void Bonus::setPosition(sf::Vector2f position)
{
	m_body->setPosition(position);
}

void Bonus::setPlateIndex(int index)
{
	m_plateIndex = index;
}

int Bonus::getPlateIndex(void)
{
	return m_plateIndex;
}

void Bonus::setSpeedX(int speed)
{
	m_speedX = speed;
}

int Bonus::getSpeedX(void)
{
	return m_speedX;
}

void Bonus::setBonusType(BonusType type)
{
	m_type = type;
}

BonusType Bonus::getBonusType(void)
{
	return m_type;
}

void Bonus::setRotation(float degree)
{
	m_body->setRotation(degree);
}

void Bonus::rotate(float degree)
{
	m_body->rotate(degree);
}
