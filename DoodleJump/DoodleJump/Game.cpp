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

void Game::playPlateSound(void)
{
	PlaySound(L"sounds/jump.wav", NULL, NULL);
}

void Game::playSpringSound(void)
{
	PlaySound(L"sounds/feder.wav", NULL, NULL);
}

void Game::playTrampolineSound(void)
{
	PlaySound(L"sounds/trampoline.wav", NULL, NULL);
}

void Game::playRocketSound(void)
{
	PlaySound(L"sounds/jetpack.wav", NULL, NULL);
}

void Game::playHatHelicopterSound(void)
{
	PlaySound(L"sounds/propeller.wav", NULL, NULL);
}

void Game::playStartGameSound(void)
{
	PlaySound(L"sounds/start.wav", NULL, NULL);
}

void Game::playGameOverSound(void)
{
	PlaySound(L"sounds/pada.wav", NULL, NULL);
}

void Game::gameLoop(sf::RenderWindow & window)
{
	SGameResult result;

	// TODO: do not use thread
	sf::Thread soundPlateThread(&Game::playPlateSound, this);
	sf::Thread soundSpringThread(&Game::playSpringSound, this);
	sf::Thread soundTrampolineThread(&Game::playTrampolineSound, this);
	sf::Thread soundRocketThread(&Game::playRocketSound, this);
	sf::Thread soundHatHelicopterThread(&Game::playHatHelicopterSound, this);
	sf::Thread soundStartGameThread(&Game::playStartGameSound, this);
	sf::Thread soundGameOverThread(&Game::playGameOverSound, this);

	while (window.isOpen())
	{
		switch (gameState.status)
		{
		case gameStatus::START_SCENE:
			result = sceneStart->onStartMenu(window);
			gameState.status = result.status; 
			if (result.status == gameStatus::GAME_SCENE)
			{
				soundStartGameThread.launch(); // TODO: ќбработчик снизу, вытащи вниз
			}
			else
			{
				if (result.status == gameStatus::HELP_SCENE)
				{
					gameState.status = gameStatus::HELP_SCENE;
				}
			}
			break;
		case gameStatus::GAME_SCENE:
			result = sceneGame->onGameFrame(window);
			if (result.status == gameStatus::GAME_SCENE)
			{
				gameState.status = gameStatus::GAME_SCENE;
			}
			else
			{
				if (result.status == gameStatus::GAME_OVER_SCENE)
				{
					gameState.status = gameStatus::GAME_OVER_SCENE;
					soundGameOverThread.launch(); // TODO: ќбработчик снизу, вытащи вниз
				}
				else
				{
					if (result.status == gameStatus::PAUSE_SCENE)
					{
						gameState.status = gameStatus::PAUSE_SCENE;
					}
				}
			}
			break;
		case gameStatus::GAME_OVER_SCENE:
			gameState = sceneGameOver->onGameOverMenu(window, result.points); // NOTE: не требует росписи на if'ы т.к. сразу в gameState присваиваетс€
			break;
		case gameStatus::PAUSE_SCENE:
			gameState = scenePause->onPauseMenu(window); // NOTE: не требует росписи на if'ы т.к. сразу в gameState присваиваетс€
			break;
		case gameStatus::HELP_SCENE:
			gameState = sceneHelp->onHelpMenu(window); // NOTE: не требует росписи на if'ы т.к. сразу в gameState присваиваетс€
			break;
		}

		// TODO: don't play sound here
		switch (result.collision)
		{
		case Collision::COLLISION_PLATE:
			soundPlateThread.launch();
			break;
		case Collision::COLLISION_SPRING:
			soundSpringThread.launch();
			break;
		case Collision::COLLISION_TRAMPLANE:
			soundTrampolineThread.launch();
			break;
		case Collision::COLLISION_ROCKET:
			soundRocketThread.launch();
			break;
		case Collision::COLLISION_HAT_HELICOPTER:
			soundHatHelicopterThread.launch();
			break;
		default:
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
