#include "stdafx.h"
#include "sheet.h"

Game::Game()
{
	
}

Game::~Game()
{
	// TODO: прибери за собой
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
	gameResult result;

	sf::Thread soundPlateThread(&Game::playPlateSound, this);
	sf::Thread soundSpringThread(&Game::playSpringSound, this);
	sf::Thread soundTrampolineThread(&Game::playTrampolineSound, this);
	sf::Thread soundRocketThread(&Game::playRocketSound, this);
	sf::Thread soundHatHelicopterThread(&Game::playHatHelicopterSound, this);
	sf::Thread soundStartGameThread(&Game::playStartGameSound, this);
	sf::Thread soundGameOverThread(&Game::playGameOverSound, this);

	while (window.isOpen())
	{
		switch (status.gameStatus)
		{
		case statusGame::START_SCENE:
			result = sceneStart.onStartMenu(window);
			status.gameStatus = result.gameStatus; 
			if (result.gameStatus == statusGame::GAME_SCENE)
			{
				soundStartGameThread.launch(); // TODO: Обработчик снизу, вытащи вниз
			}
			else
			{
				if (result.gameStatus == statusGame::HELP_SCENE)
				{
					status.gameStatus = statusGame::HELP_SCENE;
				}
			}
			break;
		case statusGame::GAME_SCENE:
			result = sceneGame.onGameFrame(window);
			if (result.gameStatus == statusGame::GAME_SCENE)
			{
				status.gameStatus = statusGame::GAME_SCENE;
			}
			else
			{
				if (result.gameStatus == statusGame::GAME_OVER_SCENE)
				{
					status.gameStatus = statusGame::GAME_OVER_SCENE;
					soundGameOverThread.launch(); // TODO: Обработчик снизу, вытащи вниз
				}
				else
				{
					if (result.gameStatus == statusGame::PAUSE_SCENE)
					{
						status.gameStatus = statusGame::PAUSE_SCENE;
					}
				}
			}
			break;
		case statusGame::GAME_OVER_SCENE:
			status = sceneGameOver.onGameOverMenu(window, result.points); // NOTE: не требует росписи на if'ы т.к. сразу в status присваивается
			break;
		case statusGame::PAUSE_SCENE:
			status = scenePause.onPauseMenu(window); // NOTE: не требует росписи на if'ы т.к. сразу в status присваивается
			break;
		case statusGame::HELP_SCENE:
			status = sceneHelp.onHelpMenu(window); // NOTE: не требует росписи на if'ы т.к. сразу в status присваивается
			break;
		}

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
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	view.reset(sf::FloatRect(0, 0, 550, 700));
	view.setCenter(275, 350);
	window.setView(view);
	status.gameStatus = statusGame::START_SCENE;

	gameLoop(window);
}
