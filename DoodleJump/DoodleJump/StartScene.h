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

	std::unique_ptr<Assets> m_assets; //Assets * m_assets;
	std::unique_ptr<sf::View> m_view; //sf::View * m_view;

	std::unique_ptr<Plate> m_plate; //Plate * m_plate;
	std::unique_ptr<Doodle> m_hero; //Doodle * m_hero;

	std::unique_ptr<sf::Sprite> m_title; //sf::Sprite * m_title;
	std::unique_ptr<sf::Sprite> m_insects[NUMBER_INSECTS]; //sf::Sprite * m_insects[NUMBER_INSECTS];
	std::unique_ptr<sf::Sprite> m_background; //sf::Sprite * m_background;
	std::unique_ptr<sf::Sprite> m_hole; //sf::Sprite * m_hole;

	std::unique_ptr<Button> m_playButton; //Button * m_playButton;
	std::unique_ptr<Button> m_exitButton; //Button * m_exitButton;
	std::unique_ptr<Button> m_helpButton; //Button * m_helpButton;

	SGameResult result;
};