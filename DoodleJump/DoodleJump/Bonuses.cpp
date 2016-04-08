#include "stdafx.h"
#include "sheet.h"

Bonus::Bonus()
{
	body = new sf::Sprite;
}

Bonus::~Bonus()
{
	delete body;
	body = NULL;
}
