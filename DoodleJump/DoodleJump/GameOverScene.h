#pragma once

#include "stdafx.h"
#include "sheet.h"

struct gameOverScene : public Game
{
public:
	gameOverScene();
	~gameOverScene();
	virtual void onGameOverMenu(sf::RenderWindow & window, uint64_t & score);
private:
	sf::Sprite * background;
	sf::Sprite * goMenuButton;
	sf::Sprite * exitButton;

	sf::Text goMenuText;
	sf::Text exitText;
	sf::Text lastRecord;
};