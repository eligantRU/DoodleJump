#include "stdafx.h"
#include "sheet.h"

StartScene::StartScene(Assets & assets, sf::View & view)
	:assets(&assets)
	, view(&view)
{
	hero = new Doodle(&assets);
	plate = new Plate(&assets);
	hero->speedY = -20.f;
	hero->body->setTexture(assets.DOODLE_RIGHT_TEXTURE);
	hero->body->setPosition(sf::Vector2f(110.f, 500.f - DOODLE_HEIGHT));

	title = new sf::Sprite;
	title->setTexture(assets.MAIN_TITLE_TEXTURE);
	title->setPosition(100, 50);

	playButton = new sf::Sprite;
	playButton->setTexture(assets.BUTTON_INACTIVE_TEXTURE);
	playButton->setPosition(200, 180);
	playText.setFont(assets.font);
	playText.setCharacterSize(20);
	playText.setString("Play");
	playText.setStyle(sf::Text::Bold);
	playText.setPosition(232.f, 182.f);
	playText.setColor(sf::Color(0, 0, 0));

	exitButton = new sf::Sprite;
	exitButton->setTexture(assets.BUTTON_INACTIVE_TEXTURE);
	exitButton->setPosition(250, 240);
	exitText.setFont(assets.font);
	exitText.setCharacterSize(20);
	exitText.setString("Exit");
	exitText.setStyle(sf::Text::Bold);
	exitText.setPosition(280.f, 242.f);
	exitText.setColor(sf::Color(0, 0, 0));

	helpButton = new sf::Sprite;
	helpButton->setTexture(assets.BUTTON_INACTIVE_TEXTURE);
	helpButton->setPosition(350, 475);
	helpText.setFont(assets.font);
	helpText.setCharacterSize(20);
	helpText.setString("Help");
	helpText.setStyle(sf::Text::Bold);
	helpText.setPosition(380.f, 477.f);
	helpText.setColor(sf::Color(0, 0, 0));

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

	platePosition.x = 100.f;
	platePosition.y = 500.f;
	plate->body->setPosition(platePosition);
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
	window.draw(*plate->body);
	window.draw(*hero->body);
	window.draw(*playButton);
	window.draw(playText);
	window.draw(*exitButton);
	window.draw(exitText);
	window.draw(*helpButton);
	window.draw(helpText);
	window.draw(*hole);
	for (int i = 0; i < NUMBER_INSECTS; ++i)
	{
		window.draw(*insects[i]);
	}
}

void StartScene::checkMouseOnButtons(sf::Vector2i & mousePosition)
{
	if (((mousePosition.y >= 180) && (mousePosition.y <= 209)
		&& (mousePosition.x >= 200) && (mousePosition.x <= 300)))
	{
		playButton->setTexture(assets->BUTTON_ACTIVE_TEXTURE);
	}
	else
	{
		playButton->setTexture(assets->BUTTON_INACTIVE_TEXTURE);
	}

	if (((mousePosition.y >= 240) && (mousePosition.y <= 269)
		&& (mousePosition.x >= 250) && (mousePosition.x <= 350)))
	{
		exitButton->setTexture(assets->BUTTON_ACTIVE_TEXTURE);
	}
	else
	{
		exitButton->setTexture(assets->BUTTON_INACTIVE_TEXTURE);
	}

	if (((mousePosition.y >= 475) && (mousePosition.y <= 504)
		&& (mousePosition.x >= 350) && (mousePosition.x <= 450)))
	{
		helpButton->setTexture(assets->BUTTON_ACTIVE_TEXTURE);
	}
	else
	{
		helpButton->setTexture(assets->BUTTON_INACTIVE_TEXTURE);
	}
}


void StartScene::checkMouseClick(sf::RenderWindow & window, sf::Event & event)
{
	if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
	{
		const sf::Vector2i mousePosition(event.mouseButton.x, event.mouseButton.y);
		if (((mousePosition.y >= 180) && (mousePosition.y <= 209)
			&& (mousePosition.x >= 200) && (mousePosition.x <= 300)))
		{
			playButton->setTexture(assets->BUTTON_INACTIVE_TEXTURE);
			result.status = GameStatus::GAME_SCENE;
		}
		if (((mousePosition.y >= 240) && (mousePosition.y <= 269)
			&& (mousePosition.x >= 250) && (mousePosition.x <= 350)))
		{
			window.close();
		}
		if (((mousePosition.y >= 475) && (mousePosition.y <= 504)
			&& (mousePosition.x >= 350) && (mousePosition.x <= 450)))
		{
			helpButton->setTexture(assets->BUTTON_INACTIVE_TEXTURE);
			result.status = GameStatus::HELP_SCENE;
		}
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
	doodlePosition = hero->body->getPosition();

	sf::Vector2f position(0.f, 0.f);
	if (hero->speedY < 0)
	{
		hero->speedY += ACCELERATION;
		position.y = hero->speedY;

		hero->body->setTexture(assets->DOODLE_JUMP_RIGHT_TEXTURE);
	}
	else
	{
		if (checkCollisionPlate() == Collision::NO_COLLISION)
		{
			hero->speedY += ACCELERATION / 8;
			position.y = hero->speedY;

			hero->body->setTexture(assets->DOODLE_RIGHT_TEXTURE);
		}
		else
		{
			hero->speedY = -PLATE_DELTA_HEIGHT;
		}
	}
	hero->body->move(position);
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