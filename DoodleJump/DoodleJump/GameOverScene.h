#pragma once

#include "stdafx.h"
#include "sheet.h"

struct gameOverScene
{
public:
	gameOverScene();
	~gameOverScene();
	gameResult onGameOverMenu(sf::RenderWindow & window, uint64_t & score);
private:
	sf::Sprite * background;
	sf::Sprite * playAgainButton;
	sf::Sprite * goMenuButton;
	sf::Sprite * title;

	sf::Text playAgainText;
	sf::Text goMenuText;
	sf::Text lastRecord;
};
