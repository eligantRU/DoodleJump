#include "stdafx.h"
#include "sheet.h"

gameScene::gameScene(Assets * assets, sf::View * view)
{
	this->assets = assets;
	this->view = view;
	this->hero = new Doodle(assets);
	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		plate[i] = new Plate(assets);
	}

	actualBonus = BonusType::NO;
	points = 0;
	endOfGame = false;
	isPause = false;
	view->reset(sf::FloatRect(0, 0, 550, 700));
	hero->speedY = -50.f;
	animationCounter = 0;
	unstablePlatesCounter = 0;
	offsetFallBonus.x = 0.f;
	offsetFallBonus.y = 0.f;

	hole = new sf::Sprite;
	hole->setTextureRect(sf::IntRect(0, 0, 60, 54));
	hole->setTexture(assets->HOLE_TEXTURE);
	holePosition.x = float(rand() % (550 - HOLE_WIDTH));
	holePosition.y = -1.f * float(rand() % 15000) - 10.f * 750.f;
	hole->setPosition(holePosition.x, holePosition.y);

	scoreNum.setFont(assets->font);
	scoreNum.setCharacterSize(20);
	scoreNum.setStyle(sf::Text::Bold);
	scoreNum.setColor(sf::Color(0, 0, 0));

	background = new sf::Sprite;
	background->setTextureRect(sf::IntRect(0, 0, 550, 700));
	background->setTexture(assets->BACKGROUND_TEXTURE);

	initBonuses();
	resetGame();
}

gameScene::~gameScene()
{
	delete background;
	background = NULL;
}

SGameResult gameScene::onGameFrame(sf::RenderWindow & window) // TODO: Need refactoring!
{
	if (!endOfGame)
	{
		result.collision = Collision::NO_COLLISION;
		keyPressed(window);
		update(window);
		window.setView(*view);
		render(window);
		window.display();

		result.points = points;
		if (isPause)
		{
			result.status = gameStatus::PAUSE_SCENE;
			isPause = false;
		}
		else
		{
			result.status = gameStatus::GAME_SCENE;
		}
		return result;
	}
	else
	{
		view->setCenter(275, 350);
		window.setView(*view);
		result.points = points;
		result.status = gameStatus::GAME_OVER_SCENE;
		resetGame();
		return result;
	}
	//window.setView(*view);
	//return result;
}

void gameScene::moveDoodle(void)
{
	sf::Vector2f position(0.f, 0.f);
	moveDoodleHorizontal(position.x);
	moveDoodleVertical(position.y);
	hero->body->move(position);
}

void gameScene::moveDoodleHorizontal(float & positionX)
{
	if (hero->direction.x == DirectionX::RIGHT)
	{
		positionX += STEP;
		hero->body->setTexture(assets->DOODLE_JUMP_RIGHT_TEXTURE);
	}
	else if (hero->direction.x == DirectionX::LEFT)
	{
		positionX -= STEP;
		hero->body->setTexture(assets->DOODLE_JUMP_LEFT_TEXTURE);
	}
}

void gameScene::moveDoodleVertical(float & positionY)
{
	if (hero->speedY < 0)
	{
		hero->speedY += ACCELERATION;
		positionY = hero->speedY;

		if (hero->body->getPosition().y < hero->positionBeforeDown.y)
		{
			hero->positionBeforeDown = hero->body->getPosition();
		}
	}
	else
	{
		float testingFall = checkDoodleFall();
		if (testingFall == 0)
		{
			actualBonus = BonusType::NO;
			hero->speedY += ACCELERATION / 8;
			positionY = hero->speedY;
			if (hero->body->getPosition().y < hero->positionBeforeDown.y)
			{
				hero->positionBeforeDown = hero->body->getPosition();
			}
		}
		else
		{
			hero->speedY = -testingFall;
		}
	}
}

void gameScene::animateBonus(void)
{
	animateSpring();
	animateTrampoline();
	animateRocket();
	animateHatHelicopter();
}

void gameScene::animateSpring(void)
{

}

