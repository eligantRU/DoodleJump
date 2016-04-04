#pragma once

#include "stdafx.h"
#include "sheet.h"

struct pauseScene
{
public:
	pauseScene();
	~pauseScene();
	gameResult onPauseMenu(sf::RenderWindow & window);
private:
	sf::Sprite * background;
	sf::Sprite * backButton;
	sf::Sprite * exitButton;

	sf::Text backText;
	sf::Text exitText;
};
