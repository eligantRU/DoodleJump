#include "stdafx.h"
#include "sheet.h"

gameScene::gameScene()
{
	actualBonus = BonusType::NO;
	points = 0;
	endOfGame = false;
	view.reset(sf::FloatRect(0, 0, 550, 700));
	qwerty = 0; // TODO: do not optimize using this sheet
	unstablePlatesCounter = 0;
	kostil2 = 30;
	unstablePlateID = -1;
	initBonuses();

	hole = new sf::Sprite;
	hole->setTextureRect(sf::IntRect(0, 0, 60, 54));
	hole->setTexture(assets->HOLE_TEXTURE);
	holePosition.x = float(rand() % (550 - HOLE_WIDTH));
	holePosition.y = -1.f * float(rand() % 1000) - 750.f;
	hole->setPosition(holePosition.x, holePosition.y);

	text.setFont(assets->font);
	text.setCharacterSize(20);
	text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color(0, 0, 0));

	background = new sf::Sprite;
	background->setTextureRect(sf::IntRect(0, 0, 550, 700));
	background->setTexture(assets->BACKGROUND_TEXTURE);
}

gameScene::~gameScene()
{
	delete background;
	background = NULL;
}

void gameScene::generHole(void)
{
	if (hole->getPosition().y >= view.getCenter().y + 350.f)
	{
		holePosition.x = float(rand() % (550 - HOLE_WIDTH));
		holePosition.y = hero.body->getPosition().y -1.f * float(rand() % 7500) - 750.f;
		hole->setPosition(sf::Vector2f(holePosition.x, holePosition.y));
	}
}

void gameScene::generBonuses(void)
{
	sf::Vector2f doodlePosition = hero.body->getPosition();
	sf::Vector2f bonusPosition[NUMBER_BONUSES];
	sf::Vector2f platePosition;

	for (int bonusIndex = 0; bonusIndex < NUMBER_BONUSES; ++bonusIndex)
	{
		bonusPosition[bonusIndex] = bonus[bonusIndex].body->getPosition();

		if (bonusPosition[bonusIndex].y > view.getCenter().y + 350 + ROCKET_HEIGHT) 
		{
			for (int plateIndex = 0; plateIndex < NUMBER_PLATES; ++plateIndex)
			{
				platePosition = plate[plateIndex].body->getPosition();
				if ((platePosition.y <= doodlePosition.y - 275) && ((plate[plateIndex].type == PlateType::STATIC) || (plate[plateIndex].type == PlateType::STATIC_DYNAMIC_X)))
				{
					int randomNum = rand() % 4;
					switch (randomNum)
					{
					case 0:
						buildBonus(BonusType::SPRING, bonusIndex, platePosition, plateIndex);
						break;
					case 1:
						buildBonus(BonusType::TRAMPOLINE, bonusIndex, platePosition, plateIndex);
						break;
					case 2:
						buildBonus(BonusType::HAT_HELICOPTER, bonusIndex, platePosition, plateIndex);
						break;
					case 3:
						buildBonus(BonusType::ROCKET, bonusIndex, platePosition, plateIndex);
						break;
					}
				}
			}
		}
	}
}

void gameScene::initBonuses(void)
{
	for (int plateIndex = 0; plateIndex < NUMBER_PLATES; ++plateIndex)
	{
		platePosition.push_back(plate[plateIndex].body->getPosition());
	}
	for (int bonusIndex = 0; bonusIndex < NUMBER_BONUSES; ++bonusIndex)
	{
		int plateIndex = rand() % platePosition.size();
		BonusType type = (rand() % 2) ? BonusType::SPRING : BonusType::TRAMPOLINE;
		buildBonus(type, bonusIndex, platePosition[plateIndex], plateIndex);
		bonus[bonusIndex].direction.x = DirectionX::NONE;
	}
}