void gameScene::animateTrampoline(void)
{
	if (actualBonus == BonusType::TRAMPOLINE)
	{
		if (hero->speedY >= 0)
		{
			hero->body->setRotation(0.f);
			actualBonus = BonusType::NO;
		}
		else
		{
			hero->body->rotate(360.f / TRAMPLANE_DELTA_HEIGHT);
		}
	}

}

void gameScene::animateRocket(void)
{
	if (actualBonus == BonusType::ROCKET)
	{
		if ((hero->speedY >= 0) || (bonus[actualBonusId].body->getPosition().y < view->getCenter().y - 350 - ROCKET_HEIGHT))
		{
			animationCounter = 0;
			actualBonus = BonusType::NO;
			offsetFallBonus.x = 0.f;
			offsetFallBonus.y = 0.f;
			bonus[actualBonusId].body->setRotation(0);
		}

		if ((animationCounter >= 0) && (animationCounter <= 2))
		{
			delete bonus[actualBonusId].body;
			bonus[actualBonusId].body = new sf::Sprite;
			if (hero->lastDirectionX == DirectionX::RIGHT)
			{
				bonus[actualBonusId].body->setTexture(assets->ROCKET_0_LEFT_TEXTURE);
			}
			else if (hero->lastDirectionX == DirectionX::LEFT)
			{
				bonus[actualBonusId].body->setTexture(assets->ROCKET_0_RIGHT_TEXTURE);
			}
			++animationCounter;
		}
		if ((animationCounter >= 3) && (animationCounter <= 5))
		{
			delete bonus[actualBonusId].body;
			bonus[actualBonusId].body = new sf::Sprite;
			if (hero->lastDirectionX == DirectionX::RIGHT)
			{
				bonus[actualBonusId].body->setTexture(assets->ROCKET_1_LEFT_TEXTURE);
			}
			else if (hero->lastDirectionX == DirectionX::LEFT)
			{
				bonus[actualBonusId].body->setTexture(assets->ROCKET_1_RIGHT_TEXTURE);
			}
			++animationCounter;
		}
		if ((animationCounter >= 6) && (animationCounter <= 8))
		{
			delete bonus[actualBonusId].body;
			bonus[actualBonusId].body = new sf::Sprite;
			if (hero->lastDirectionX == DirectionX::RIGHT)
			{
				bonus[actualBonusId].body->setTexture(assets->ROCKET_2_LEFT_TEXTURE);
			}
			else if (hero->lastDirectionX == DirectionX::LEFT)
			{
				bonus[actualBonusId].body->setTexture(assets->ROCKET_2_RIGHT_TEXTURE);
			}
			++animationCounter;
		}
		if ((animationCounter >= 9) && (animationCounter <= 11))
		{
			delete bonus[actualBonusId].body;
			bonus[actualBonusId].body = new sf::Sprite;
			if (hero->lastDirectionX == DirectionX::RIGHT)
			{
				bonus[actualBonusId].body->setTexture(assets->ROCKET_3_LEFT_TEXTURE);
			}
			else if (hero->lastDirectionX == DirectionX::LEFT)
			{
				bonus[actualBonusId].body->setTexture(assets->ROCKET_3_RIGHT_TEXTURE);
			}
			++animationCounter;
		}
		if (animationCounter == 11)
		{
			animationCounter = 0;
		}

		if ((animationCounter >= 0) && (animationCounter <= 11) && (actualBonus != BonusType::NO) && (hero->speedY < -0.05f * ROCKET_DELTA_HEIGHT))
		{
			if (hero->lastDirectionX == DirectionX::RIGHT)
			{
				if ((animationCounter >= 0) && (animationCounter <= 2))
				{
					bonus[actualBonusId].body->setPosition(hero->body->getPosition().x - 13, hero->body->getPosition().y);
				}
				if ((animationCounter >= 3) && (animationCounter <= 5))
				{
					bonus[actualBonusId].body->setPosition(hero->body->getPosition().x - 13, hero->body->getPosition().y);
				}
				if ((animationCounter >= 6) && (animationCounter <= 8))
				{
					bonus[actualBonusId].body->setPosition(hero->body->getPosition().x - 15, hero->body->getPosition().y);
				}
				if ((animationCounter >= 9) && (animationCounter <= 11))
				{
					bonus[actualBonusId].body->setPosition(hero->body->getPosition().x - 17, hero->body->getPosition().y);
				}
			}
			else if (hero->lastDirectionX == DirectionX::LEFT)
			{
				if ((animationCounter >= 0) && (animationCounter <= 2))
				{
					bonus[actualBonusId].body->setPosition(hero->body->getPosition().x + DOODLE_WIDTH + 1, hero->body->getPosition().y);
				}
				if ((animationCounter >= 3) && (animationCounter <= 5))
				{
					bonus[actualBonusId].body->setPosition(hero->body->getPosition().x + DOODLE_WIDTH + 1, hero->body->getPosition().y);
				}
				if ((animationCounter >= 6) && (animationCounter <= 8))
				{
					bonus[actualBonusId].body->setPosition(hero->body->getPosition().x + DOODLE_WIDTH, hero->body->getPosition().y);
				}
				if ((animationCounter >= 9) && (animationCounter <= 11))
				{
					bonus[actualBonusId].body->setPosition(hero->body->getPosition().x + DOODLE_WIDTH - 5, hero->body->getPosition().y);
				}
			}
		}

		if (hero->speedY >= -0.05f * ROCKET_DELTA_HEIGHT)
		{
			bonus[actualBonusId].body = new sf::Sprite;
			bonus[actualBonusId].body->setTexture(assets->ROCKET_NONE_TEXTURE);
			if (actualBonus != BonusType::NO)
			{
				bonus[actualBonusId].body->setPosition(hero->body->getPosition().x, hero->body->getPosition().y);
			}
			bonus[actualBonusId].body->rotate(-10.f);
			offsetFallBonus.x += -2.f * STEP;
			offsetFallBonus.y += 6.f * STEP;
			bonus[actualBonusId].body->move(sf::Vector2f(offsetFallBonus));
		}
	}
}

