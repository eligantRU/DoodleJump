#include "stdafx.h"
#include "sheet.h"

Game::Game()
{
	assets = new Assets();
}

Game::~Game()
{
	delete assets;
	assets = NULL;
}

void Game::gameLoop(sf::RenderWindow & window)
{
	while (window.isOpen())
	{
		frameFunc(window);
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

	startScene scene;
	Game * kostil = & scene;

	while (window.isOpen()) 
	{
		kostil->onStartMenu(window);
	}
}
