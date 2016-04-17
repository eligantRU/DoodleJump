#pragma once

#include "stdafx.h"
#include "sheet.h"

struct GameOverScene
{
public:
	GameOverScene(Assets & assets, sf::View & view);
	~GameOverScene();
	SGameResult onGameOverMenu(sf::RenderWindow & window, uint64_t & score);
private:
	Assets * assets;
	sf::View * view;
	void render(sf::RenderWindow & window);
	void checkEvents(sf::RenderWindow & window);
	void checkMouseOnButtons(sf::Vector2i mousePosition);
	void checkMouseClick(sf::Event & event);

	sf::Sprite * background;
	sf::Sprite * title;

	sf::Text lastRecord;

	Button * playAgainButton;
	Button * goMenuButton;

	SGameResult result;
};