void gameScene::animateHatHelicopter(void)
{
	if (actualBonus == BonusType::HAT_HELICOPTER)
	{
		if ((hero->speedY >= 0) || (bonus[actualBonusId].body->getPosition().y < view->getCenter().y - 350 - HAT_HELICOPTER_HEIGHT))
		{
			animationCounter = 0;
			actualBonus = BonusType::NO;
			offsetFallBonus.x = 0.f;
			offsetFallBonus.y = 0.f;
			bonus[actualBonusId].body->setRotation(0);
		}

		if ((animationCounter >= 0) && (animationCounter <= 5))
		{
			delete bonus[actualBonusId].body;
			bonus[actualBonusId].body = new sf::Sprite;
			bonus[actualBonusId].body->setTexture(assets->HAT_HELOCPTER_FLY_LEFT_TEXTURE);
			++animationCounter;
		}
		if ((animationCounter >= 6) && (animationCounter <= 10))
		{
			delete bonus[actualBonusId].body;
			bonus[actualBonusId].body = new sf::Sprite;
			bonus[actualBonusId].body->setTexture(assets->HAT_HELOCPTER_DIAGONAL_LEFT_TEXTURE);
			++animationCounter;
		}
		if ((animationCounter >= 11) && (animationCounter <= 15))
		{
			delete bonus[actualBonusId].body;
			bonus[actualBonusId].body = new sf::Sprite;
			bonus[actualBonusId].body->setTexture(assets->HAT_HELOCPTER_DIAGONAL_RIGHT_TEXTURE);
			++animationCounter;
		}
		if ((animationCounter >= 16) && (animationCounter <= 20))
		{
			delete bonus[actualBonusId].body;
			bonus[actualBonusId].body = new sf::Sprite;
			bonus[actualBonusId].body->setTexture(assets->HAT_HELOCPTER_FLY_RIGHT_TEXTURE);
			++animationCounter;
		}
		if (animationCounter == 20)
		{
			animationCounter = 0;
		}

		if ((animationCounter >= 0) && (animationCounter <= 20) && (actualBonus != BonusType::NO) && (hero->speedY < -0.05f * HAT_HELICOPTER_DELTA_HEIGHT))
		{
			if (hero->lastDirectionX == DirectionX::RIGHT)
			{
				bonus[actualBonusId].body->setPosition(hero->body->getPosition().x, hero->body->getPosition().y - 14);
			}
			else if (hero->lastDirectionX == DirectionX::LEFT)
			{
				bonus[actualBonusId].body->setPosition(hero->body->getPosition().x + 15, hero->body->getPosition().y - 14);
			}
		}

		if (hero->speedY >= -0.05f * HAT_HELICOPTER_DELTA_HEIGHT)
		{
			bonus[actualBonusId].body = new sf::Sprite;
			bonus[actualBonusId].body->setTexture(assets->HAT_HELOCPTER_NONE_LEFT_TEXTURE);
			if (actualBonus != BonusType::NO)
			{
				bonus[actualBonusId].body->setPosition(hero->body->getPosition().x, hero->body->getPosition().y - 14);
			}
			bonus[actualBonusId].body->rotate(-10.f);
			offsetFallBonus.x += -2.f * STEP;
			offsetFallBonus.y += 6.f * STEP;
			bonus[actualBonusId].body->move(sf::Vector2f(offsetFallBonus));
		}
	}
}