void gameScene::buildBonus(BonusType bonusType, int bonusIndex, sf::Vector2f platePosition, int plateIndex)
{
	//Bonus & bonus = bonus[bonusIndex];

	bonus[bonusIndex].direction.x = plate[plateIndex].direction.x;
	bonus[bonusIndex].plateIndex = plateIndex;

	switch (bonusType)
	{
	case BonusType::SPRING:
	{
		int x = rand() % (PLATE_WIDTH - SPRING_WIDTH);
		bonus[bonusIndex].body = new sf::Sprite;
		bonus[bonusIndex].type = BonusType::SPRING;
		bonus[bonusIndex].body->setPosition(platePosition.x + x, platePosition.y - SPRING_HEIGHT);
		bonus[bonusIndex].body->setTexture(assets->SPRING_TEXTURE);
		break;
	}
	case BonusType::TRAMPOLINE:
	{
		int x = rand() % (PLATE_WIDTH - TRAMPOLINE_WIDTH);
		bonus[bonusIndex].body = new sf::Sprite;
		bonus[bonusIndex].type = BonusType::TRAMPOLINE;
		bonus[bonusIndex].body->setPosition(platePosition.x + x, platePosition.y - TRAMPOLINE_HEIGHT);
		bonus[bonusIndex].body->setTexture(assets->TRAMPOLINE_TEXTURE);
		break;
	}
	case BonusType::HAT_HELICOPTER:
	{
		int x = rand() % (PLATE_WIDTH - SPRING_WIDTH);
		bonus[bonusIndex].body = new sf::Sprite;
		bonus[bonusIndex].type = BonusType::HAT_HELICOPTER;
		bonus[bonusIndex].body->setPosition(platePosition.x + x, platePosition.y - HAT_HELICOPTER_HEIGHT);
		switch (rand() % 2)
		{
		case 0:
			bonus[bonusIndex].body->setTexture(assets->HAT_HELOCPTER_NONE_LEFT_TEXTURE);
			break;
		case 1:
			bonus[bonusIndex].body->setTexture(assets->HAT_HELOCPTER_NONE_RIGHT_TEXTURE);
			break;
		}
		break;
	}
	case BonusType::ROCKET:
	{
		int x = rand() % (PLATE_WIDTH - ROCKET_WIDTH);
		bonus[bonusIndex].body = new sf::Sprite;
		bonus[bonusIndex].type = BonusType::ROCKET;
		bonus[bonusIndex].body->setPosition(platePosition.x + x, platePosition.y - ROCKET_HEIGHT);
		bonus[bonusIndex].body->setTexture(assets->ROCKET_NONE_TEXTURE);
		break;
	}
	}
}

void gameScene::render(sf::RenderWindow & window) // TODO: try to use std::vector
{
	//for (std::vector<sf::Sprite*>::const_iterator it = needRender.begin(); it != needRender.end(); ++it)
	window.clear(sf::Color(255, 255, 255));

	window.draw(*background);

	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		window.draw(*plate[i].body);
	}

	window.draw(*hero.body);

	for (int i = 0; i < NUMBER_BONUSES; ++i)
	{
		window.draw(*bonus[i].body);
	}
	window.draw(*hole);
	
	text.setString("Score: " + std::to_string(points));
	window.draw(text);
}

void gameScene::onGameFrame(sf::RenderWindow & window)
{
	if (!endOfGame)
	{
		keyPressed(window);
		update(window);
		window.setView(view);
		render(window);
		window.display();
	}
	else
	{
		view.setCenter(275, 350);
		window.setView(view);
		
		gameOverScene scene;
		Game * game = &scene;
		while (window.isOpen())
		{
			game->onGameOverMenu(window, points);
		}
		delete game;
		game = NULL;
	}
}

