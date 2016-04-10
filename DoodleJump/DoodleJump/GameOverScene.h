#pragma once

#include "stdafx.h"
#include "sheet.h"

struct gameOverScene
{
public:
	gameOverScene(Assets * assets, sf::View * view);
	~gameOverScene();
	SGameResult onGameOverMenu(sf::RenderWindow & window, uint64_t & score);
private:
	Assets * assets;
	sf::View * view;
	void render(sf::RenderWindow & window);
	void checkEvents(sf::RenderWindow & window);
	void checkMouseOnButtons(sf::Vector2i & mousePosition);
	void checkMouseClick(sf::RenderWindow & window, sf::Event & event);

	sf::Sprite * background;
	sf::Sprite * playAgainButton;
	sf::Sprite * goMenuButton;
	sf::Sprite * title;

	sf::Text playAgainText;
	sf::Text goMenuText;
	sf::Text lastRecord;

	SGameResult result;
};
