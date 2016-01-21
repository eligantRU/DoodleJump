#include "stdafx.h"
#include "sheet.h"

// TODO: No global variable!
Game game;
sf::View view;
sf::Vector2f kostil; // TODO: fix it!

void keyPressed(sf::RenderWindow & window, Game & game)
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			game.hero.direction.x = DirectionX::LEFT;
			game.hero.lastDirectionX = DirectionX::LEFT;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			game.hero.direction.x = DirectionX::RIGHT;
			game.hero.lastDirectionX = DirectionX::RIGHT;
		}
		else
		{
			game.hero.direction.x = DirectionX::NONE;
		}

		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			view.setCenter(275, 350);
			game.frameFunc = onPauseMenu; // It's no working!
		}
	}
}

bool checkGameEnd(Game & game)
{
	sf::Vector2f doodlePosition = game.hero.body->getPosition();
	sf::Vector2f platePosition[NUMBER_PLATES];

	int flag = 0;

	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		platePosition[i] = game.plate[i].body->getPosition();

		if (platePosition[i].y >= doodlePosition.y + DOODLE_HEIGHT - PLATE_HEIGHT - game.hero.deltaHeight*STEP)
		{
			flag = 0;
		}
		else
		{
			++flag;
		}
	}

	if (flag == NUMBER_PLATES)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void initialGame(Game & game, sf::View view)
{
	initialHero(game, view);
	initialPlates(game);
	initBonuses(game);
	game.actualBonus = BonusType::NO;
}

void render(sf::RenderWindow & window, Game & game) // TODO: try to use std::vector
{
	window.clear(sf::Color(230, 230, 230));
	window.draw(*game.assets.BACKGROUND);

	for (Plate &plate : game.plate)
	{
		window.draw(*plate.body);
	}

	window.draw(*game.hero.body);

	for (int i = 0; i < NUMBER_BONUSES; ++i)
	{
		window.draw(*game.bonus[i].body);
	}

	game.text.setFont(game.assets.font);
	game.text.setCharacterSize(20);
	game.text.setString("Bonuses: " + std::to_string(game.points));
	game.text.setStyle(sf::Text::Bold);
	game.text.move(0.f, 0.f);
	game.text.setColor(sf::Color(0, 0, 0));
	window.draw(game.text);

	window.display();
}

