#pragma once

#include "stdafx.h"
#include "sheet.h"

struct startScene
{
public:
	startScene();
	~startScene();
	gameResult onStartMenu(sf::RenderWindow & window);
private:
	Collision checkCollisionPlate(void);
	void moveDoodle(void);
	Plate plate;
	Doodle hero;
	sf::Sprite * title;
	sf::Sprite * insects[NUMBER_INSECTS];
	sf::Sprite * background;
	sf::Sprite * playButton;
	sf::Sprite * exitButton;
	sf::Sprite * helpButton;
	sf::Sprite * hole;
	sf::Vector2f platePosition;
	sf::Vector2f doodlePosition;

	sf::Text playText;
	sf::Text recordText;
	sf::Text exitText;
	sf::Text helpText;

	gameResult result;
};