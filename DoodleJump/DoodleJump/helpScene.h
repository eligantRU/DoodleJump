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
	
	Assets & m_assets;
	sf::View & m_view;

	std::unique_ptr<sf::Sprite> m_background;
	std::unique_ptr<sf::Sprite> m_buttonA;
	std::unique_ptr<sf::Sprite> m_buttonD;

	std::unique_ptr<Button> m_goMenuButton;

	sf::Text m_helpText1;
	sf::Text m_helpText2;

	SGameResult m_result;
};