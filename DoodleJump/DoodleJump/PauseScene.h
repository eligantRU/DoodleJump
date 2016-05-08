#pragma once

#include "stdafx.h"
#include "sheet.h"

struct PauseScene
{
public:
	PauseScene(Assets & assets, sf::View & view, SoundHandler & soundHandler);
	~PauseScene();
	SGameResult onPauseMenu(sf::RenderWindow & window);
private:
	void render(sf::RenderWindow & window) const;
	void checkEvents(sf::RenderWindow & window);
	void checkMouseOnButtons(sf::Vector2i mousePosition);
	void checkMouseClick(sf::RenderWindow & window, sf::Event & event);
	void clearResult();

	Assets & m_assets;
	sf::View & m_view;
	SoundHandler & m_soundHandler;

	std::unique_ptr<sf::Sprite> m_background;

	std::unique_ptr<Button> m_backButton;
	std::unique_ptr<Button> m_exitButton;

	SGameResult m_result;
};