bool gameScene::checkGameEnd(void)
{
	sf::Vector2f doodlePosition = hero.body->getPosition();
	if ((checkCollisionHole(doodlePosition) == Collision::COLLISION_HOLE) && ((actualBonus != BonusType::ROCKET) && (actualBonus != BonusType::HAT_HELICOPTER)))
	{
		return true;
	}
	if (hero.body->getPosition().y <= view.getCenter().y + 350.f + hero.speedY + DOODLE_HEIGHT)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void gameScene::dropUnstablePlates(void)
{
	for (int plateIndex = 0; plateIndex < NUMBER_PLATES; ++plateIndex)
	{
		if (plate[plateIndex].fallingPlate == true)
		{
			plate[plateIndex].body->rotate(-1.f);
			plate[plateIndex].body->move(sf::Vector2f(-1 * STEP, 4 * STEP));
			if (plate[plateIndex].body->getPosition().y >= view.getCenter().y + 350)
			{
				plate[plateIndex].body->setRotation(0);
				plate[plateIndex].fallingPlate = false;
			}
		}
	}
}

void gameScene::update(sf::RenderWindow & window) // смену текстур в отдельные функции...убожество!
{
	sf::Vector2f position(0.f, 0.f);
	sf::Vector2f doodlePosition = hero.body->getPosition();

	if (hero.direction.x == DirectionX::RIGHT)
	{
		position.x += STEP;
		hero.body->setTexture(assets->DOODLE_JUMP_RIGHT_TEXTURE);
	}
	else if (hero.direction.x == DirectionX::LEFT)
	{
		position.x -= STEP;
		hero.body->setTexture(assets->DOODLE_JUMP_LEFT_TEXTURE);
	}

	if (hero.speedY <= 0)
	{
		hero.speedY += ACCELERATION;
		position.y = hero.speedY;

		if (hero.body->getPosition().y < hero.positionBeforeDown.y)
		{
			hero.positionBeforeDown = hero.body->getPosition();
		}
	}
	else
	{
		float testingFall = checkDoodleFall();
		if (testingFall == 0)
		{
			actualBonus = BonusType::NO;
			hero.speedY += ACCELERATION/8;
			position.y = hero.speedY;
			if (hero.body->getPosition().y < hero.positionBeforeDown.y)
			{
				hero.positionBeforeDown = hero.body->getPosition();
			}
		}
		else
		{
			hero.speedY = -testingFall; 
		}
	}
	hero.body->move(position);

	checkCylinderEffect(doodlePosition);
	
	//

	/*
	if (game.actualBonus == BonusType::HAT_HELICOPTER) // и это тоже в отдельную функцию
	{
		if (game.hero.deltaHeight <= 20)
		{
			game.qwerty = -1;
			game.bonus[game.actualBonusId].body->setTexture(game.assets.HAT_HELOCPTER_FLY_LEFT_TEXTURE);
			game.bonus[game.actualBonusId].body->rotate(-0.07f);
			game.bonus[game.actualBonusId].body->move(sf::Vector2f(-2 * STEP, 3 * STEP));
		}
		if (game.hero.deltaHeight == 0)
		{
			game.qwerty = 0;
			game.actualBonus = BonusType::NO;
			game.bonus[game.actualBonusId].body->setPosition(0.f, doodlePosition.y + DOODLE_HEIGHT + 275 + 2 * PLATE_HEIGHT); // костыль
		}

		if ((game.qwerty >= 0) && (game.qwerty <= 5))
		{
			game.bonus[game.actualBonusId].body->setTexture(game.assets.HAT_HELOCPTER_FLY_LEFT_TEXTURE);
			++game.qwerty;
		}
		if ((game.qwerty >= 6) && (game.qwerty <= 10))
		{
			game.bonus[game.actualBonusId].body->setTexture(game.assets.HAT_HELOCPTER_DIAGONAL_LEFT_TEXTURE);
			++game.qwerty;
		}
		if ((game.qwerty >= 11) && (game.qwerty <= 15))
		{
			game.bonus[game.actualBonusId].body->setTexture(game.assets.HAT_HELOCPTER_DIAGONAL_RIGHT_TEXTURE);
			++game.qwerty;
		}
		if ((game.qwerty >= 16) && (game.qwerty <= 20))
		{
			game.bonus[game.actualBonusId].body->setTexture(game.assets.HAT_HELOCPTER_FLY_RIGHT_TEXTURE);
			++game.qwerty;
		}
		
		if (game.qwerty == 20)
		{
			game.qwerty = 0;
		}

		if ((game.qwerty >= 0) && (game.qwerty <= 20) && (game.actualBonus != BonusType::NO))
		{
			if (game.hero.lastDirectionX == DirectionX::RIGHT)
			{
				game.bonus[game.actualBonusId].body->setPosition(game.hero.body->getPosition().x, game.hero.body->getPosition().y - 13);
			}
			else if (game.hero.lastDirectionX == DirectionX::LEFT)
			{
				game.bonus[game.actualBonusId].body->setPosition(game.hero.body->getPosition().x + 15, game.hero.body->getPosition().y - 13);
			}
		}
	}

	if (game.actualBonus == BonusType::ROCKET) // в отдельную функцию
	{
		if (game.hero.deltaHeight <= 15)
		{
			game.qwerty = -1;
			game.bonus[game.actualBonusId].body->setTexture(game.assets.ROCKET_NONE_TEXTURE);
			game.bonus[game.actualBonusId].body->rotate(-0.07f);
			game.bonus[game.actualBonusId].body->move(sf::Vector2f(-2 * STEP, 6 * STEP));
		}
		if (game.hero.deltaHeight == 0)
		{
			game.qwerty = 0;
			game.actualBonus = BonusType::NO;
			game.bonus[game.actualBonusId].body->setPosition(0.f, doodlePosition.y + DOODLE_HEIGHT + 275 + 2 * PLATE_HEIGHT); // костыль
		}

		if ((game.qwerty >= 0) && (game.qwerty <= 5))
		{
			game.bonus[game.actualBonusId].body = new sf::Sprite; // костыль
			if (game.hero.lastDirectionX == DirectionX::RIGHT)
			{
				game.bonus[game.actualBonusId].body->setTexture(game.assets.ROCKET_1_LEFT_TEXTURE);
			}
			else if (game.hero.lastDirectionX == DirectionX::LEFT)
			{
				game.bonus[game.actualBonusId].body->setTexture(game.assets.ROCKET_1_RIGHT_TEXTURE);
			}
			++game.qwerty;
		}
		if ((game.qwerty >= 6) && (game.qwerty <= 10))
		{
			game.bonus[game.actualBonusId].body = new sf::Sprite; // костыль
			if (game.hero.lastDirectionX == DirectionX::RIGHT)
			{
				game.bonus[game.actualBonusId].body->setTexture(game.assets.ROCKET_2_LEFT_TEXTURE);
			}
			else if (game.hero.lastDirectionX == DirectionX::LEFT)
			{
				game.bonus[game.actualBonusId].body->setTexture(game.assets.ROCKET_2_RIGHT_TEXTURE);
			}
			++game.qwerty;
		}
		if ((game.qwerty >= 11) && (game.qwerty <= 15))
		{
			game.bonus[game.actualBonusId].body = new sf::Sprite; // костыль
			if (game.hero.lastDirectionX == DirectionX::RIGHT)
			{
				game.bonus[game.actualBonusId].body->setTexture(game.assets.ROCKET_3_LEFT_TEXTURE);
			}
			else if (game.hero.lastDirectionX == DirectionX::LEFT)
			{
				game.bonus[game.actualBonusId].body->setTexture(game.assets.ROCKET_3_RIGHT_TEXTURE);
			}
			++game.qwerty;
		}
		if (game.qwerty == 15)
		{
			game.qwerty = 0;
		}

		if ((game.qwerty >= 0) && (game.qwerty <= 15) && (game.actualBonus != BonusType::NO))
		{
			if (game.hero.lastDirectionX == DirectionX::RIGHT)
			{
				game.bonus[game.actualBonusId].body->setPosition(game.hero.body->getPosition().x - ROCKET_WIDTH, game.hero.body->getPosition().y);
			}
			else if (game.hero.lastDirectionX == DirectionX::LEFT)
			{
				game.bonus[game.actualBonusId].body->setPosition(game.hero.body->getPosition().x + DOODLE_WIDTH, game.hero.body->getPosition().y);
			}
		}
	} */

	if ((hero.speedY <= 0) && (doodlePosition.y <= hero.positionBeforeDown.y))
	{
		view.setCenter(275, doodlePosition.y);
		background->setPosition(0, doodlePosition.y - 350);
		text.setPosition(0, doodlePosition.y - 350);
		++points;
	}

	moveBonuses();
	dropUnstablePlates();
	moveDynamicPlates();
	generPlates();
	generBonuses();
	generHole();

	if (checkGameEnd())
	{
		endOfGame = true;
	}
}

void gameScene::keyPressed(sf::RenderWindow & window)
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			hero.direction.x = DirectionX::LEFT;
			hero.lastDirectionX = DirectionX::LEFT;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			hero.direction.x = DirectionX::RIGHT;
			hero.lastDirectionX = DirectionX::RIGHT;
		}
		else
		{
			hero.direction.x = DirectionX::NONE;
		}

		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			view.setCenter(275, 350);

			pauseScene scene;
			Game * game = &scene;			
			while (window.isOpen()) 
			{
				game->onPauseMenu(window, view);
			}
			delete game;
			game = NULL;
		}
	}
}

