#include "stdafx.h"
#include "sheet.h"

Game::Game()
{
	assets = new Assets();
	view = new sf::View();
	sceneStart = new StartScene(*assets, *view);
	sceneHelp = new HelpScene(*assets, *view);
	sceneGame = new GameScene(*assets, *view);
	sceneGameOver = new GameOverScene(*assets, *view);
	scenePause = new PauseScene(*assets, *view);
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
		case GameStatus::START_SCENE:
			gameState = sceneStart->onStartMenu(window);
			break;
		case GameStatus::GAME_SCENE:
			gameState = sceneGame->onGameFrame(window);
			break;
		case GameStatus::GAME_OVER_SCENE:
			gameState = sceneGameOver->onGameOverMenu(window, gameState.points);
			break;
		case GameStatus::PAUSE_SCENE:
			gameState = scenePause->onPauseMenu(window);
			break;
		case GameStatus::HELP_SCENE:
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
	gameState.status = GameStatus::START_SCENE;

	gameLoop(window);
}
