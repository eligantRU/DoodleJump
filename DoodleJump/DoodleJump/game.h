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
	sf::Sprite * playAgainButton;
	sf::Sprite * goMenuButton;
	sf::Sprite * title;

	sf::Text playAgainText;
	sf::Text goMenuText;
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

struct helpScene
{
public:
	helpScene();
	~helpScene();
	gameResult onHelpMenu(sf::RenderWindow & window);
private:
	sf::Sprite * background;
	sf::Sprite * goMenuButton;
	sf::Sprite * buttonA;
	sf::Sprite * buttonD;

	sf::Text goMenuText;
	sf::Text helpText1;
	sf::Text helpText2;
};

struct Game
{
public:
	Game();
	~Game();
	void launch(void);
private:
	startScene sceneStart;
	helpScene sceneHelp;
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
	void playRocketSound(void);
	void playHatHelicopterSound(void);
	void playStartGameSound(void);
	void playGameOverSound(void);
};