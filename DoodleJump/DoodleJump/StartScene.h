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
	Assets * assets;
	sf::View * view;
	void render(sf::RenderWindow & window);
	void checkEvents(sf::RenderWindow & window);
	void checkMouseOnButtons(sf::Vector2i & mousePosition);
	void checkMouseClick(sf::RenderWindow & window, sf::Event & event);
	void clearResult(void);
	Collision checkCollisionPlate(void);
	void moveDoodle(void);
	Plate * plate;
	Doodle * hero;
	sf::Sprite * title;
	sf::Sprite * insects[NUMBER_INSECTS];
	sf::Sprite * background;
	sf::Sprite * hole;
	sf::Vector2f platePosition;
	sf::Vector2f doodlePosition;

	Button * playButton;
	Button * exitButton;
	Button * helpButton;

	SGameResult result;
};