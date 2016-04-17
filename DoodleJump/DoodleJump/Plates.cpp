#include "stdafx.h"
#include "sheet.h"

Plate::Plate(Assets * assets)
{	
	m_body = new sf::Sprite;
	m_type = PlateType::STATIC;
	m_body->setTexture(assets->PLATE_STATIC_TEXTURE);
	setPosition(sf::Vector2f(float(rand() % (550 - PLATE_WIDTH)), float(rand() % (700 - PLATE_HEIGHT))));
}

Plate::~Plate()
{
	delete m_body;
	m_body = nullptr;
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

sf::Vector2f Plate::getPosition(void)
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

PlateType Plate::getType(void)
{
	return m_type;
}

int Plate::getSpeedX(void)
{
	return m_speedX;
}

void Plate::setSpeedX(int speedX)
{
	m_speedX = speedX;
}

bool Plate::getFallStatus(void)
{
	return m_fallStatus;
}

void Plate::setFallStatus(bool fallStatus)
{
	m_fallStatus = fallStatus;
}