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
	void render(sf::RenderWindow & window);
	void checkEvents(sf::RenderWindow & window);
	void checkMouseOnButtons(sf::Vector2i mousePosition);
	void checkMouseClick(sf::RenderWindow & window, sf::Event & event);
	void clearResult(void);
	
	Assets * m_assets;
	sf::View * m_view;

	sf::Sprite * m_background;
	sf::Sprite * m_buttonA;
	sf::Sprite * m_buttonD;

	sf::Text m_helpText1;
	sf::Text m_helpText2;

	Button * m_goMenuButton;

	SGameResult m_result;
};