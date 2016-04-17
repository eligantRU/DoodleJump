#include "stdafx.h"
#include "sheet.h"

PauseScene::PauseScene(Assets & assets, sf::View & view)
	:assets(&assets)
	,view(&view)
{
	backButton = new Button("Back", sf::Vector2f(200.f, 210.f), assets);
	exitButton = new Button("Exit", sf::Vector2f(250.f, 270.f), assets);

	background = new sf::Sprite;
	background->setTextureRect(sf::IntRect(0, 0, 550, 700));
	background->setPosition(0.f, 0.f);
	background->setTexture(assets.BACKGROUND_TEXTURE);
}

PauseScene::~PauseScene()
{
	delete background;
	delete backButton;
	delete exitButton;
	background = nullptr;
	backButton = nullptr;
	exitButton = nullptr;
}

SGameResult PauseScene::onPauseMenu(sf::RenderWindow & window) 
{	
	clearResult();
	checkEvents(window);
	render(window);
	window.display();
	return result;
}

void PauseScene::clearResult(void)
{
	result.status = GameStatus::PAUSE_SCENE;
	result.collision = Collision::NO_COLLISION;
	result.points = 0;
}

void PauseScene::render(sf::RenderWindow & window)
{
	window.clear(sf::Color(255, 255, 255));
	window.draw(*background);
	backButton->draw(window);
	exitButton->draw(window);
}

void PauseScene::checkEvents(sf::RenderWindow & window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		checkMouseOnButtons(sf::Mouse::getPosition(window));
		checkMouseClick(window, event);
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
	}
}

void PauseScene::checkMouseOnButtons(sf::Vector2i mousePosition)
{
	backButton->onMouse(mousePosition);
	exitButton->onMouse(mousePosition);
}

void PauseScene::checkMouseClick(sf::RenderWindow & window, sf::Event & event)
{
	if (backButton->onClick(event))
	{
		result.status = GameStatus::GAME_SCENE;
	}
	if (exitButton->onClick(event))
	{
		window.close();
	}
}
