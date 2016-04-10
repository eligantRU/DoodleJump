#pragma once

#include "stdafx.h"
#include "sheet.h"

struct pauseScene
{
public:
	pauseScene(Assets * assets, sf::View * view);
	~pauseScene();
	SGameResult onPauseMenu(sf::RenderWindow & window);
private:
	Assets * assets;
	sf::View * view;
	void render(sf::RenderWindow & window);
	void checkEvents(sf::RenderWindow & window);
	void checkMouseOnButtons(sf::Vector2i & mousePosition);
	void checkMouseClick(sf::RenderWindow & window, sf::Event & event);
	sf::Sprite * background;
	sf::Sprite * backButton;
	sf::Sprite * exitButton;

	sf::Text backText;
	sf::Text exitText;

	SGameResult result;
};
