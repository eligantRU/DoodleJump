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

	std::unique_ptr<Assets> m_assets;
	std::unique_ptr<sf::View> m_view;

	StartScene * m_sceneStart;
	HelpScene * m_sceneHelp;
	GameScene * m_sceneGame;
	GameOverScene * m_sceneGameOver;
	PauseScene * m_scenePause;
/*	std::unique_ptr<StartScene> m_sceneStart;
	std::unique_ptr<HelpScene> m_sceneHelp;
	std::shared_ptr<GameScene> m_sceneGame;
	std::unique_ptr<GameOverScene> m_sceneGameOver;
	std::unique_ptr<PauseScene> m_scenePause;*/

	//typedef std::function<void(sf::RenderWindow & )> RenderFrameFunc;
	//RenderFrameFunc frameFunc;

	SGameResult m_gameState;
};