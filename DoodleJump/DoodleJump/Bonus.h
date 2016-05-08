#pragma once

#include "stdafx.h"
#include "sheet.h"

struct Bonus
{
public:
	Bonus();
	~Bonus();
	void draw(sf::RenderWindow & window) const;
	void move(sf::Vector2f deltaPosition);
	void setTexture(sf::Texture & texture);
	sf::Vector2f getPosition() const;
	void setPosition(sf::Vector2f position);
	void setPlateIndex(int index);
	int getPlateIndex() const;
	void setSpeedX(int speed);
	int getSpeedX() const;
	void setRotation(float degree);
	void rotate(float degree);
	void setBonusType(BonusType type);
	BonusType getBonusType() const;
private:
	std::unique_ptr<sf::Sprite> m_body;
	int m_plateIndex;
	int m_speedX;
	BonusType m_type;
};