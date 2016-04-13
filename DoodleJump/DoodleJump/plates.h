#pragma once

#include "stdafx.h"
#include "sheet.h"

struct Plate
{
public:
	sf::Sprite * body;
	PlateType type;
	bool fallingPlate;
	int speedX;
	Plate(Assets * assets);
	~Plate();
};