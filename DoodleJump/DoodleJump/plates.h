#pragma once

#include "stdafx.h"
#include "sheet.h"

struct Plate
{
public:
	Plate(Assets & assets);
	~Plate();
	void draw(sf::RenderWindow & window);
	void move(sf::Vector2f deltaPosition);
	void setTexture(sf::Texture & texture);
	sf::Vector2f getPosition(void);
	void setPosition(sf::Vector2f position);
	void setRotation(float degree);
	void rotate(float degree);
	void setType(PlateType type);
	PlateType getType(void);
	int getSpeedX(void);
	void setSpeedX(int speedX);
	bool getFallStatus(void);
	void setFallStatus(bool fallStatus);
private:
	sf::Sprite * m_body;
	PlateType m_type;
	bool m_fallStatus = false;
	int m_speedX = 0;
};