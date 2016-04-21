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

	std::unique_ptr<Assets> m_assets;
	std::unique_ptr<sf::View> m_view;

	std::unique_ptr<sf::Sprite> m_background;

	std::unique_ptr<Button> m_backButton;
	std::unique_ptr<Button> m_exitButton;

	SGameResult m_result;
};