float gameScene::checkDoodleFall(void)
{
	sf::Vector2f doodlePosition = hero.body->getPosition();
	sf::Vector2f platePosition[NUMBER_PLATES];
	sf::Vector2f bonusPosition[NUMBER_BONUSES];
	Collision collision = Collision::NO_COLLISION;

	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		platePosition[i] = plate[i].body->getPosition();
	}
	for (int i = 0; i < NUMBER_BONUSES; ++i)
	{
		bonusPosition[i] = bonus[i].body->getPosition();
	}

	collision = checkCollisionBonus(doodlePosition, bonusPosition);
	if (collision == Collision::NO_COLLISION)
	{
		collision = checkCollisionPlate(doodlePosition, platePosition);
	}

	switch (collision)
	{
	case Collision::COLLISION_PLATE:
		actualBonus = BonusType::NO;
		return PLATE_DELTA_HEIGHT;
	case Collision::COLLISION_SPRING:
		actualBonus = BonusType::SPRING;
		return SPRING_DELTA_HEIGHT;
	case Collision::COLLISION_TRAMPLANE:
		actualBonus = BonusType::TRAMPOLINE;
		return TRAMPLANE_DELTA_HEIGHT;
	case Collision::COLLISION_HAT_HELICOPTER:
		actualBonus = BonusType::HAT_HELICOPTER;
		return HAT_HELICOPTER_DELTA_HEIGHT;
	case Collision::COLLISION_ROCKET:
		actualBonus = BonusType::ROCKET;
		return ROCKET_DELTA_HEIGHT;
	default:
		return 0.f;
	}
}

