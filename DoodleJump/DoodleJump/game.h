#pragma once

#include "stdafx.h"
#include "sheet.h"

struct Game
{
public:
	Game();
	~Game();
	void launch();
private:
	void gameLoop(sf::RenderWindow & window);

	std::unique_ptr<Assets> m_assets;
	std::unique_ptr<sf::View> m_view;
	std::unique_ptr<SoundHandler> m_soundHandler;

	std::unique_ptr<StartScene> m_sceneStart;
	std::unique_ptr<HelpScene> m_sceneHelp;
	std::unique_ptr<PauseScene> m_scenePause;
	std::shared_ptr<GameScene> m_sceneGame;
	std::unique_ptr<GameOverScene> m_sceneGameOver;

	//RenderFrameFunc frameFunc;

	SGameResult m_gameState;
};