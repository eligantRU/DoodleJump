#pragma once

#include "stdafx.h"
#include "sheet.h"

struct helpScene
{
public:
	helpScene();
	~helpScene();
	gameResult onHelpMenu(sf::RenderWindow & window);
private:
	void render(sf::RenderWindow & window);
	void checkEvents(sf::RenderWindow & window);
	void checkMouseOnButtons(sf::Vector2i & mousePosition);
	void checkMouseClick(sf::RenderWindow & window, sf::Event & event, sf::Vector2i & mousePosition);

	sf::Sprite * background;
	sf::Sprite * goMenuButton;
	sf::Sprite * buttonA;
	sf::Sprite * buttonD;

	sf::Text goMenuText;
	sf::Text helpText1;
	sf::Text helpText2;

	gameResult result;
};