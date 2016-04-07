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
	void render(sf::RenderWindow & window);
	void checkEvents(sf::RenderWindow & window);
	void checkMouseOnButtons(sf::Vector2i & mousePosition);
	void checkMouseClick(sf::RenderWindow & window, sf::Event & event, sf::Vector2i & mousePosition);
	sf::Sprite * background;
	sf::Sprite * backButton;
	sf::Sprite * exitButton;

	sf::Text backText;
	sf::Text exitText;

	gameResult result;
};
