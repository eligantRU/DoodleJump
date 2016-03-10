#pragma once

#include "stdafx.h"
#include "sheet.h"

struct pauseScene : public Game
{
public:
	pauseScene();
	~pauseScene();
protected:
	virtual void onPauseMenu(sf::RenderWindow & windowm, sf::View & view);
private:
	sf::Sprite * background;
	sf::Sprite * backButton;
	sf::Sprite * exitButton;

	sf::Text backText;
	sf::Text exitText;
};