void gameScene::update(sf::RenderWindow & window)
{
	moveDoodle();
	sf::Vector2f doodlePosition = hero->body->getPosition();
	checkCylinderEffect(doodlePosition);
	animateBonus();

	if ((hero->speedY <= 0) && (doodlePosition.y <= hero->positionBeforeDown.y))
	{
		view->setCenter(275, doodlePosition.y);
		background->setPosition(0, doodlePosition.y - 350);
		scoreNum.setPosition(0, doodlePosition.y - 350);
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

void gameScene::resetGame(void)
{
	view->reset(sf::FloatRect(0, 0, 550, 700));
	scoreNum.setPosition(0, 0);
	endOfGame = false;
	points = 0;
	actualBonus = BonusType::NO;
	offsetFallBonus.x = 0.f;
	offsetFallBonus.y = 0.f;

	hero->body->setTexture(assets->DOODLE_LEFT_TEXTURE);
	hero->body->setPosition(260, 350);
	hero->speedY = -50.f;
	hero->lastDirectionX = DirectionX::LEFT;
	animationCounter = 0;
	hero->positionBeforeDown.y = hero->body->getPosition().y;
	view->setCenter(275, 350);

	plate[0]->body->setPosition(275 - PLATE_WIDTH/2, 700 - PLATE_HEIGHT);
	for (int i = 1; i < NUMBER_PLATES/2; ++(++i))
	{
		plate[i]->body = new sf::Sprite;
		plate[i]->type = PlateType::STATIC;
		plate[i]->body->setTexture(assets->PLATE_STATIC_TEXTURE);

		float y1 = float((rand() % 152) + 90);
		float x1 = (sqrt(484*484 - y1*y1))/2;
		float y2 = float((rand() % 152) + 90);
		float x2 = (sqrt(484 * 484 - y1*y1)) / 2;
		if ((plate[i - 1]->body->getPosition().x + x1 >= 550 - PLATE_WIDTH) && (plate[i - 1]->body->getPosition().x - x1 <= 0))
		{
			x1 = float(rand() % (550-PLATE_WIDTH));
		}

		plate[i]->body->setPosition(x1, plate[i-1]->body->getPosition().y - y1);
		plate[i]->body->setPosition(x2, plate[i-1]->body->getPosition().y - y2);
	}
	view->setCenter(275, 350);
	initBonuses();
}

void gameScene::generPlates(void)
{
	if (plate[0]->body->getPosition().y > view->getCenter().x + 350.f)
	{
		plate[0]->type = PlateType::STATIC;
		plate[0]->body->setTexture(assets->PLATE_DYNAMIC_TEXTURE);
		plate[0]->body->setPosition(float(rand() % (550 - PLATE_WIDTH)), view->getCenter().y - 350 - PLATE_HEIGHT);
	}

	sf::Vector2f platePosition[NUMBER_PLATES];
	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		platePosition[i] = plate[i]->body->getPosition();
	}
	std::array<float, NUMBER_PLATES> platePositionY;
	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		platePositionY[i] = plate[i]->body->getPosition().y;
	}
	std::sort(platePositionY.begin(), platePositionY.end(), std::greater<int>());

	for (int i = 1; i < NUMBER_PLATES / 2; ++(++i))
	{
		float y1 = float((rand() % 152) + 90);
		float x1 = (sqrt(484 * 484 - y1 * y1)) / 2;


		if (platePosition[i].y > view->getCenter().y + 350.f)
		{
			if ((plate[i]->body->getPosition().x + x1 >= 550 - PLATE_WIDTH) && (plate[i]->body->getPosition().x - x1 <= 0))
			{
				x1 = float(rand() % (550 - PLATE_WIDTH));
			}

			if ((plate[i]->type == PlateType::UNSTABLE) || (plate[i]->type == PlateType::UNSTABLE_DYNAMIC_X))
			{
				--unstablePlatesCounter;
			}

			plate[i]->body->setRotation(0);
			switch (rand() % 3)
			{
			case 0:
				plate[i]->type = PlateType::STATIC;
				plate[i]->body->setTexture(assets->PLATE_STATIC_TEXTURE);
				plate[i]->speedX = 0;
				break;
			case 1:
				plate[i]->type = PlateType::STATIC_DYNAMIC_X;
				plate[i]->body->setTexture(assets->PLATE_DYNAMIC_TEXTURE);

				plate[i]->speedX = (rand() % 3) + 1;
				if (rand() % 2)
				{
					plate[i]->speedX *= -1;
				}
				break;
			case 2:
				plate[i]->type = PlateType::CLOUD;
				plate[i]->body->setTexture(assets->PLATE_CLOUD_TEXTURE);
				plate[i]->speedX = 0;
				break;
			}
			plate[i]->body->setPosition(x1, platePositionY[NUMBER_PLATES-1] - y1);

			for (int j = 1; j < NUMBER_PLATES/ 2; ++(++j)) // NOTE: Oh my God...What the f*ck r u doing?
			{
				float y2 = float((rand() % 152) + 90);
				float x2 = float(rand() % (550 - PLATE_WIDTH));

				if (platePosition[j].y > view->getCenter().y + 350.f)
				{
					/*int divider;
					if (unstablePlatesCounter < 1)
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
					}*/

					plate[i]->body->setRotation(0);
					switch (rand() % 3)
					{
					case 0:
						plate[i]->type = PlateType::STATIC;
						plate[i]->body->setTexture(assets->PLATE_STATIC_TEXTURE);
						plate[i]->speedX = 0;
						break;
					case 1:
						plate[i]->type = PlateType::STATIC_DYNAMIC_X;
						plate[i]->body->setTexture(assets->PLATE_DYNAMIC_TEXTURE);

						plate[i]->speedX = (rand() % 3) + 1;
						if (rand() % 2)
						{
							plate[i]->speedX *= -1;
						}
						break;
					case 2:
						plate[i]->type = PlateType::CLOUD;
						plate[i]->body->setTexture(assets->PLATE_CLOUD_TEXTURE);
						plate[i]->speedX = 0;
						break;
					case 3:
						plate[i]->type = PlateType::UNSTABLE;
						plate[i]->body->setTexture(assets->PLATE_UNSTABLE_TEXTURE);
						plate[i]->speedX = 0;
						++unstablePlatesCounter;
						break;
					case 4:
						plate[i]->type = PlateType::UNSTABLE_DYNAMIC_X;
						plate[i]->body->setTexture(assets->PLATE_UNSTABLE_TEXTURE);

						plate[i]->speedX = (rand() % 3) + 1;
						if (rand() % 2)
						{
							plate[i]->speedX *= -1;
						}
						++unstablePlatesCounter;
						break;
					}

					plate[j]->body->setPosition(x2, platePositionY[NUMBER_PLATES - 1] - y1);
					break;
				}
			}
		}
	}
}