Collision gameScene::checkCollisionPlate(sf::Vector2f & doodlePosition, sf::Vector2f platePosition[NUMBER_PLATES])
{
	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		if (((doodlePosition.y + DOODLE_HEIGHT >= platePosition[i].y) && (doodlePosition.y + DOODLE_HEIGHT <= platePosition[i].y + PLATE_HEIGHT)
			&& (doodlePosition.x + DOODLE_WIDTH >= platePosition[i].x) && (doodlePosition.x - PLATE_WIDTH <= platePosition[i].x)))
		{
			if ((plate[i].type == PlateType::UNSTABLE) || (plate[i].type == PlateType::UNSTABLE_DYNAMIC_X))
			{
				plate[i].fallingPlate = true;
				continue;
			}

			if (plate[i].type == PlateType::CLOUD)
			{
				// здесь и должна была бы появиться функция генерации одной новой плиты, которая бала бы частью генерации двух и более плит -- костыль!
				plate[i].body->setPosition(view.getCenter().x, view.getCenter().y + 350); // TODO: fix it!
			}
			return  Collision::COLLISION_PLATE;
		}
	}
	return Collision::NO_COLLISION;
}

Collision gameScene::checkCollisionHole(sf::Vector2f & doodlePosition)
{
	if (((doodlePosition.y + DOODLE_HEIGHT >= holePosition.y) && (doodlePosition.y + DOODLE_HEIGHT <= holePosition.y + HOLE_HEIGHT)
		&& (doodlePosition.x + DOODLE_WIDTH >= holePosition.x) && (doodlePosition.x - HOLE_WIDTH <= holePosition.x)))
	{
		return Collision::COLLISION_HOLE;
	}
	return Collision::NO_COLLISION;
}

