#pragma once

#include "stdafx.h"
#include "sheet.h"

struct Doodle
{
public:
	Doodle(Assets & assets);
	~Doodle();
	void updateDirection(bool isLeft, bool isRight);
	void setDirection(DirectionX direction);
	DirectionX getDirection(void);
	DirectionX getLastDirection(void);
	sf::Sprite * body;
	Collision collision;
	sf::Vector2f positionBeforeDown;
	float speedY;
private:
	SDirection direction;
	DirectionX lastDirection;
	Assets * assets;
};