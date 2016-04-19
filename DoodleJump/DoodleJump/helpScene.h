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
	
	std::unique_ptr<Assets> m_assets; //Assets * m_assets;
	std::unique_ptr<sf::View> m_view; //sf::View * m_view;

	std::unique_ptr<sf::Sprite> m_background; //sf::Sprite * m_background;
	std::unique_ptr<sf::Sprite> m_buttonA; //sf::Sprite * m_buttonA;
	std::unique_ptr<sf::Sprite> m_buttonD; //sf::Sprite * m_buttonD;

	sf::Text m_helpText1;
	sf::Text m_helpText2;

	std::unique_ptr<Button> m_goMenuButton; //Button * m_goMenuButton; 

	SGameResult m_result;
};