Collision gameScene::checkCollisionBonus(sf::Vector2f & doodlePosition, sf::Vector2f bonusPosition[NUMBER_PLATES]) // TODO: duplicated code -- fix!
{
	for (int i = 0; i < NUMBER_BONUSES; ++i)
	{
		switch (bonus[i].type)
		{
		case BonusType::SPRING:
			if (((doodlePosition.y + DOODLE_HEIGHT >= bonusPosition[i].y) && (doodlePosition.y + DOODLE_HEIGHT <= bonusPosition[i].y + SPRING_HEIGHT)
				&& (doodlePosition.x + DOODLE_WIDTH >= bonusPosition[i].x) && (doodlePosition.x - SPRING_WIDTH <= bonusPosition[i].x)))
			{
				bonus[i].body->setTexture(assets->SPRING_2_TEXTURE);
				actualBonusId = i;

				return Collision::COLLISION_SPRING;
			}
			break;
		case BonusType::TRAMPOLINE:
			if (((doodlePosition.y + DOODLE_HEIGHT >= bonusPosition[i].y) && (doodlePosition.y + DOODLE_HEIGHT <= bonusPosition[i].y + TRAMPOLINE_HEIGHT)
				&& (doodlePosition.x + DOODLE_WIDTH >= bonusPosition[i].x) && (doodlePosition.x - TRAMPOLINE_WIDTH <= bonusPosition[i].x)))
			{
				actualBonusId = i;
				return Collision::COLLISION_TRAMPLANE;
			}
			break;
		case BonusType::HAT_HELICOPTER:
			if (((doodlePosition.y + DOODLE_HEIGHT >= bonusPosition[i].y) && (doodlePosition.y + DOODLE_HEIGHT <= bonusPosition[i].y + HAT_HELICOPTER_HEIGHT)
				&& (doodlePosition.x + DOODLE_WIDTH >= bonusPosition[i].x) && (doodlePosition.x - HAT_HELICOPTER_WIDTH <= bonusPosition[i].x)))
			{
				actualBonusId = i;

				if (hero.direction.x == DirectionX::RIGHT)
				{
					bonus[i].body->setPosition(doodlePosition.x + 15, doodlePosition.y - 15);     // 15 -- подгон, введи точное значение
				}
				else if ((hero.direction.x == DirectionX::LEFT) || (hero.direction.x == DirectionX::NONE))
				{
					bonus[i].body->setPosition(doodlePosition.x + 15, doodlePosition.y - 15);     // аналогично, не удалять!
				}

				return Collision::COLLISION_HAT_HELICOPTER;
			}
			break;
		case BonusType::ROCKET:
			if (((doodlePosition.y + DOODLE_HEIGHT >= bonusPosition[i].y) && (doodlePosition.y + DOODLE_HEIGHT <= bonusPosition[i].y + ROCKET_HEIGHT)
				&& (doodlePosition.x + DOODLE_WIDTH >= bonusPosition[i].x) && (doodlePosition.x - ROCKET_WIDTH <= bonusPosition[i].x)))
			{
				actualBonusId = i;

				if (hero.direction.x == DirectionX::RIGHT)
				{
					bonus[i].body->setPosition(doodlePosition.x - ROCKET_WIDTH, doodlePosition.y);
				}
				else if ((hero.direction.x == DirectionX::LEFT) || (hero.direction.x == DirectionX::NONE))
				{
					bonus[i].body->setPosition(doodlePosition.x + DOODLE_WIDTH, doodlePosition.y);
				}

				return Collision::COLLISION_ROCKET;
			}
			break;
		}
	}

	return Collision::NO_COLLISION;
}

