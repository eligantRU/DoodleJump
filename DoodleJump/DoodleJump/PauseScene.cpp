#include "stdafx.h"
#include "sheet.h"

PauseScene::PauseScene(Assets & assets, sf::View & view)
	:m_assets(&assets)
	, m_view(&view)
{
	m_backButton = new Button("Back", sf::Vector2f(200.f, 210.f), *m_assets);
	m_exitButton = new Button("Exit", sf::Vector2f(250.f, 270.f), *m_assets);

	m_background = new sf::Sprite;
	m_background->setTextureRect(sf::IntRect(0, 0, 550, 700));
	m_background->setPosition(0.f, 0.f);
	m_background->setTexture(m_assets->BACKGROUND_TEXTURE);
}

PauseScene::~PauseScene()
{
	delete m_background;
	delete m_backButton;
	delete m_exitButton;
	m_background = nullptr;
	m_backButton = nullptr;
	m_exitButton = nullptr;
}

SGameResult PauseScene::onPauseMenu(sf::RenderWindow & window) 
{	
	clearResult();
	checkEvents(window);
	render(window);
	window.display();
	return m_result;
}

void PauseScene::clearResult(void)
{
	m_result.status = GameStatus::PAUSE_SCENE;
	m_result.collision = Collision::NO_COLLISION;
	m_result.points = 0;
}

void PauseScene::render(sf::RenderWindow & window)
{
	window.clear(sf::Color(255, 255, 255));
	window.draw(*m_background);
	m_backButton->draw(window);
	m_exitButton->draw(window);
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
	m_backButton->onMouse(mousePosition);
	m_exitButton->onMouse(mousePosition);
}

void PauseScene::checkMouseClick(sf::RenderWindow & window, sf::Event & event)
{
	if (m_backButton->onClick(event))
	{
		m_result.status = GameStatus::GAME_SCENE;
	}
	if (m_exitButton->onClick(event))
	{
		window.close();
	}
}
