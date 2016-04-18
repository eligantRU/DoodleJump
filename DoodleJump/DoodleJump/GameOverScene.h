#pragma once

#include "stdafx.h"
#include "sheet.h"

struct GameOverScene
{
public:
	GameOverScene(Assets & assets, sf::View & view, std::function<uint64_t()> getter);
	~GameOverScene();
	SGameResult onGameOverMenu(sf::RenderWindow & window);
private:
	Assets * assets;
	sf::View * view;
	void render(sf::RenderWindow & window);
	void checkEvents(sf::RenderWindow & window);
	void checkMouseOnButtons(sf::Vector2i mousePosition);
	void checkMouseClick(sf::Event & event);
	std::function<uint64_t()> m_getter;

	sf::Sprite * background;
	sf::Sprite * title;
	uint64_t m_score;

	sf::Text lastRecord;

	Button * playAgainButton;
	Button * goMenuButton;

	SGameResult result;
};
