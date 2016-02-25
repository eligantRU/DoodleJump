#include "stdafx.h"
#include "sheet.h"

// TODO: No global variable!
// костыль
Game game;
sf::View view;
sf::Vector2f kostil;
int kostil2 = 0; //костыль
int unstablePlateID = -1;

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
			game.frameFunc = onPauseMenu;
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

	for (Plate & plate : game.plate)
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

Collision checkCollisionPlate(Game & game, sf::Vector2f & doodlePosition, sf::Vector2f platePosition[NUMBER_PLATES])
{
	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		if (((doodlePosition.y + DOODLE_HEIGHT >= platePosition[i].y) && (doodlePosition.y + DOODLE_HEIGHT <= platePosition[i].y + PLATE_HEIGHT)
				&& (doodlePosition.x + DOODLE_WIDTH >= platePosition[i].x) && (doodlePosition.x - PLATE_WIDTH <= platePosition[i].x)))
		{
			if (game.plate[i].type == PlateType::UNSTABLE)
			{
				kostil2 = 30;
				unstablePlateID = i;
				continue;
			}

			if (game.plate[i].type == PlateType::CLOUD)
			{
				// здесь и должна была бы по€витьс€ функци€ генерации одной новой плиты, котора€ бала бы частью генерации двух и более плит -- костыль!
				game.plate[i].body->setPosition(platePosition[i].x, platePosition[i].y + 550); // TODO: fix it!
			}
			return  Collision::COLLISION_PLATE;
		}
	}
	// return Collision::NO_COLLISION; // TODO: Function must return value...present value?
}

Collision checkCollisionBonus(Game & game, sf::Vector2f & doodlePosition, sf::Vector2f bonusPosition[NUMBER_PLATES]) // TODO: duplicated code -- fix!
{
	for (int i = 0; i < NUMBER_BONUSES; ++i)
	{
		switch (game.bonus[i].type)
		{
		case BonusType::SPRING:
			if (((doodlePosition.y + DOODLE_HEIGHT >= bonusPosition[i].y) && (doodlePosition.y + DOODLE_HEIGHT <= bonusPosition[i].y + SPRING_HEIGHT)
				&& (doodlePosition.x + DOODLE_WIDTH >= bonusPosition[i].x) && (doodlePosition.x - SPRING_WIDTH <= bonusPosition[i].x)))
			{				
				game.bonus[i].body->setTexture(game.assets.SPRING_2_TEXTURE);
				game.actualBonusId = i;

				return Collision::COLLISION_SPRING;
			}
			break;
		case BonusType::TRAMPOLINE:
			if (((doodlePosition.y + DOODLE_HEIGHT >= bonusPosition[i].y) && (doodlePosition.y + DOODLE_HEIGHT <= bonusPosition[i].y + TRAMPOLINE_HEIGHT)
				&& (doodlePosition.x + DOODLE_WIDTH >= bonusPosition[i].x) && (doodlePosition.x - TRAMPOLINE_WIDTH <= bonusPosition[i].x))) 
			{
				game.actualBonusId = i;
				return Collision::COLLISION_TRAMPLANE;
			}
			break;
		case BonusType::HAT_HELICOPTER:
			if (((doodlePosition.y + DOODLE_HEIGHT >= bonusPosition[i].y) && (doodlePosition.y + DOODLE_HEIGHT <= bonusPosition[i].y + HAT_HELICOPTER_HEIGHT)
				&& (doodlePosition.x + DOODLE_WIDTH >= bonusPosition[i].x) && (doodlePosition.x - HAT_HELICOPTER_WIDTH <= bonusPosition[i].x)))
			{
				game.actualBonusId = i;

				if (game.hero.direction.x == DirectionX::RIGHT)
				{
					game.bonus[i].body->setPosition(doodlePosition.x + 15, doodlePosition.y - 15);     // 15 -- подгон, введи точное значение
				}
				else if ((game.hero.direction.x == DirectionX::LEFT) || (game.hero.direction.x == DirectionX::NONE))
				{
					game.bonus[i].body->setPosition(doodlePosition.x + 15, doodlePosition.y - 15);     // аналогично, не удал€ть!
				}

				return Collision::COLLISION_HAT_HELICOPTER;
			}
			break;
		case BonusType::ROCKET:
			if (((doodlePosition.y + DOODLE_HEIGHT >= bonusPosition[i].y) && (doodlePosition.y + DOODLE_HEIGHT <= bonusPosition[i].y + ROCKET_HEIGHT)
				&& (doodlePosition.x + DOODLE_WIDTH >= bonusPosition[i].x) && (doodlePosition.x - ROCKET_WIDTH <= bonusPosition[i].x)))
			{
				game.actualBonusId = i;

				if (game.hero.direction.x == DirectionX::RIGHT)
				{
					game.bonus[i].body->setPosition(doodlePosition.x - ROCKET_WIDTH, doodlePosition.y);
				}
				else if ((game.hero.direction.x == DirectionX::LEFT) || (game.hero.direction.x == DirectionX::NONE))
				{
					game.bonus[i].body->setPosition(doodlePosition.x + DOODLE_WIDTH, doodlePosition.y);
				}

				return Collision::COLLISION_ROCKET;
			}
			break;
		}
	}

	return Collision::NO_COLLISION;
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
	
	collision = checkCollisionBonus(game, doodlePosition, bonusPosition);
	collision = checkCollisionPlate(game, doodlePosition, platePosition);
	
	switch (collision)
	{
	case Collision::COLLISION_PLATE:
		game.actualBonus = BonusType::NO;
		return PLATE_DELTA_HEIGHT;
	case Collision::COLLISION_SPRING:
		game.actualBonus = BonusType::SPRING;
		return SPRING_DELTA_HEIGHT;
	case Collision::COLLISION_TRAMPLANE:
		game.actualBonus = BonusType::TRAMPOLINE;
		return TRAMPLANE_DELTA_HEIGHT;
	case Collision::COLLISION_HAT_HELICOPTER:
		game.actualBonus = BonusType::HAT_HELICOPTER;
		return HAT_HELICOPTER_DELTA_HEIGHT;
	case Collision::COLLISION_ROCKET:
		game.actualBonus = BonusType::ROCKET;
		return ROCKET_DELTA_HEIGHT;
	default:
		return 0;
	}
}
