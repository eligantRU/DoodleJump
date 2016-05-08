#pragma once

#include "stdafx.h"
#include "sheet.h"

struct Doodle
{
public:
	Doodle(Assets & assets);
	~Doodle();
	void draw(sf::RenderWindow & window) const;
	void move(sf::Vector2f deltaPosition);
	void setTexture(sf::Texture & texture);
	sf::Vector2f getPosition() const;
	void setPosition(sf::Vector2f position);
	void setRotation(float degree);
	void rotate(float degree);
	void updateDirection(bool isLeft, bool isRight);
	void setDirection(DirectionX direction);
	void setSpeedY(float speed);
	float getSpeedY() const;
	void correctSkin();
	sf::Vector2f getPositionBeforeDown() const;
	void setPositionBeforeDown(sf::Vector2f position);
	DirectionX getDirection() const;
	DirectionX getLastDirection() const;
private:
	std::unique_ptr<sf::Sprite> m_body;
	float m_speedY;
	DirectionX m_direction;
	DirectionX m_lastDirection;
	Assets & m_assets;
	sf::Vector2f m_positionBeforeDown;
};