void gameScene::generHole(void)
{
	if (hole->getPosition().y >= view->getCenter().y + 350.f)
	{
		holePosition.x = float(rand() % (550 - HOLE_WIDTH));
		holePosition.y = hero->body->getPosition().y -1.f * float(rand() % 15000) - 10.f * 750.f;
		hole->setPosition(sf::Vector2f(holePosition.x, holePosition.y));
	}
}

void gameScene::generBonuses(void)
{
	sf::Vector2f bonusPosition[NUMBER_BONUSES];
	sf::Vector2f platePosition;

	for (int bonusIndex = 0; bonusIndex < NUMBER_BONUSES; ++bonusIndex)
	{
		bonusPosition[bonusIndex] = bonus[bonusIndex].body->getPosition();

		if (bonusPosition[bonusIndex].y > view->getCenter().y + 350)
		{
			for (int plateIndex = 0; plateIndex < NUMBER_PLATES; ++plateIndex)
			{
				platePosition = plate[plateIndex]->body->getPosition();
				if ((platePosition.y < view->getCenter().y - 350 - ROCKET_HEIGHT) && ((plate[plateIndex]->type == PlateType::STATIC) || (plate[plateIndex]->type == PlateType::STATIC_DYNAMIC_X)))
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

void gameScene::dropUnstablePlates(void)
{
	for (int plateIndex = 0; plateIndex < NUMBER_PLATES; ++plateIndex)
	{
		if (plate[plateIndex]->fallingPlate == true)
		{
			plate[plateIndex]->body->rotate(-1.f);
			plate[plateIndex]->body->move(sf::Vector2f(-1 * STEP, 4 * STEP));
			if (plate[plateIndex]->body->getPosition().y >= view->getCenter().y + 350)
			{
				plate[plateIndex]->body->setRotation(0);
				plate[plateIndex]->fallingPlate = false;
			}
		}
	}
}

bool gameScene::checkGameEnd(void)
{
	sf::Vector2f doodlePosition = hero->body->getPosition();
	if ((checkCollisionHole(doodlePosition) == Collision::COLLISION_HOLE) && ((actualBonus == BonusType::NO)))
	{
		PlaySound(L"sounds/crnarupa.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		return true;
	}
	if ((doodlePosition.y <= view->getCenter().y + 350.f))
	{
		return false;
	}
	PlaySound(L"sounds/pada.wav", NULL, SND_ASYNC | SND_NODEFAULT);
	return true;
}

void gameScene::render(sf::RenderWindow & window)
{
	//for (std::vector<sf::Sprite*>::const_iterator it = needRender.begin(); it != needRender.end(); ++it) // NOTE: try to use std::vector
	window.clear(sf::Color(255, 255, 255));

	window.draw(*background);
	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		window.draw(*plate[i]->body);
	}
	window.draw(*hero->body);
	for (int i = 0; i < NUMBER_BONUSES; ++i)
	{
		window.draw(*bonus[i].body);
	}
	window.draw(*hole);
	scoreNum.setString("Score: " + std::to_string(points));
	window.draw(scoreNum);
}

void gameScene::keyPressed(sf::RenderWindow & window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			hero->direction.x = DirectionX::LEFT;
			hero->lastDirectionX = DirectionX::LEFT;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			hero->direction.x = DirectionX::RIGHT;
			hero->lastDirectionX = DirectionX::RIGHT;
		}
		else
		{
			hero->direction.x = DirectionX::NONE;
		}

		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		{
			isPause = true;
		}
	}
}

void gameScene::moveDynamicPlates(void)
{
	sf::Vector2f platePosition[NUMBER_PLATES];

	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		platePosition[i] = plate[i]->body->getPosition();
		if (plate[i]->speedX != 0)
		{
			if (plate[i]->speedX < 0)
			{
				if (platePosition[i].x <= plate[i]->speedX)
				{
					plate[i]->speedX *= -1;
				}
			}
			if (plate[i]->speedX > 0)
			{
				if (platePosition[i].x >= 550 - PLATE_WIDTH - plate[i]->speedX)
				{
					plate[i]->speedX *= -1;
				}
			}
			plate[i]->body->move(float(plate[i]->speedX), 0.f);
		}
	}
}

void gameScene::moveBonuses(void)
{
	for (int bonusIndex = 0; bonusIndex < NUMBER_BONUSES; ++bonusIndex)
	{
		bonus[bonusIndex].speedX = plate[bonus[bonusIndex].plateIndex]->speedX;

		if (bonus[bonusIndex].speedX != 0)
		{
			bonus[bonusIndex].body->move(float(bonus[bonusIndex].speedX), 0.f);
		}
	}
}

void gameScene::checkCylinderEffect(sf::Vector2f & doodlePosition)
{
	if (doodlePosition.x <= -DOODLE_WIDTH)
	{
		hero->body->setPosition(550 - DOODLE_WIDTH, doodlePosition.y);
	}
	if (doodlePosition.x >= 550)
	{
		hero->body->setPosition(0, doodlePosition.y);
	}
}

void gameScene::initBonuses(void)
{
	std::vector<sf::Vector2f> platePosition;
	for (int plateIndex = 0; plateIndex < NUMBER_PLATES; ++plateIndex)
	{
		platePosition.push_back(plate[plateIndex]->body->getPosition());
	}

	for (int bonusIndex = 0; bonusIndex < NUMBER_BONUSES; ++bonusIndex)
	{
		int plateIndex = rand() % platePosition.size();
		BonusType type = (rand() % 2) ? BonusType::SPRING : BonusType::TRAMPOLINE;
		buildBonus(type, bonusIndex, platePosition[plateIndex], plateIndex);
	}
}

void gameScene::buildBonus(BonusType bonusType, int bonusIndex, sf::Vector2f platePosition, int plateIndex)
{
	bonus[bonusIndex].plateIndex = plateIndex;
	delete bonus[bonusIndex].body;
	bonus[bonusIndex].body = NULL;

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

float gameScene::checkDoodleFall(void)
{
	sf::Vector2f doodlePosition = hero->body->getPosition();
	sf::Vector2f platePosition[NUMBER_PLATES];
	sf::Vector2f bonusPosition[NUMBER_BONUSES];
	Collision collision = Collision::NO_COLLISION;

	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		platePosition[i] = plate[i]->body->getPosition();
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
		result.collision = Collision::COLLISION_PLATE;
		PlaySound(L"sounds/jump.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		return PLATE_DELTA_HEIGHT;
	case Collision::COLLISION_SPRING:
		actualBonus = BonusType::SPRING;
		result.collision = Collision::COLLISION_SPRING;
		PlaySound(L"sounds/feder.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		return SPRING_DELTA_HEIGHT;
	case Collision::COLLISION_TRAMPLANE:
		actualBonus = BonusType::TRAMPOLINE;
		result.collision = Collision::COLLISION_TRAMPLANE;
		PlaySound(L"sounds/trampoline.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		return TRAMPLANE_DELTA_HEIGHT;
	case Collision::COLLISION_HAT_HELICOPTER:
		actualBonus = BonusType::HAT_HELICOPTER;
		result.collision = Collision::COLLISION_HAT_HELICOPTER;
		PlaySound(L"sounds/propeller.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		return HAT_HELICOPTER_DELTA_HEIGHT;
	case Collision::COLLISION_ROCKET:
		actualBonus = BonusType::ROCKET;
		result.collision = Collision::COLLISION_ROCKET;
		PlaySound(L"sounds/jetpack.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		return ROCKET_DELTA_HEIGHT;
	default:
		result.collision = Collision::NO_COLLISION;
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
			if ((plate[i]->type == PlateType::UNSTABLE) || (plate[i]->type == PlateType::UNSTABLE_DYNAMIC_X))
			{
				plate[i]->fallingPlate = true;
				continue;
			}

			if (plate[i]->type == PlateType::CLOUD)
			{
				plate[i]->body->setPosition(100.f, 1000.f); // TODO: u know
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

Collision gameScene::checkCollisionBonus(sf::Vector2f & doodlePosition, sf::Vector2f bonusPosition[NUMBER_PLATES])
{
	for (int bonusIndex = 0; bonusIndex < NUMBER_BONUSES; ++bonusIndex)
	{
		switch (bonus[bonusIndex].type)
		{
		case BonusType::SPRING:
			if (((doodlePosition.y + DOODLE_HEIGHT >= bonusPosition[bonusIndex].y) && (doodlePosition.y + DOODLE_HEIGHT <= bonusPosition[bonusIndex].y + SPRING_HEIGHT)
				&& (doodlePosition.x + DOODLE_WIDTH >= bonusPosition[bonusIndex].x) && (doodlePosition.x - SPRING_WIDTH <= bonusPosition[bonusIndex].x)))
			{
				bonus[bonusIndex].body->setTexture(assets->SPRING_2_TEXTURE);
				actualBonusId = bonusIndex;
				return Collision::COLLISION_SPRING;
			}
			break;
		case BonusType::TRAMPOLINE:
			if (((doodlePosition.y + DOODLE_HEIGHT >= bonusPosition[bonusIndex].y) && (doodlePosition.y + DOODLE_HEIGHT <= bonusPosition[bonusIndex].y + TRAMPOLINE_HEIGHT)
				&& (doodlePosition.x + DOODLE_WIDTH >= bonusPosition[bonusIndex].x) && (doodlePosition.x - TRAMPOLINE_WIDTH <= bonusPosition[bonusIndex].x)))
			{
				actualBonusId = bonusIndex;
				return Collision::COLLISION_TRAMPLANE;
			}
			break;
		case BonusType::HAT_HELICOPTER:
			if (((doodlePosition.y + DOODLE_HEIGHT >= bonusPosition[bonusIndex].y) && (doodlePosition.y + DOODLE_HEIGHT <= bonusPosition[bonusIndex].y + HAT_HELICOPTER_HEIGHT)
				&& (doodlePosition.x + DOODLE_WIDTH >= bonusPosition[bonusIndex].x) && (doodlePosition.x - HAT_HELICOPTER_WIDTH <= bonusPosition[bonusIndex].x)))
			{
				actualBonusId = bonusIndex;
				if (hero->direction.x == DirectionX::RIGHT)
				{
					bonus[bonusIndex].body->setPosition(doodlePosition.x + 15, doodlePosition.y - 15);
				}
				else if ((hero->direction.x == DirectionX::LEFT) || (hero->direction.x == DirectionX::NONE))
				{
					bonus[bonusIndex].body->setPosition(doodlePosition.x + 15, doodlePosition.y - 15);
				}
				return Collision::COLLISION_HAT_HELICOPTER;
			}
			break;
		case BonusType::ROCKET:
			if (((doodlePosition.y + DOODLE_HEIGHT >= bonusPosition[bonusIndex].y) && (doodlePosition.y + DOODLE_HEIGHT <= bonusPosition[bonusIndex].y + ROCKET_HEIGHT)
				&& (doodlePosition.x + DOODLE_WIDTH >= bonusPosition[bonusIndex].x) && (doodlePosition.x - ROCKET_WIDTH <= bonusPosition[bonusIndex].x)))
			{
				actualBonusId = bonusIndex;

				if (hero->direction.x == DirectionX::RIGHT)
				{
					bonus[bonusIndex].body->setPosition(doodlePosition.x - ROCKET_WIDTH, doodlePosition.y);
				}
				else if ((hero->direction.x == DirectionX::LEFT) || (hero->direction.x == DirectionX::NONE))
				{
					bonus[bonusIndex].body->setPosition(doodlePosition.x + DOODLE_WIDTH, doodlePosition.y);
				}
				return Collision::COLLISION_ROCKET;
			}
			break;
		}
	}
	return Collision::NO_COLLISION;
}