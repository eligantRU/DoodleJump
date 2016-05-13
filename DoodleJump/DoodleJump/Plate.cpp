#include "stdafx.h"
#include "sheet.h"

Plate::Plate()
{	
	m_body = std::make_unique<sf::Sprite>();
	setPosition(sf::Vector2f(float(rand() % (WINDOW_WIDTH - PLATE_WIDTH)), float(rand() % (WINDOW_HEIGHT - PLATE_HEIGHT))));
}

Plate::~Plate()
{

}

void Plate::draw(sf::RenderWindow & window)
{
	window.draw(*m_body);
}

void Plate::move(sf::Vector2f deltaPosition)
{
	m_body->move(deltaPosition);
}

void Plate::setTexture(sf::Texture & texture)
{
	m_body->setTextureRect(sf::IntRect(0, 0, int(texture.getSize().x), int(texture.getSize().y)));
	m_body->setTexture(texture);
}

sf::Vector2f Plate::getPosition()
{
	return m_body->getPosition();
}

void Plate::setPosition(sf::Vector2f position)
{
	m_body->setPosition(position);
}

void Plate::setRotation(float degree)
{
	m_body->setRotation(degree);
}

void Plate::rotate(float degree)
{
	m_body->rotate(degree);
}

void Plate::setType(PlateType type)
{
	m_type = type;
}

PlateType Plate::getType()
{
	return m_type;
}

int Plate::getSpeedX()
{
	return m_speedX;
}

void Plate::setSpeedX(int speedX)
{
	m_speedX = speedX;
}

bool Plate::getFallStatus()
{
	return m_fallStatus;
}

void Plate::setFallStatus(bool fallStatus)
{
	m_fallStatus = fallStatus;
}