int checkDoodleFall(Game & game)
{
	sf::Vector2f doodlePosition = game.hero.body->getPosition();
	sf::Vector2f platePosition[NUMBER_PLATES];
	sf::Vector2f bonusPosition[NUMBER_BONUSES];
	Collision collision = Collision::NO_COLLISION;

	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		platePosition[i] = game.plate[i].body->getPosition();
	}
	for (int i = 0; i < NUMBER_BONUSES; ++i)
	{
		bonusPosition[i] = game.bonus[i].body->getPosition();
	}
	
	for (int i = 0; i < NUMBER_PLATES; ++i) // TODO: this cycle is the prototype of collisionPlate() 
	{
		if (((doodlePosition.y + DOODLE_HEIGHT >= platePosition[i].y) && (doodlePosition.y + DOODLE_HEIGHT <= platePosition[i].y + PLATE_HEIGHT)
			&& (doodlePosition.x + DOODLE_WIDTH >= platePosition[i].x) && (doodlePosition.x - PLATE_WIDTH <= platePosition[i].x)))
		{
			if (game.plate[i].type == PlateType::CLOUD)
			{
				// здесь и должна была бы появиться функция генерации одной новой плиты, которая бала бы частью генерации двух и более плит
				// костылёк
				game.plate[i].body->setPosition(platePosition[i].x, platePosition[i].y + 550);
			}
			collision = Collision::COLLISION_PLATE;
			break;
		}
	}

	for (int i = 0; i < NUMBER_BONUSES; ++i) // TODO: collisionBonus() based on collisionPlate()
	{
		switch (game.bonus[i].type)
		{
		case BonusType::SPRING:
			if (((doodlePosition.y + DOODLE_HEIGHT + SPRING_HEIGHT + 0.5 >= bonusPosition[i].y + SPRING_HEIGHT - 0.5) && (doodlePosition.y - 0.5 <= bonusPosition[i].y - DOODLE_HEIGHT + 0.5)
				&& (doodlePosition.x + DOODLE_WIDTH + SPRING_WIDTH >= bonusPosition[i].x) && (doodlePosition.x - SPRING_WIDTH <= bonusPosition[i].x)))
			{
				collision = Collision::COLLISION_SPRING;
				game.bonus[i].body->setTexture(game.assets.SPRING_2_TEXTURE);
				game.actualBonusId = i;
			}
			break;
		case BonusType::TRAMPOLINE:
			if (((doodlePosition.y + DOODLE_HEIGHT + TRAMPOLINE_HEIGHT + 0.5 >= bonusPosition[i].y + TRAMPOLINE_HEIGHT - 0.5) && (doodlePosition.y - 0.5 <= bonusPosition[i].y - DOODLE_HEIGHT + 0.5)
				&& (doodlePosition.x + DOODLE_WIDTH + TRAMPOLINE_WIDTH >= bonusPosition[i].x) && (doodlePosition.x - TRAMPOLINE_WIDTH <= bonusPosition[i].x)))
			{
				collision = Collision::COLLISION_TRAMPLANE;
				game.actualBonusId = i;
			}
			break;
		case BonusType::HAT_HELICOPTER:
			if (((doodlePosition.y + DOODLE_HEIGHT + HAT_HELICOPTER_HEIGHT + 0.5 >= bonusPosition[i].y + HAT_HELICOPTER_HEIGHT - 0.5) && (doodlePosition.y - 0.5 <= bonusPosition[i].y - DOODLE_HEIGHT + 0.5)
				&& (doodlePosition.x + DOODLE_WIDTH + HAT_HELICOPTER_WIDTH >= bonusPosition[i].x) && (doodlePosition.x - HAT_HELICOPTER_WIDTH <= bonusPosition[i].x)))
			{
				collision = Collision::COLLISION_HAT_HELICOPTER;
				game.actualBonusId = i;

				if (game.hero.direction.x == DirectionX::RIGHT)
				{
					game.bonus[i].body->setPosition(doodlePosition.x + 15, doodlePosition.y - 15);     // 15 -- подгон, введи точное значение
				}
				else if ((game.hero.direction.x == DirectionX::LEFT) || (game.hero.direction.x == DirectionX::NONE))
				{
					game.bonus[i].body->setPosition(doodlePosition.x + 15, doodlePosition.y - 15);     // аналогично, не удалять!
				}
			}
			break;
		case BonusType::ROCKET:
			if (((doodlePosition.y + DOODLE_HEIGHT + ROCKET_HEIGHT + 0.5 >= bonusPosition[i].y + ROCKET_HEIGHT - 0.5) && (doodlePosition.y - 0.5 <= bonusPosition[i].y - DOODLE_HEIGHT + 0.5)
				&& (doodlePosition.x + DOODLE_WIDTH + ROCKET_WIDTH >= bonusPosition[i].x) && (doodlePosition.x - ROCKET_WIDTH <= bonusPosition[i].x)))
			{
				collision = Collision::COLLISION_ROCKET;
				game.actualBonusId = i;

				if (game.hero.direction.x == DirectionX::RIGHT)
				{
					game.bonus[i].body->setPosition(doodlePosition.x - ROCKET_WIDTH, doodlePosition.y);
				}
				else if ((game.hero.direction.x == DirectionX::LEFT) || (game.hero.direction.x == DirectionX::NONE))
				{
					game.bonus[i].body->setPosition(doodlePosition.x + DOODLE_WIDTH, doodlePosition.y);
				}
			}
			break;
		}
	}

	switch (collision)
	{
	case Collision::COLLISION_PLATE:
		game.actualBonus = BonusType::NO;
		return 100;
	case Collision::COLLISION_SPRING:
		game.actualBonus = BonusType::SPRING;
		return 75;
	case Collision::COLLISION_TRAMPLANE:
		game.actualBonus = BonusType::TRAMPOLINE;
		return 100;
	case Collision::COLLISION_HAT_HELICOPTER:
		game.actualBonus = BonusType::HAT_HELICOPTER;
		return 200;
	case Collision::COLLISION_ROCKET:
		game.actualBonus = BonusType::ROCKET;
		return 400;
	default:
		return 0;
	}
}
