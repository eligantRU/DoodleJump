#include "stdafx.h"
#include "sheet.h"

startScene::startScene()
{
	hero.speedY = -20.f;

	title = new sf::Sprite;
	title->setTextureRect(sf::IntRect(0, 0, 202, 46));
	title->setTexture(assets->TITLE_TEXTURE);
	title->setPosition(100, 50);

	playButton = new sf::Sprite;
	playButton->setTextureRect(sf::IntRect(0, 0, 104, 29));
	playButton->setTexture(assets->BUTTON_INACTIVE_TEXTURE);
	playButton->setPosition(200, 180);
	playText.setFont(assets->font);
	playText.setCharacterSize(20);
	playText.setString("Play");
	playText.setStyle(sf::Text::Bold);
	playText.setPosition(232.f, 182.f);
	playText.setColor(sf::Color(0, 0, 0));

	exitButton = new sf::Sprite;
	exitButton->setTextureRect(sf::IntRect(0, 0, 104, 29));
	exitButton->setTexture(assets->BUTTON_INACTIVE_TEXTURE);
	exitButton->setPosition(250, 240);
	exitText.setFont(assets->font);
	exitText.setCharacterSize(20);
	exitText.setString("Exit");
	exitText.setStyle(sf::Text::Bold);
	exitText.setPosition(280.f, 242.f);
	exitText.setColor(sf::Color(0, 0, 0));

	title = new sf::Sprite;
	title->setTextureRect(sf::IntRect(0, 0, 202, 46));
	title->setTexture(assets->TITLE_TEXTURE);
	title->setPosition(100, 50);	
	
	hole = new sf::Sprite;
	hole->setTextureRect(sf::IntRect(0, 0, 60, 54));
	hole->setTexture(assets->HOLE_TEXTURE);
	hole->setPosition(300, 350);
	hole->setScale(sf::Vector2f(1.25f, 1.25f));

	insects[0] = new sf::Sprite;
	insects[0]->setTextureRect(sf::IntRect(0, 0, 21, 16));
	insects[0]->setTexture(assets->GARBAGE_1_TEXTURE);
	insects[0]->setPosition(450, 250);
	insects[1] = new sf::Sprite;
	insects[1]->setTextureRect(sf::IntRect(0, 0, 20, 23));
	insects[1]->setTexture(assets->GARBAGE_2_TEXTURE);
	insects[1]->setPosition(300, 300);
	insects[2] = new sf::Sprite;
	insects[2]->setTextureRect(sf::IntRect(0, 0, 21, 18));
	insects[2]->setTexture(assets->GARBAGE_3_TEXTURE);
	insects[2]->setPosition(210, 215);
	insects[3] = new sf::Sprite;
	insects[3]->setTextureRect(sf::IntRect(0, 0, 36, 18));
	insects[3]->setTexture(assets->GARBAGE_4_TEXTURE);
	insects[3]->setPosition(50, 50);
	insects[4] = new sf::Sprite;
	insects[4]->setTextureRect(sf::IntRect(0, 0, 28, 17));
	insects[4]->setTexture(assets->GARBAGE_5_TEXTURE);
	insects[4]->setPosition(400, 400);
	
	background = new sf::Sprite;
	background->setTextureRect(sf::IntRect(0, 0, 550, 700));
	background->setTexture(assets->BACKGROUND_TEXTURE);
	background->setPosition(0, 0);

	platePosition.x = 100.f;
	platePosition.y = 500.f;
	plate.body->setPosition(platePosition);

	hero.body->setTexture(assets->DOODLE_RIGHT_TEXTURE);
	hero.body->setPosition(sf::Vector2f(110.f, 500.f - DOODLE_HEIGHT));
}

startScene::~startScene()
{
	delete title;
	delete insects[NUMBER_INSECTS];
	delete background;
	delete playButton;
	delete exitButton;
	delete hole;
	title = NULL;
	*insects = NULL;
	background = NULL;
	playButton = NULL;
	exitButton = NULL;
	hole = NULL;
}

void startScene::onStartMenu(sf::RenderWindow & window)
{
	moveDoodle();

	window.clear(sf::Color(255, 255, 255));
	window.draw(*background);
	window.draw(*title);
	window.draw(*plate.body);
	window.draw(*hero.body);
	window.draw(*playButton);
	window.draw(playText);
	window.draw(*exitButton);
	window.draw(exitText);
	window.draw(*hole);
	for (int i = 0; i < NUMBER_INSECTS; ++i)
	{
		window.draw(*insects[i]);
	}
	window.display();

	sf::Event event;
	while (window.pollEvent(event))
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

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

		if (sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		{
			if (((mousePosition.y >= 180) && (mousePosition.y <= 209)
				&& (mousePosition.x >= 200) && (mousePosition.x <= 300)))
			{
				gameScene scene;
				Game * game = &scene;
				while (window.isOpen())
				{
					game->onGameFrame(window);
				}
				delete game;
				game = NULL;
			}
			if (((mousePosition.y >= 240) && (mousePosition.y <= 269)
				&& (mousePosition.x >= 250) && (mousePosition.x <= 350)))
			{
				window.close();
			}

		}
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
	}
}

void startScene::moveDoodle(void)
{
	doodlePosition = hero.body->getPosition();

	sf::Vector2f position(0.f, 0.f);
	if (hero.speedY <= 0)
	{
		hero.speedY += ACCELERATION;
		position.y = hero.speedY;

		hero.body->setTexture(assets->DOODLE_JUMP_RIGHT_TEXTURE);
	}
	else
	{
		if (checkCollisionPlate() == Collision::NO_COLLISION)
		{
			hero.speedY += ACCELERATION / 8;
			position.y = hero.speedY;

			hero.body->setTexture(assets->DOODLE_RIGHT_TEXTURE);
		}
		else
		{
			hero.speedY = -PLATE_DELTA_HEIGHT;
		}
	}
	hero.body->move(position);
}

Collision startScene::checkCollisionPlate(void)
{
	if (((doodlePosition.y + DOODLE_HEIGHT >= platePosition.y) && (doodlePosition.y + DOODLE_HEIGHT <= platePosition.y + PLATE_HEIGHT)
		&& (doodlePosition.x + DOODLE_WIDTH >= platePosition.x) && (doodlePosition.x - PLATE_WIDTH <= platePosition.x)))
	{
		return  Collision::COLLISION_PLATE;
	}
	return Collision::NO_COLLISION;
}