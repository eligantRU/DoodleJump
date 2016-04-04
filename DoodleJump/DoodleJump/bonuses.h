#pragma once

#include "stdafx.h"
#include "sheet.h"

struct Bonus
{
public:
	Bonus();
	~Bonus();
	BonusType type;
	sf::Sprite * body;
	int plateIndex;
	int speedX;
private:
};