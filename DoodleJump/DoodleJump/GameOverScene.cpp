#include "stdafx.h"
#include "sheet.h"

GameOverScene::GameOverScene(Assets & assets, sf::View & view)
	:assets(&assets)
	,view(&view)
{
	title = new sf::Sprite;
	title->setTextureRect(sf::IntRect(0, 0, 236, 96));
	title->setTexture(assets.GAME_OVER_TITLE_TEXTURE);
	title->setPosition(150, 30);

	goMenuButton = new Button("Menu", sf::Vector2f(200.f, 210.f), assets);
	playAgainButton = new Button("Play", sf::Vector2f(250.f, 270.f), assets);

	lastRecord.setFont(assets.font);
	lastRecord.setCharacterSize(24);
	lastRecord.setStyle(sf::Text::Bold);
	lastRecord.setPosition(190.f, 150.f);
	lastRecord.setColor(sf::Color(0, 0, 0));

	background = new sf::Sprite;
	background->setTextureRect(sf::IntRect(0, 0, 550, 700));
	background->setTexture(assets.BACKGROUND_TEXTURE);
	background->setPosition(0, 0);
}

GameOverScene::~GameOverScene()
{
	delete background;
	delete goMenuButton;
	delete playAgainButton;
	background = nullptr;
	goMenuButton = nullptr;
	playAgainButton = nullptr;
}

SGameResult GameOverScene::onGameOverMenu(sf::RenderWindow & window, uint64_t & score)
{
	result.status = GameStatus::GAME_OVER_SCENE;
	result.collision = Collision::NO_COLLISION;
	result.points = score;
	lastRecord.setString("Your record: " + std::to_string(score));

	render(window);
	window.display();

	checkEvents(window);
	return result;
}

void GameOverScene::render(sf::RenderWindow & window)
{
	window.clear(sf::Color(255, 255, 255));
	window.draw(*background);
	window.draw(*title);
	goMenuButton->draw(window);
	playAgainButton->draw(window);
	window.draw(lastRecord);
}

void GameOverScene::checkEvents(sf::RenderWindow & window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		checkMouseOnButtons(sf::Mouse::getPosition(window));
		checkMouseClick(event);
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
	}
}

void GameOverScene::checkMouseOnButtons(sf::Vector2i & mousePosition)
{
	goMenuButton->onMouse(mousePosition);
	playAgainButton->onMouse(mousePosition);
}

void GameOverScene::checkMouseClick(sf::Event & event)
{
	if (goMenuButton->onClick(event))
	{
		result.status = GameStatus::START_SCENE;
	}

	if (playAgainButton->onClick(event))
	{
		result.status = GameStatus::GAME_SCENE;
	}
}

