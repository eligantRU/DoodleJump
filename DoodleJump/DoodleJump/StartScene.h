#pragma once

#include "stdafx.h"
#include "sheet.h"

class StartScene
{
public:
	StartScene(Assets & assets, sf::View & view, SoundHandler & soundHandler);
	~StartScene();
	SGameResult onStartMenu(sf::RenderWindow & window);
private:
	Collision checkCollisionPlates() const;
	void render(sf::RenderWindow & window) const;
	void checkEvents(sf::RenderWindow & window);
	void checkMouseOnButtons(sf::Vector2i mousePosition);
	void checkMouseClick(sf::RenderWindow & window, sf::Event & event);
	void clearResult();
	void moveDoodle();

	Assets & m_assets;
	sf::View & m_view;
	SoundHandler & m_soundHandler;

	std::unique_ptr<Plate> m_plate;
	std::unique_ptr<Doodle> m_hero;

	std::unique_ptr<sf::Sprite> m_title;
	std::array<std::unique_ptr<sf::Sprite>, NUMBER_INSECTS> m_insects;
	std::unique_ptr<sf::Sprite> m_background;
	std::unique_ptr<sf::Sprite> m_hole;

	std::unique_ptr<Button> m_playButton;
	std::unique_ptr<Button> m_exitButton;
	std::unique_ptr<Button> m_helpButton;

	SGameResult result;
};