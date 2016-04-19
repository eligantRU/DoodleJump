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
	void render(sf::RenderWindow & window);
	void checkEvents(sf::RenderWindow & window);
	void checkMouseOnButtons(sf::Vector2i mousePosition);
	void checkMouseClick(sf::RenderWindow & window, sf::Event & event);
	void clearResult(void);

	Assets * m_assets;
	sf::View * m_view;

	sf::Sprite * m_background;

	Button * m_backButton;
	Button * m_exitButton;

	SGameResult m_result;
};
