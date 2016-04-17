#include "stdafx.h"
#include "sheet.h"

StartScene::StartScene(Assets & assets, sf::View & view)
	:assets(&assets)
	,view(&view)
{
	hero = new Doodle(assets);
	plate = new Plate(&assets);
	hero->setSpeedY(-20.f);
	hero->setTexture(assets.DOODLE_RIGHT_TEXTURE);
	hero->setPosition(sf::Vector2f(110.f, 500.f - DOODLE_HEIGHT));

	title = new sf::Sprite;
	title->setTexture(assets.MAIN_TITLE_TEXTURE);
	title->setPosition(100, 50);
	
	playButton = new Button("Play", sf::Vector2f(232.f, 182.f), assets);
	exitButton = new Button("Exit", sf::Vector2f(250.f, 240.f), assets);
	helpButton = new Button("Help", sf::Vector2f(350.f, 475.f), assets);

	title = new sf::Sprite;
	title->setTexture(assets.MAIN_TITLE_TEXTURE);
	title->setPosition(100, 50);

	hole = new sf::Sprite;
	hole->setTexture(assets.HOLE_TEXTURE);
	hole->setPosition(300, 350);
	hole->setScale(sf::Vector2f(1.25f, 1.25f));

	insects[0] = new sf::Sprite;
	insects[0]->setTexture(assets.GARBAGE_1_TEXTURE);
	insects[0]->setPosition(450, 250);
	insects[1] = new sf::Sprite;
	insects[1]->setTexture(assets.GARBAGE_2_TEXTURE);
	insects[1]->setPosition(300, 300);
	insects[2] = new sf::Sprite;
	insects[2]->setTexture(assets.GARBAGE_3_TEXTURE);
	insects[2]->setPosition(210, 215);
	insects[3] = new sf::Sprite;
	insects[3]->setTexture(assets.GARBAGE_4_TEXTURE);
	insects[3]->setPosition(50, 50);
	insects[4] = new sf::Sprite;
	insects[4]->setTexture(assets.GARBAGE_5_TEXTURE);
	insects[4]->setPosition(400, 400);

	background = new sf::Sprite;
	background->setTextureRect(sf::IntRect(0, 0, 550, 700));
	background->setTexture(assets.BACKGROUND_TEXTURE);
	background->setPosition(0, 0);

	plate->setPosition(sf::Vector2f(100.f, 500.f));
}

StartScene::~StartScene()
{
	delete title;
	delete *insects;
	delete playButton;
	delete exitButton;
	delete hole;
	title = nullptr;
	*insects = nullptr;
	playButton = nullptr;
	exitButton = nullptr;
	hole = nullptr;
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
	result.collision = Collision::NO_COLLISION;
	result.points = 0;
}

void StartScene::render(sf::RenderWindow & window)
{
	window.clear(sf::Color(255, 255, 255));
	window.draw(*background);
	window.draw(*title);
	plate->draw(window);
	hero->draw(window);
	playButton->draw(window);
	exitButton->draw(window);
	helpButton->draw(window);
	window.draw(*hole);

	for (auto insect : insects)
	{
		window.draw(*insect);
	}
}

void StartScene::checkMouseOnButtons(sf::Vector2i mousePosition)
{
	playButton->onMouse(mousePosition);
	exitButton->onMouse(mousePosition);
	helpButton->onMouse(mousePosition);
}

void StartScene::checkMouseClick(sf::RenderWindow & window, sf::Event & event)
{
	if (playButton->onClick(event))
	{
		result.status = GameStatus::GAME_SCENE;
	}
	if (exitButton->onClick(event))
	{
		window.close();
	}
	if (helpButton->onClick(event))
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
	doodlePosition = hero->getPosition();

	sf::Vector2f position(0.f, 0.f);
	if (hero->getSpeedY() < 0)
	{
		hero->setSpeedY(hero->getSpeedY() + ACCELERATION);
		position.y = hero->getSpeedY();

		hero->setTexture(assets->DOODLE_JUMP_RIGHT_TEXTURE);
	}
	else
	{
		if (checkCollisionPlate() == Collision::NO_COLLISION)
		{
			hero->setSpeedY(hero->getSpeedY() + ACCELERATION / 8);
			position.y = hero->getSpeedY();

			hero->setTexture(assets->DOODLE_RIGHT_TEXTURE);
		}
		else
		{
			hero->setSpeedY(hero->getSpeedY() - PLATE_DELTA_HEIGHT);
		}
	}
	hero->move(position);
}

Collision StartScene::checkCollisionPlate(void)
{
	if (((doodlePosition.y + DOODLE_HEIGHT >= platePosition.y) && (doodlePosition.y + DOODLE_HEIGHT <= platePosition.y + PLATE_HEIGHT)
		&& (doodlePosition.x + DOODLE_WIDTH >= platePosition.x) && (doodlePosition.x - PLATE_WIDTH <= platePosition.x)))
	{
		result.collision = Collision::COLLISION_PLATE;
		PlaySound(L"sounds/jump.wav", nullptr, SND_ASYNC | SND_NODEFAULT);
		return  Collision::COLLISION_PLATE;
	}
	return Collision::NO_COLLISION;
}