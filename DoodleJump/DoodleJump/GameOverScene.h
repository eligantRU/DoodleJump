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
	void render(sf::RenderWindow & window);
	void checkEvents(sf::RenderWindow & window);
	void checkMouseOnButtons(sf::Vector2i mousePosition);
	void checkMouseClick(sf::Event & event);
	std::function<uint64_t()> m_getter;

	Assets * m_assets;
	sf::View * m_view;

	sf::Sprite * m_background;
	sf::Sprite * m_title;

	uint64_t m_score;
	sf::Text m_lastRecord;

	Button * m_playAgainButton;
	Button * m_goMenuButton;

	SGameResult m_result;
};
