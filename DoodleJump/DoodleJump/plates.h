#pragma once

#include "stdafx.h"
#include "sheet.h"

struct Plate
{
public:
	sf::Sprite * body;
	sf::Texture texture;
	PlateType type;
	bool fallingPlate;
	int speedX;
	Plate(Assets * assets);
	~Plate();
private:
	Assets * assets;
};