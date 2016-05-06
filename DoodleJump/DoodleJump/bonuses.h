#pragma once

#include "stdafx.h"
#include "sheet.h"

struct Bonus
{
public:
	Bonus();
	~Bonus();
	void draw(sf::RenderWindow & window);
	void move(sf::Vector2f deltaPosition);
	void setTexture(sf::Texture & texture);
	sf::Vector2f getPosition(void);
	void setPosition(sf::Vector2f position);
	void setPlateIndex(int index);
	int getPlateIndex(void);
	void setSpeedX(int speed);
	int getSpeedX(void);
	void setRotation(float degree);
	void rotate(float degree);
	void setBonusType(BonusType type);
	BonusType getBonusType(void);
private:
	std::unique_ptr<sf::Sprite> m_body;
	int m_plateIndex;
	int m_speedX;
	BonusType m_type;
};