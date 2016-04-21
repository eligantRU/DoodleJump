#include "stdafx.h"
#include "sheet.h"

StartScene::StartScene(Assets & assets, sf::View & view)
	:m_assets(&assets)
	,m_view(&view)
{
	m_hero = std::make_unique<Doodle>(*m_assets);
	m_plate = std::make_unique<Plate>(*m_assets);
	m_hero->setSpeedY(-20.f);
	m_hero->setTexture(m_assets->DOODLE_RIGHT_TEXTURE);
	m_hero->setPosition(sf::Vector2f(110.f, 500.f - DOODLE_HEIGHT));

	m_title = std::make_unique<sf::Sprite>();
	m_title->setTexture(m_assets->MAIN_TITLE_TEXTURE);
	m_title->setPosition(100, 50);
	
	m_playButton = std::make_unique<Button>("Play", sf::Vector2f(232.f, 182.f), *m_assets);
	m_exitButton = std::make_unique<Button>("Exit", sf::Vector2f(250.f, 240.f), *m_assets);
	m_helpButton = std::make_unique<Button>("Help", sf::Vector2f(350.f, 475.f), *m_assets);

	m_hole = std::make_unique<sf::Sprite>();
	m_hole->setTexture(m_assets->HOLE_TEXTURE);
	m_hole->setPosition(300, 350);
	m_hole->setScale(sf::Vector2f(1.25f, 1.25f));

	m_insects[0] = std::make_unique<sf::Sprite>();
	m_insects[0]->setTexture(m_assets->GARBAGE_1_TEXTURE);
	m_insects[0]->setPosition(450, 250);
	m_insects[1] = std::make_unique<sf::Sprite>();
	m_insects[1]->setTexture(m_assets->GARBAGE_2_TEXTURE);
	m_insects[1]->setPosition(300, 300);
	m_insects[2] = std::make_unique<sf::Sprite>();
	m_insects[2]->setTexture(m_assets->GARBAGE_3_TEXTURE);
	m_insects[2]->setPosition(210, 215);
	m_insects[3] = std::make_unique<sf::Sprite>();
	m_insects[3]->setTexture(m_assets->GARBAGE_4_TEXTURE);
	m_insects[3]->setPosition(50, 50);
	m_insects[4] = std::make_unique<sf::Sprite>();
	m_insects[4]->setTexture(m_assets->GARBAGE_5_TEXTURE);
	m_insects[4]->setPosition(400, 400);

	m_background = std::make_unique<sf::Sprite>();
	m_background->setTextureRect(sf::IntRect(0, 0, 550, 700));
	m_background->setTexture(m_assets->BACKGROUND_TEXTURE);
	m_background->setPosition(0, 0);

	m_plate->setPosition(sf::Vector2f(100.f, 500.f));
}

StartScene::~StartScene()
{
	*m_insects = nullptr;
	m_hero = nullptr;
	m_plate = nullptr;
	m_hole = nullptr;
	m_title = nullptr;
	m_playButton = nullptr;
	m_exitButton = nullptr;
	m_helpButton = nullptr;
	m_background = nullptr;
}

SGameResult StartScene::onStartMenu(sf::RenderWindow & window)
{
	clearResult();

	moveDoodle();
	checkEvents(window);
	render(window);
	window.display();

	return result;
}

void StartScene::clearResult(void)
{
	result.status = GameStatus::START_SCENE;
}

void StartScene::render(sf::RenderWindow & window)
{
	window.clear(sf::Color(255, 255, 255));
	window.draw(*m_background);
	window.draw(*m_title);
	m_plate->draw(window);
	m_hero->draw(window);
	m_playButton->draw(window);
	m_exitButton->draw(window);
	m_helpButton->draw(window);
	window.draw(*m_hole);

	for (auto &insect : m_insects)
	{
		window.draw(*insect);
	}
}

void StartScene::checkMouseOnButtons(sf::Vector2i mousePosition)
{
	m_playButton->onMouse(mousePosition);
	m_exitButton->onMouse(mousePosition);
	m_helpButton->onMouse(mousePosition);
}

void StartScene::checkMouseClick(sf::RenderWindow & window, sf::Event & event)
{
	if (m_playButton->onClick(event))
	{
		result.status = GameStatus::GAME_SCENE;
	}
	if (m_exitButton->onClick(event))
	{
		window.close();
	}
	if (m_helpButton->onClick(event))
	{
		result.status = GameStatus::HELP_SCENE;
	}
}

void StartScene::checkEvents(sf::RenderWindow & window)
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

void StartScene::moveDoodle(void)
{
	sf::Vector2f position(0.f, 0.f);
	if (m_hero->getSpeedY() < 0)
	{
		m_hero->setSpeedY(m_hero->getSpeedY() + ACCELERATION);
		position.y = m_hero->getSpeedY();

		m_hero->setTexture(m_assets->DOODLE_JUMP_RIGHT_TEXTURE);
	}
	else
	{
		if (checkCollisionPlate() == Collision::NO_COLLISION)
		{
			m_hero->setSpeedY(m_hero->getSpeedY() + ACCELERATION / 8);
			position.y = m_hero->getSpeedY();

			m_hero->setTexture(m_assets->DOODLE_RIGHT_TEXTURE);
		}
		else
		{
			m_hero->setSpeedY(-PLATE_DELTA_HEIGHT);
		}
	}
	m_hero->move(position);
}

Collision StartScene::checkCollisionPlate(void)
{
	sf::Vector2f doodlePosition = m_hero->getPosition();
	sf::Vector2f platePosition = m_plate->getPosition();

	if (((doodlePosition.y + DOODLE_HEIGHT >= platePosition.y) && (doodlePosition.y + DOODLE_HEIGHT <= platePosition.y + PLATE_HEIGHT)
		&& (doodlePosition.x + DOODLE_WIDTH >= platePosition.x) && (doodlePosition.x - PLATE_WIDTH <= platePosition.x)))
	{
		PlaySound(L"sounds/jump.wav", nullptr, SND_ASYNC | SND_NODEFAULT);
		return  Collision::COLLISION_PLATE;
	}
	return Collision::NO_COLLISION;
}