void gameScene::generPlates(void)
{
	sf::Vector2f platePosition[NUMBER_PLATES];

	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		platePosition[i] = plate[i].body->getPosition();
		float x = float(rand() % (550 - PLATE_WIDTH));
		float y = float(rand() % 150); // TODO: Сюда запилить функцию для равномерной генерации плит по высоте

		if (platePosition[i].y >= view.getCenter().y + 350.f)
		{
			int divider;
			if (unstablePlatesCounter < 3)
			{
				divider = 5;
			}
			else
			{
				divider = 3;
			}

			if ((plate[i].type == PlateType::UNSTABLE) || (plate[i].type == PlateType::UNSTABLE_DYNAMIC_X))
			{
				--unstablePlatesCounter;
			}

			plate[i].body->setRotation(0);
			switch (rand() % divider)
			{
			case 0:
				plate[i].type = PlateType::STATIC;
				plate[i].direction.x = DirectionX::NONE;
				plate[i].body->setTexture(assets->PLATE_STATIC_TEXTURE);
				break;
			case 1:
				plate[i].type = PlateType::STATIC_DYNAMIC_X;
				switch (rand() % 2)
				{
				case 0:
					plate[i].direction.x = DirectionX::LEFT;
					break;
				case 1:
					plate[i].direction.x = DirectionX::RIGHT;
					break;
				}
				plate[i].body->setTexture(assets->PLATE_DYNAMIC_TEXTURE);
				break;
			case 2:
				plate[i].type = PlateType::CLOUD;
				plate[i].direction.x = DirectionX::NONE;
				plate[i].body->setTexture(assets->PLATE_CLOUD_TEXTURE);
				break;
			case 3:
				plate[i].type = PlateType::UNSTABLE;
				plate[i].direction.x = DirectionX::NONE;
				plate[i].body->setTexture(assets->PLATE_UNSTABLE_TEXTURE);
				++unstablePlatesCounter;
				break;
			case 4:
				plate[i].type = PlateType::UNSTABLE_DYNAMIC_X;
				switch (rand() % 2)
				{
				case 0:
					plate[i].direction.x = DirectionX::LEFT;
					break;
				case 1:
					plate[i].direction.x = DirectionX::RIGHT;
					break;
				}
				plate[i].body->setTexture(assets->PLATE_UNSTABLE_TEXTURE);
				++unstablePlatesCounter;
				break;
			}
			plate[i].body->setPosition(x, view.getCenter().y - 350.f - y);
		}
	}
}

void gameScene::moveDynamicPlates(void)
{
	sf::Vector2f position(0.f, 0.f);
	sf::Vector2f platePosition[NUMBER_PLATES];

	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		platePosition[i] = plate[i].body->getPosition();
		if ((plate[i].type == PlateType::STATIC_DYNAMIC_X) || (plate[i].type == PlateType::UNSTABLE_DYNAMIC_X)) // лишнее условие, но так нагляднее
		{
			switch (plate[i].direction.x)
			{
			case DirectionX::LEFT:
				if (platePosition[i].x <= STEP)
				{
					plate[i].direction.x = DirectionX::RIGHT;
				}
				else
				{
					position.x -= 0.5f * STEP;
				}
				break;
			case DirectionX::RIGHT:
				if (platePosition[i].x >= 550 - PLATE_WIDTH - STEP) // 550 - это ширина экрана
				{
					plate[i].direction.x = DirectionX::LEFT;
				}
				else
				{
					position.x += 0.5f * STEP;
				}
				break;
			default:
				break;
			}
			plate[i].body->move(position);
			position.x = 0;
			position.y = 0;
		}
	}
}

void gameScene::moveBonuses(void)
{
	sf::Vector2f position(0.f, 0.f);

	for (int bonusIndex = 0; bonusIndex < NUMBER_BONUSES; ++bonusIndex)
	{
		bonus[bonusIndex].direction.x = plate[bonus[bonusIndex].plateIndex].direction.x;
		if (bonus[bonusIndex].direction.x != DirectionX::NONE)
		{
			if (bonus[bonusIndex].direction.x == DirectionX::LEFT)
			{
				position.x -= 0.5f * STEP;
			}
			if (bonus[bonusIndex].direction.x == DirectionX::RIGHT)
			{
				position.x += 0.5f * STEP;
			}
			bonus[bonusIndex].body->move(position);
			position.x = 0.f;
		}
		else
		{
			bonus[bonusIndex].direction.x = DirectionX::NONE;
		}
	}
}

void gameScene::checkCylinderEffect(sf::Vector2f & doodlePosition)
{
	if (doodlePosition.x <= -1 * DOODLE_WIDTH)
	{
		hero.body->setPosition(550 - DOODLE_WIDTH, doodlePosition.y);
	}
	if (doodlePosition.x >= 550)
	{
		hero.body->setPosition(0, doodlePosition.y);
	}
}