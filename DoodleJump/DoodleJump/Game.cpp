#include "stdafx.h"
#include "sheet.h"

Game::Game()
{
	assets = new Assets();
	view = new sf::View();
	sceneStart = new startScene(assets, view);
	sceneHelp = new helpScene(assets, view);
	sceneGame = new gameScene(assets, view);
	sceneGameOver = new gameOverScene(assets, view);
	scenePause = new pauseScene(assets, view);
}

Game::~Game()
{
	
}

/*void Game::gameLoop(sf::RenderWindow & window)
{
	while (window.isOpen())
	{
		frameFunc(window);
	}
}*/

void Game::gameLoop(sf::RenderWindow & window)
{
	while (window.isOpen())
	{
		switch (gameState.status)
		{
		case gameStatus::START_SCENE:
			gameState = sceneStart->onStartMenu(window);
			break;
		case gameStatus::GAME_SCENE:
			gameState = sceneGame->onGameFrame(window);
			break;
		case gameStatus::GAME_OVER_SCENE:
			gameState = sceneGameOver->onGameOverMenu(window, gameState.points);
			break;
		case gameStatus::PAUSE_SCENE:
			gameState = scenePause->onPauseMenu(window);
			break;
		case gameStatus::HELP_SCENE:
			gameState = sceneHelp->onHelpMenu(window);
			break;
		}
	}
}

void Game::launch(void)
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;
	sf::RenderWindow window(sf::VideoMode(550, 700), "Doodle Jump", sf::Style::Close, settings);
	sf::Image icon = assets->ICON;;
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	view->reset(sf::FloatRect(0, 0, 550, 700));
	view->setCenter(275, 350);
	window.setView(*view);
	gameState.status = gameStatus::START_SCENE;

	gameLoop(window);
}
