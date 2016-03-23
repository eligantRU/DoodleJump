#pragma once

#include "stdafx.h"
#include "sheet.h"

struct gameOverScene
{
public:
	gameOverScene();
	~gameOverScene();
	gameResult onGameOverMenu(sf::RenderWindow & window, uint64_t & score);
private:
	sf::Sprite * background;
	sf::Sprite * goMenuButton;
	sf::Sprite * exitButton;

	sf::Text goMenuText;
	sf::Text exitText;
	sf::Text lastRecord;
};

struct pauseScene
{
public:
	pauseScene();
	~pauseScene();
	gameResult onPauseMenu(sf::RenderWindow & window);
private:
	sf::Sprite * background;
	sf::Sprite * backButton;
	sf::Sprite * exitButton;

	sf::Text backText;
	sf::Text exitText;
};

struct Game
{
public:
	Game();
	~Game();
	void launch(void);
private:
	startScene sceneStart;
	gameScene sceneGame;
	gameOverScene sceneGameOver;
	pauseScene scenePause;
	typedef std::function<void(sf::RenderWindow & )> RenderFrameFunc;
	RenderFrameFunc frameFunc;
	std::vector<sf::Vector2f> platePosition;
	void gameLoop(sf::RenderWindow & window);
	gameResult status;
	void playPlateSound(void);
	void playSpringSound(void);
	void playTrampolineSound(void);
	void playGameOverSound(void);
	void playRocketSound(void);
	void playHatHelicopterSound(void);
};