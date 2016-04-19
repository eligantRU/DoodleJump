#pragma once

#include "stdafx.h"
#include "sheet.h"

struct StartScene
{
public:
	StartScene(Assets & assets, sf::View & view);
	~StartScene();
	SGameResult onStartMenu(sf::RenderWindow & window);
private:
	Collision checkCollisionPlate(void);
	void render(sf::RenderWindow & window);
	void checkEvents(sf::RenderWindow & window);
	void checkMouseOnButtons(sf::Vector2i mousePosition);
	void checkMouseClick(sf::RenderWindow & window, sf::Event & event);
	void clearResult(void);
	void moveDoodle(void);

	Assets * m_assets;
	sf::View * m_view;

	Plate * m_plate;
	Doodle * m_hero;

	sf::Sprite * m_title;
	sf::Sprite * m_insects[NUMBER_INSECTS];
	sf::Sprite * m_background;
	sf::Sprite * m_hole;

	Button * m_playButton;
	Button * m_exitButton;
	Button * m_helpButton;

	SGameResult result;
};