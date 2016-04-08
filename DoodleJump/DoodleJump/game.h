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
	Assets * assets;
	sf::View * view;
	startScene * sceneStart;
	helpScene * sceneHelp;
	gameScene * sceneGame;
	gameOverScene * sceneGameOver;
	pauseScene * scenePause;
	typedef std::function<void(sf::RenderWindow & )> RenderFrameFunc;
	RenderFrameFunc frameFunc;
	std::vector<sf::Vector2f> platePosition;
	void gameLoop(sf::RenderWindow & window);
	void playPlateSound(void);
	void playSpringSound(void);
	void playTrampolineSound(void);
	void playRocketSound(void);
	void playHatHelicopterSound(void);
	void playStartGameSound(void);
	void playGameOverSound(void);

	SGameResult gameState;
};