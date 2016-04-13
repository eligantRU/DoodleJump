#pragma once

#include "stdafx.h"
#include "sheet.h"

struct Doodle
{
public:
	Doodle(Assets * assets);
	~Doodle();
	sf::Sprite * body;
	SDirection direction;
	Collision collision;
	int deltaHeight;
	DirectionX lastDirectionX;
	sf::Vector2f positionBeforeDown;
	float speedY;
};