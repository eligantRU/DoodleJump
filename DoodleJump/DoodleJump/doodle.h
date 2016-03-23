#pragma once

#include "stdafx.h"
#include "sheet.h"

struct Doodle
{
public:
	Doodle();
	~Doodle();
	sf::Sprite * body;
	sf::Texture texture;
	Direction direction;
	Collision collision;
	int deltaHeight;
	DirectionX lastDirectionX;
	sf::Vector2f positionBeforeDown;
	float speedY;
private:
};