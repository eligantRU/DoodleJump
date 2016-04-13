#pragma once

#include "stdafx.h"
#include "sheet.h"

struct PauseScene
{
public:
	PauseScene(Assets & assets, sf::View & view);
	~PauseScene();
	SGameResult onPauseMenu(sf::RenderWindow & window);
private:
	Assets * assets;
	sf::View * view;
	void render(sf::RenderWindow & window);
	void checkEvents(sf::RenderWindow & window);
	void checkMouseOnButtons(sf::Vector2i & mousePosition);
	void checkMouseClick(sf::RenderWindow & window, sf::Event & event);
	void clearResult(void);
	sf::Sprite * background;
	sf::Sprite * backButton;
	sf::Sprite * exitButton;

	sf::Text backText;
	sf::Text exitText;

	SGameResult result;
};
