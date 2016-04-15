#pragma once

#include "stdafx.h"
#include "sheet.h"

struct HelpScene
{
public:
	HelpScene(Assets & assets, sf::View & view);
	~HelpScene();
	SGameResult onHelpMenu(sf::RenderWindow & window);
private:
	Assets * assets;
	sf::View * view;
	void render(sf::RenderWindow & window);
	void checkEvents(sf::RenderWindow & window);
	void checkMouseOnButtons(sf::Vector2i & mousePosition);
	void checkMouseClick(sf::RenderWindow & window, sf::Event & event);
	void clearResult(void);

	sf::Sprite * background;
	sf::Sprite * buttonA;
	sf::Sprite * buttonD;

	sf::Text helpText1;
	sf::Text helpText2;

	Button * goMenuButton;

	SGameResult result;
};