#pragma once

#include "stdafx.h"
#include "sheet.h"

struct Game
{
public:
	Game();
	~Game();
	void launch(void);
private:
	void gameLoop(sf::RenderWindow & window);

	Assets * m_assets;
	sf::View * m_view;

	StartScene * m_sceneStart;
	HelpScene * m_sceneHelp;
	GameScene * m_sceneGame;
	GameOverScene * m_sceneGameOver;
	PauseScene * m_scenePause;
	//typedef std::function<void(sf::RenderWindow & )> RenderFrameFunc;
	//RenderFrameFunc frameFunc;

	SGameResult m_gameState;
};