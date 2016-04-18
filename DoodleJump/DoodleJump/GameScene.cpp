#include "stdafx.h"
#include "sheet.h"

GameScene::GameScene(Assets & assets, sf::View & view)
	:assets(&assets)
	,view(&view)
{
	hero = new Doodle(assets);
	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		plate[i] = new Plate(&assets);
	}

	actualBonus = BonusType::NO;
	points = 0;
	endOfGame = false;
	isPause = false;
	view.reset(sf::FloatRect(0, 0, 550, 700));
	hero->setSpeedY(-50.f);
	animationCounter = 0;
	unstablePlatesCounter = 0;
	offsetFallBonus.x = 0.f;
	offsetFallBonus.y = 0.f;
	isLeft = false;
	isRight = false;

	hole = new sf::Sprite;
	hole->setTextureRect(sf::IntRect(0, 0, 60, 54));
	hole->setTexture(assets.HOLE_TEXTURE);
	holePosition.x = float(rand() % (550 - HOLE_WIDTH));
	holePosition.y = -1.f * float(rand() % 15000) - 10.f * 750.f;
	hole->setPosition(holePosition.x, holePosition.y);

	scoreNum.setFont(assets.font);
	scoreNum.setCharacterSize(20);
	scoreNum.setStyle(sf::Text::Bold);
	scoreNum.setColor(sf::Color(0, 0, 0));

	background = new sf::Sprite;
	background->setTextureRect(sf::IntRect(0, 0, 550, 700));
	background->setTexture(assets.BACKGROUND_TEXTURE);

	initBonuses();
	resetGame();
}

GameScene::~GameScene()
{
	delete background;
	background = nullptr;
}

SGameResult GameScene::onGameFrame(sf::RenderWindow & window)
{
	if (result.status == GameStatus::GAME_OVER_SCENE)
	{
	resetGame();
	}
	result.collision = Collision::NO_COLLISION;

	if (!endOfGame)
	{
		if (isPause)
		{
			isPause = false;
			view->setCenter(WINDOW_WIDTH/2, background->getPosition().y + WINDOW_HEIGHT/2);
			window.setView(*view);
		}
		checkEvents(window);
		update(window);
		window.setView(*view);
		render(window);
		window.display();

		result.points = points;
		if (isPause)
		{
			view->setCenter(275, 350); 
			window.setView(*view);
			result.status = GameStatus::PAUSE_SCENE;
		}
		else
		{
			result.status = GameStatus::GAME_SCENE;
		}
	}
	else
	{
		view->setCenter(275, 350);
		window.setView(*view);
		result.points = points;
		result.status = GameStatus::GAME_OVER_SCENE;
		
	}
	return result;
}

void GameScene::moveDoodle(void)
{
	sf::Vector2f position(0.f, 0.f);
	moveDoodleHorizontal(position.x);
	moveDoodleVertical(position.y);
	hero->move(position);
}

void GameScene::moveDoodleHorizontal(float & positionX)
{
	DirectionX doodleDirection = hero->getDirection();
	if (doodleDirection == DirectionX::RIGHT)
	{
		positionX += STEP;
	}
	else if (doodleDirection  == DirectionX::LEFT)
	{
		positionX -= STEP;
	}
}

void GameScene::moveDoodleVertical(float & positionY)
{
	if (hero->getSpeedY() < 0)
	{
		hero->setSpeedY(hero->getSpeedY() + ACCELERATION);
		positionY = hero->getSpeedY();
		
		if (hero->getPosition().y < hero->getPositionBeforeDown().y)
		{
			hero->setPositionBeforeDown(hero->getPosition());
		}
	}
	else
	{
		float testingFall = checkDoodleFall();
		if (testingFall == 0)
		{
			actualBonus = BonusType::NO;
			hero->setSpeedY(hero->getSpeedY() + ACCELERATION / 8);
			positionY = hero->getSpeedY();
			if (hero->getPosition().y < hero->getPositionBeforeDown().y)
			{
				hero->setPositionBeforeDown(hero->getPosition());
			}
		}
		else
		{
			hero->setSpeedY(-testingFall);
		}
	}
}

void GameScene::animateBonus(void)
{
	if (actualBonus != BonusType::NO)
	{
		switch (actualBonus)
		{
		case BonusType::SPRING:
			animateSpring();
			break;
		case BonusType::TRAMPOLINE:
			animateTrampoline();
			break;
		case BonusType::ROCKET:
			animateRocket();
			break;
		case BonusType::HAT_HELICOPTER:
			animateHatHelicopter();
			break;
		default:
			break;
		}
	}
}

void GameScene::animateSpring(void)
{
	if ((hero->getSpeedY() >= 0) || (bonus[actualBonusId].getPosition().y < view->getCenter().y - 350 - SPRING_HEIGHT))
	{
		actualBonus = BonusType::NO;
	}
	else
	{
		bonus[actualBonusId].setPosition(sf::Vector2f(bonus[actualBonusId].getPosition().x, bonus[actualBonusId].getPosition().y - 4.f));
		bonus[actualBonusId].setTexture(assets->SPRING_2_TEXTURE);
	}
}

void GameScene::animateTrampoline(void)
{
	if (hero->getSpeedY() >= 0)
	{
		hero->setRotation(0.f);
		actualBonus = BonusType::NO;
	}
	else
	{
		hero->rotate(360.f / TRAMPLANE_DELTA_HEIGHT);
	}
}

void GameScene::animateRocket(void)
{
	DirectionX doodleLastDirection = hero->getLastDirection();
	if ((hero->getSpeedY() >= 0) || (bonus[actualBonusId].getPosition().y < view->getCenter().y - 350 - ROCKET_HEIGHT))
	{
		animationCounter = 0;
		actualBonus = BonusType::NO;
		offsetFallBonus.x = 0.f;
		offsetFallBonus.y = 0.f;
		bonus[actualBonusId].setRotation(0.f);
		bonus[actualBonusId].move(sf::Vector2f(0.f, float(WINDOW_HEIGHT)));
	}

	if ((animationCounter >= 0) && (animationCounter <= 2))
	{
		if (doodleLastDirection == DirectionX::RIGHT)
		{
			bonus[actualBonusId].setTexture(assets->ROCKET_0_LEFT_TEXTURE);
		}
		else if (doodleLastDirection == DirectionX::LEFT)
		{
			bonus[actualBonusId].setTexture(assets->ROCKET_0_RIGHT_TEXTURE);
		}
		++animationCounter;
	}
	if ((animationCounter >= 3) && (animationCounter <= 5))
	{
		if (doodleLastDirection == DirectionX::RIGHT)
		{
			bonus[actualBonusId].setTexture(assets->ROCKET_1_LEFT_TEXTURE);
		}
		else if (doodleLastDirection == DirectionX::LEFT)
		{
			bonus[actualBonusId].setTexture(assets->ROCKET_1_RIGHT_TEXTURE);
		}
		++animationCounter;
	}
	if ((animationCounter >= 6) && (animationCounter <= 8))
	{
		if (doodleLastDirection == DirectionX::RIGHT)
		{
			bonus[actualBonusId].setTexture(assets->ROCKET_2_LEFT_TEXTURE);
		}
		else if (doodleLastDirection == DirectionX::LEFT)
		{
			bonus[actualBonusId].setTexture(assets->ROCKET_2_RIGHT_TEXTURE);
		}
		++animationCounter;
	}
	if ((animationCounter >= 9) && (animationCounter <= 11))
	{
		if (doodleLastDirection == DirectionX::RIGHT)
		{
			bonus[actualBonusId].setTexture(assets->ROCKET_3_LEFT_TEXTURE);
		}
		else if (doodleLastDirection == DirectionX::LEFT)
		{
			bonus[actualBonusId].setTexture(assets->ROCKET_3_RIGHT_TEXTURE);
		}
		++animationCounter;
	}
	if (animationCounter == 11)
	{
		animationCounter = 0;
	}

	if ((animationCounter >= 0) && (animationCounter <= 11) && (actualBonus != BonusType::NO) && (hero->getSpeedY() < -0.05f * ROCKET_DELTA_HEIGHT))
	{
		if (doodleLastDirection == DirectionX::RIGHT)
		{
			if ((animationCounter >= 0) && (animationCounter <= 2))
			{
				bonus[actualBonusId].setPosition(sf::Vector2f(hero->getPosition().x - 13, hero->getPosition().y));
			}
			if ((animationCounter >= 3) && (animationCounter <= 5))
			{
				bonus[actualBonusId].setPosition(sf::Vector2f(hero->getPosition().x - 13, hero->getPosition().y));
			}
			if ((animationCounter >= 6) && (animationCounter <= 8))
			{
				bonus[actualBonusId].setPosition(sf::Vector2f(hero->getPosition().x - 15, hero->getPosition().y));
			}
			if ((animationCounter >= 9) && (animationCounter <= 11))
			{
				bonus[actualBonusId].setPosition(sf::Vector2f(hero->getPosition().x - 17, hero->getPosition().y));
			}
		}
		else if (doodleLastDirection == DirectionX::LEFT)
		{
			if ((animationCounter >= 0) && (animationCounter <= 2))
			{
				bonus[actualBonusId].setPosition(sf::Vector2f(hero->getPosition().x + DOODLE_WIDTH + 1, hero->getPosition().y));
			}
			if ((animationCounter >= 3) && (animationCounter <= 5))
			{
				bonus[actualBonusId].setPosition(sf::Vector2f(hero->getPosition().x + DOODLE_WIDTH + 1, hero->getPosition().y));
			}
			if ((animationCounter >= 6) && (animationCounter <= 8))
			{
				bonus[actualBonusId].setPosition(sf::Vector2f(hero->getPosition().x + DOODLE_WIDTH, hero->getPosition().y));
			}
			if ((animationCounter >= 9) && (animationCounter <= 11))
			{
				bonus[actualBonusId].setPosition(sf::Vector2f(hero->getPosition().x + DOODLE_WIDTH - 5, hero->getPosition().y));
			}
		}
	}

	if (hero->getSpeedY() >= -0.05f * ROCKET_DELTA_HEIGHT && actualBonus != BonusType::NO)
	{
		bonus[actualBonusId].setTexture(assets->ROCKET_NONE_TEXTURE);
		if (actualBonus != BonusType::NO)
		{
			bonus[actualBonusId].setPosition(sf::Vector2f(hero->getPosition().x, hero->getPosition().y));
		}
		bonus[actualBonusId].rotate(-10.f);
		offsetFallBonus.x += -2.f * STEP;
		offsetFallBonus.y += 6.f * STEP;
		bonus[actualBonusId].move(sf::Vector2f(offsetFallBonus));
	}
}

void GameScene::animateHatHelicopter(void)
{
	if ((hero->getSpeedY() >= 0) || (bonus[actualBonusId].getPosition().y < view->getCenter().y - 350 - HAT_HELICOPTER_HEIGHT))
	{
		animationCounter = 0;
		actualBonus = BonusType::NO;
		offsetFallBonus.x = 0.f;
		offsetFallBonus.y = 0.f;
		bonus[actualBonusId].setRotation(0.f);
		bonus[actualBonusId].move(sf::Vector2f(0.f, float(WINDOW_HEIGHT)));
	}

	if (hero->getSpeedY() < -0.05f * HAT_HELICOPTER_DELTA_HEIGHT)
	{
		if ((animationCounter >= 0) && (animationCounter <= 5))
		{
			bonus[actualBonusId].setTexture(assets->HAT_HELOCPTER_FLY_LEFT_TEXTURE);
			++animationCounter;
		}
		if ((animationCounter >= 6) && (animationCounter <= 10))
		{
			bonus[actualBonusId].setTexture(assets->HAT_HELOCPTER_DIAGONAL_LEFT_TEXTURE);
			++animationCounter;
		}
		if ((animationCounter >= 11) && (animationCounter <= 15))
		{
			bonus[actualBonusId].setTexture(assets->HAT_HELOCPTER_DIAGONAL_RIGHT_TEXTURE);
			++animationCounter;
		}
		if ((animationCounter >= 16) && (animationCounter <= 20))
		{
			bonus[actualBonusId].setTexture(assets->HAT_HELOCPTER_FLY_RIGHT_TEXTURE);
			++animationCounter;
		}
		if (animationCounter == 20)
		{
			animationCounter = 0;
		}
	}
	if ((animationCounter >= 0) && (animationCounter <= 20) && (actualBonus != BonusType::NO) && (hero->getSpeedY() < -0.05f * HAT_HELICOPTER_DELTA_HEIGHT))
	{
		DirectionX doodleLastDirection = hero->getLastDirection();
		if (doodleLastDirection == DirectionX::RIGHT)
		{
			bonus[actualBonusId].setPosition(sf::Vector2f(hero->getPosition().x, hero->getPosition().y - 14));
		}
		else if (doodleLastDirection == DirectionX::LEFT)
		{
			bonus[actualBonusId].setPosition(sf::Vector2f(hero->getPosition().x + 15, hero->getPosition().y - 14));
		}
	}

	if (hero->getSpeedY() >= -0.05f * HAT_HELICOPTER_DELTA_HEIGHT && actualBonus != BonusType::NO)
	{
		bonus[actualBonusId].setTexture(assets->HAT_HELOCPTER_NONE_LEFT_TEXTURE);
		if (actualBonus != BonusType::NO)
		{
			bonus[actualBonusId].setPosition(sf::Vector2f(hero->getPosition().x, hero->getPosition().y - 14));
		}
		bonus[actualBonusId].rotate(-10.f);
		offsetFallBonus.x += -2.f * STEP;
		offsetFallBonus.y += 6.f * STEP;
		bonus[actualBonusId].move(sf::Vector2f(offsetFallBonus));
	}
}

void GameScene::update(sf::RenderWindow & window)
{
	(void)window;
	moveDoodle();
	hero->correctSkin();
	sf::Vector2f doodlePosition = hero->getPosition();
	checkCylinderEffect(doodlePosition);
	animateBonus();

	if ((hero->getSpeedY() <= 0) && (doodlePosition.y <= hero->getPositionBeforeDown().y))
	{
		view->setCenter(WINDOW_WIDTH/2, doodlePosition.y);
		background->setPosition(0, doodlePosition.y - WINDOW_HEIGHT / 2);
		scoreNum.setPosition(0, doodlePosition.y - WINDOW_HEIGHT / 2);
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

void GameScene::resetGame(void)
{
	view->reset(sf::FloatRect(0, 0, 550, 700));
	scoreNum.setPosition(0, 0);
	endOfGame = false;
	points = 0;
	actualBonus = BonusType::NO;
	offsetFallBonus.x = 0.f;
	offsetFallBonus.y = 0.f; 
	isLeft = false;
	isRight = false;
	hero->setDirection(DirectionX::NONE);

	hero->setTexture(assets->DOODLE_LEFT_TEXTURE);
	hero->setPosition(sf::Vector2f(260.f, 350.f));
	hero->setSpeedY(-50.f);
	animationCounter = 0;
	hero->setPositionBeforeDown(hero->getPosition());
	view->setCenter(275, 350);

	plate[0]->setPosition(sf::Vector2f(275 - PLATE_WIDTH/2, 700 - PLATE_HEIGHT));
	for (int i = 1; i < NUMBER_PLATES/2; ++(++i))
	{
		plate[i]->setType(PlateType::STATIC);
		plate[i]->setTexture(assets->PLATE_STATIC_TEXTURE);

		float y1 = float((rand() % 152) + 90);
		float x1 = (sqrt(484*484 - y1*y1))/2;
		float y2 = float((rand() % 152) + 90);
		float x2 = (sqrt(484 * 484 - y1*y1)) / 2;
		if ((plate[i - 1]->getPosition().x + x1 >= 550 - PLATE_WIDTH) && (plate[i - 1]->getPosition().x - x1 <= 0))
		{
			x1 = float(rand() % (550-PLATE_WIDTH));
		}

		plate[i]->setPosition(sf::Vector2f(x1, plate[i-1]->getPosition().y - y1));
		plate[i]->setPosition(sf::Vector2f(x2, plate[i-1]->getPosition().y - y2));
	}
	view->setCenter(275, 350);
	initBonuses();
}

void GameScene::generPlates(void)
{
	if (plate[0]->getPosition().y > view->getCenter().x + 350.f)
	{
		plate[0]->setType(PlateType::STATIC);
		plate[0]->setTexture(assets->PLATE_DYNAMIC_TEXTURE);
		plate[0]->setPosition(sf::Vector2f(float(rand() % (550 - PLATE_WIDTH)), view->getCenter().y - 350 - PLATE_HEIGHT));
	}

	sf::Vector2f platePosition[NUMBER_PLATES];
	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		platePosition[i] = plate[i]->getPosition();
	}
	std::array<float, NUMBER_PLATES> platePositionY;
	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		platePositionY[i] = plate[i]->getPosition().y;
	}
	std::sort(platePositionY.begin(), platePositionY.end(), std::greater<float>());

	for (int i = 1; i < NUMBER_PLATES / 2; ++(++i))
	{
		float y1 = float((rand() % 182) + 60);
		float x1 = float(rand() % (550 - PLATE_WIDTH));	//float x1 = (sqrt(484 * 484 - y1 * y1)) / 2;

		if (platePosition[i].y > view->getCenter().y + 350.f + ROCKET_HEIGHT)
		{
			if ((plate[i]->getPosition().x + x1 >= 550 - PLATE_WIDTH) && (plate[i]->getPosition().x - x1 <= 0))
			{
				x1 = float(rand() % (550 - PLATE_WIDTH));
			}

			if ((plate[i]->getType() == PlateType::UNSTABLE) || (plate[i]->getType() == PlateType::UNSTABLE_DYNAMIC_X))
			{
				--unstablePlatesCounter;
			}

			plate[i]->setRotation(0);
			switch (rand() % 3)
			{
			case 0:
				plate[i]->setType(PlateType::STATIC);
				plate[i]->setTexture(assets->PLATE_STATIC_TEXTURE);
				plate[i]->setSpeedX(0);
				break;
			case 1:
				plate[i]->setType(PlateType::STATIC_DYNAMIC_X);
				plate[i]->setTexture(assets->PLATE_DYNAMIC_TEXTURE);

				plate[i]->setSpeedX((rand() % 3) + 1);
				if (rand() % 2)
				{
					plate[i]->setSpeedX(-plate[i]->getSpeedX());
				}
				break;
			case 2:
				plate[i]->setType(PlateType::CLOUD);
				plate[i]->setTexture(assets->PLATE_CLOUD_TEXTURE);
				plate[i]->setSpeedX(0);
				break;
			}
			plate[i]->setPosition(sf::Vector2f(x1, platePositionY[NUMBER_PLATES-1] - y1));

			for (int j = 1; j < NUMBER_PLATES/ 2; ++(++j)) // NOTE: Oh my God...What the f*ck r u doing?
			{
				float y2 = float((rand() % 182) + 60);
				float x2 = float(rand() % (550 - PLATE_WIDTH));

				if (platePosition[j].y > view->getCenter().y + 350.f + ROCKET_HEIGHT)
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
					plate[i]->setRotation(0);
					switch (rand() % 3)
					{
					case 0:
						plate[i]->setType(PlateType::STATIC);
						plate[i]->setTexture(assets->PLATE_STATIC_TEXTURE);
						plate[i]->setSpeedX(0);
						break;
					case 1:
						plate[i]->setType(PlateType::STATIC_DYNAMIC_X);
						plate[i]->setTexture(assets->PLATE_DYNAMIC_TEXTURE);

						plate[i]->setSpeedX((rand() % 3) + 1);
						if (rand() % 2)
						{
							plate[i]->setSpeedX(-plate[i]->getSpeedX());
						}
						break;
					case 2:
						plate[i]->setType(PlateType::CLOUD);
						plate[i]->setTexture(assets->PLATE_CLOUD_TEXTURE);
						plate[i]->setSpeedX(0);
						break;
					case 3:
						plate[i]->setType(PlateType::UNSTABLE);
						plate[i]->setTexture(assets->PLATE_UNSTABLE_TEXTURE);
						plate[i]->setSpeedX(0);
						++unstablePlatesCounter;
						break;
					case 4:
						plate[i]->setType(PlateType::UNSTABLE_DYNAMIC_X);
						plate[i]->setTexture(assets->PLATE_UNSTABLE_TEXTURE);

						plate[i]->setSpeedX((rand() % 3) + 1);
						if (rand() % 2)
						{
							plate[i]->setSpeedX(-plate[i]->getSpeedX());
						}
						++unstablePlatesCounter;
						break;
					}

					plate[j]->setPosition(sf::Vector2f(x2, platePositionY[NUMBER_PLATES - 1] - y2));
					break;
				}
			}
		}
	}
}

void GameScene::generHole(void)
{
	if (hole->getPosition().y >= view->getCenter().y + 350.f)
	{
		holePosition.x = float(rand() % (550 - HOLE_WIDTH));
		holePosition.y = hero->getPosition().y -1.f * float(rand() % 15000) - 10.f * 750.f;
		hole->setPosition(sf::Vector2f(holePosition.x, holePosition.y));
	}
}

void GameScene::generBonuses(void)
{
	sf::Vector2f bonusPosition[NUMBER_BONUSES];
	sf::Vector2f platePosition;

	for (int bonusIndex = 0; bonusIndex < NUMBER_BONUSES; ++bonusIndex)
	{
		bonusPosition[bonusIndex] = bonus[bonusIndex].getPosition();

		if (bonusPosition[bonusIndex].y > view->getCenter().y + 350)
		{
			for (int plateIndex = 0; plateIndex < NUMBER_PLATES; ++plateIndex)
			{
				platePosition = plate[plateIndex]->getPosition();
				if ((platePosition.y < view->getCenter().y - 350 - ROCKET_HEIGHT) && ((plate[plateIndex]->getType() == PlateType::STATIC) || (plate[plateIndex]->getType() == PlateType::STATIC_DYNAMIC_X)))
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

void GameScene::dropUnstablePlates(void)
{
	for (int plateIndex = 0; plateIndex < NUMBER_PLATES; ++plateIndex)
	{
		if (plate[plateIndex]->getFallStatus() == true)
		{
			plate[plateIndex]->rotate(-1.f);
			plate[plateIndex]->move(sf::Vector2f(-1 * STEP, 4 * STEP));
			if (plate[plateIndex]->getPosition().y >= view->getCenter().y + 350)
			{
				plate[plateIndex]->setRotation(0);
				plate[plateIndex]->setFallStatus(false);
			}
		}
	}
}

bool GameScene::checkGameEnd(void)
{
	sf::Vector2f doodlePosition = hero->getPosition();
	if ((checkCollisionHole(doodlePosition) == Collision::COLLISION_HOLE) && ((actualBonus == BonusType::NO)))
	{
		PlaySound(L"sounds/crnarupa.wav", nullptr, SND_ASYNC | SND_NODEFAULT);
		return true;
	}
	if (doodlePosition.y < view->getCenter().y + 350.f - DOODLE_HEIGHT)
	{
		return false;
	}
	PlaySound(L"sounds/pada.wav", nullptr, SND_ASYNC | SND_NODEFAULT);
	return true;
}

void GameScene::render(sf::RenderWindow & window)
{
	//for (std::vector<sf::Sprite*>::const_iterator it = needRender.begin(); it != needRender.end(); ++it) // NOTE: try to use std::vector
	window.clear(sf::Color(255, 255, 255));

	window.draw(*background);
	for (auto plate : plate)
	{
		plate->draw(window);
	}
	hero->draw(window);
	for (auto bonus : bonus)
	{
		bonus.draw(window);
	}
	window.draw(*hole);
	scoreNum.setString("Score: " + std::to_string(points));
	window.draw(scoreNum);
}

void GameScene::checkEvents(sf::RenderWindow & window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		checkKeyboard(event);

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

void GameScene::checkKeyboard(sf::Event event)
{
	bool isNeedUpdate = false;
	checkKeyPressed(event, isNeedUpdate);
	checkKeyRealesed(event, isNeedUpdate);

	if (isNeedUpdate)
	{
		hero->updateDirection(isLeft, isRight);
	}
}

void GameScene::checkKeyPressed(sf::Event event, bool & isNeedUpdate)
{
	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::A:
			isLeft = true;
			isNeedUpdate = true;
			break;
		case sf::Keyboard::D:
			isRight = true;
			isNeedUpdate = true;
			break;
		default:
			break;
		}
	}
}

void GameScene::checkKeyRealesed(sf::Event event, bool & isNeedUpdate)
{
	if (event.type == sf::Event::KeyReleased)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::A:
			isLeft = false;
			isNeedUpdate = true;
			break;
		case sf::Keyboard::D:
			isRight = false;
			isNeedUpdate = true;
			break;
		default:
			break;
		}
	}
}

void GameScene::moveDynamicPlates(void)
{
	sf::Vector2f platePosition[NUMBER_PLATES];

	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		platePosition[i] = plate[i]->getPosition();
		if (plate[i]->getSpeedX() != 0)
		{
			if (plate[i]->getSpeedX() < 0)
			{
				if (platePosition[i].x <= plate[i]->getSpeedX())
				{
					plate[i]->setSpeedX(-plate[i]->getSpeedX());
				}
			}
			if (plate[i]->getSpeedX() > 0)
			{
				if (platePosition[i].x >= 550 - PLATE_WIDTH - plate[i]->getSpeedX())
				{
					plate[i]->setSpeedX(-plate[i]->getSpeedX());
				}
			}
			plate[i]->move(sf::Vector2f(float(plate[i]->getSpeedX()), 0.f));
		}
	}
}

void GameScene::moveBonuses(void)
{
	for (int bonusIndex = 0; bonusIndex < NUMBER_BONUSES; ++bonusIndex)
	{
		bonus[bonusIndex].setSpeedX(plate[bonus[bonusIndex].getPlateIndex()]->getSpeedX());

		if (bonus[bonusIndex].getSpeedX() != 0)
		{
			bonus[bonusIndex].move(sf::Vector2f(float(bonus[bonusIndex].getSpeedX()), 0.f));
		}
	}
}

void GameScene::checkCylinderEffect(sf::Vector2f & doodlePosition)
{
	if (doodlePosition.x <= -DOODLE_WIDTH)
	{
		hero->setPosition(sf::Vector2f(float(550 - DOODLE_WIDTH), doodlePosition.y));
	}
	if (doodlePosition.x >= 550)
	{
		hero->setPosition(sf::Vector2f(0.f, doodlePosition.y));
	}
}

void GameScene::initBonuses(void)
{
	std::vector<sf::Vector2f> platePosition;
	for (int plateIndex = 0; plateIndex < NUMBER_PLATES; ++plateIndex)
	{
		platePosition.push_back(plate[plateIndex]->getPosition());
	}

	for (int bonusIndex = 0; bonusIndex < NUMBER_BONUSES; ++bonusIndex)
	{
		int plateIndex = rand() % platePosition.size();
		BonusType type = (rand() % 2) ? BonusType::SPRING : BonusType::TRAMPOLINE;
		buildBonus(type, bonusIndex, platePosition[plateIndex], plateIndex);
	}
}

void GameScene::buildBonus(BonusType bonusType, int bonusIndex, sf::Vector2f platePosition, int plateIndex)
{
	bonus[bonusIndex].setPlateIndex(plateIndex);
	bonus[bonusIndex].setRotation(0.f);

	switch (bonusType)
	{
	case BonusType::SPRING:
	{
		int x = rand() % (PLATE_WIDTH - SPRING_WIDTH);
		bonus[bonusIndex].setBonusType(BonusType::SPRING);
		bonus[bonusIndex].setPosition(sf::Vector2f(platePosition.x + x, platePosition.y - SPRING_HEIGHT));
		bonus[bonusIndex].setTexture(assets->SPRING_TEXTURE);
		break;
	}
	case BonusType::TRAMPOLINE:
	{
		int x = rand() % (PLATE_WIDTH - TRAMPOLINE_WIDTH);
		bonus[bonusIndex].setBonusType(BonusType::TRAMPOLINE);
		bonus[bonusIndex].setPosition(sf::Vector2f(platePosition.x + x, platePosition.y - TRAMPOLINE_HEIGHT));
		bonus[bonusIndex].setTexture(assets->TRAMPOLINE_TEXTURE);
		break;
	}
	case BonusType::HAT_HELICOPTER:
	{
		int x = rand() % (PLATE_WIDTH - SPRING_WIDTH);
		bonus[bonusIndex].setBonusType(BonusType::HAT_HELICOPTER);
		bonus[bonusIndex].setPosition(sf::Vector2f(platePosition.x + x, platePosition.y - HAT_HELICOPTER_HEIGHT));
		switch (rand() % 2)
		{
		case 0:
			bonus[bonusIndex].setTexture(assets->HAT_HELOCPTER_NONE_LEFT_TEXTURE);
			break;
		case 1:
			bonus[bonusIndex].setTexture(assets->HAT_HELOCPTER_NONE_RIGHT_TEXTURE);
			break;
		}
		break;
	}
	case BonusType::ROCKET:
	{
		int x = rand() % (PLATE_WIDTH - ROCKET_WIDTH);
		bonus[bonusIndex].setBonusType(BonusType::ROCKET);
		bonus[bonusIndex].setPosition(sf::Vector2f(platePosition.x + x, platePosition.y - ROCKET_HEIGHT));
		bonus[bonusIndex].setTexture(assets->ROCKET_NONE_TEXTURE);
		break;
	}
	}
}

float GameScene::checkDoodleFall(void)
{
	sf::Vector2f doodlePosition = hero->getPosition();
	sf::Vector2f platePosition[NUMBER_PLATES];
	sf::Vector2f bonusPosition[NUMBER_BONUSES];
	Collision collision = Collision::NO_COLLISION;

	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		platePosition[i] = plate[i]->getPosition();
	}
	for (int i = 0; i < NUMBER_BONUSES; ++i)
	{
		bonusPosition[i] = bonus[i].getPosition();
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
		PlaySound(L"sounds/jump.wav", nullptr, SND_ASYNC | SND_NODEFAULT);
		return PLATE_DELTA_HEIGHT;
	case Collision::COLLISION_GHOST_PLATE:
		actualBonus = BonusType::NO;
		result.collision = Collision::COLLISION_GHOST_PLATE;
		PlaySound(L"sounds/bijeli.wav", nullptr, SND_ASYNC | SND_NODEFAULT);
		return PLATE_DELTA_HEIGHT;
	case Collision::COLLISION_SPRING:
		actualBonus = BonusType::SPRING;
		result.collision = Collision::COLLISION_SPRING;
		PlaySound(L"sounds/feder.wav", nullptr, SND_ASYNC | SND_NODEFAULT);
		return SPRING_DELTA_HEIGHT;
	case Collision::COLLISION_TRAMPLANE:
		actualBonus = BonusType::TRAMPOLINE;
		result.collision = Collision::COLLISION_TRAMPLANE;
		PlaySound(L"sounds/trampoline.wav", nullptr, SND_ASYNC | SND_NODEFAULT);
		return TRAMPLANE_DELTA_HEIGHT;
	case Collision::COLLISION_HAT_HELICOPTER:
		actualBonus = BonusType::HAT_HELICOPTER;
		result.collision = Collision::COLLISION_HAT_HELICOPTER;
		PlaySound(L"sounds/propeller.wav", nullptr, SND_ASYNC | SND_NODEFAULT);
		return HAT_HELICOPTER_DELTA_HEIGHT;
	case Collision::COLLISION_ROCKET:
		actualBonus = BonusType::ROCKET;
		result.collision = Collision::COLLISION_ROCKET;
		PlaySound(L"sounds/jetpack.wav", nullptr, SND_ASYNC | SND_NODEFAULT);
		return ROCKET_DELTA_HEIGHT;
	default:
		result.collision = Collision::NO_COLLISION;
		return 0.f;
	}
}

Collision GameScene::checkCollisionPlate(sf::Vector2f & doodlePosition, sf::Vector2f platePosition[NUMBER_PLATES])
{
	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		if (((doodlePosition.y + DOODLE_HEIGHT >= platePosition[i].y) && (doodlePosition.y + DOODLE_HEIGHT <= platePosition[i].y + PLATE_HEIGHT)
			&& (doodlePosition.x + DOODLE_WIDTH >= platePosition[i].x) && (doodlePosition.x - PLATE_WIDTH <= platePosition[i].x)))
		{
			if ((plate[i]->getType() == PlateType::UNSTABLE) || (plate[i]->getType() == PlateType::UNSTABLE_DYNAMIC_X))
			{
				plate[i]->setFallStatus(true);
				continue;
			}

			if (plate[i]->getType() == PlateType::CLOUD)
			{
				plate[i]->setPosition(sf::Vector2f(100.f, 1000.f));
				return Collision::COLLISION_GHOST_PLATE;
			}
			return  Collision::COLLISION_PLATE;
		}
	}
	return Collision::NO_COLLISION;
}

Collision GameScene::checkCollisionHole(sf::Vector2f & doodlePosition)
{
	if (((doodlePosition.y + DOODLE_HEIGHT >= holePosition.y) && (doodlePosition.y + DOODLE_HEIGHT <= holePosition.y + HOLE_HEIGHT)
		&& (doodlePosition.x + DOODLE_WIDTH >= holePosition.x) && (doodlePosition.x - HOLE_WIDTH <= holePosition.x)))
	{
		return Collision::COLLISION_HOLE;
	}
	return Collision::NO_COLLISION;
}

Collision GameScene::checkCollisionBonus(sf::Vector2f & doodlePosition, sf::Vector2f bonusPosition[NUMBER_PLATES])
{
	for (int bonusIndex = 0; bonusIndex < NUMBER_BONUSES; ++bonusIndex)
	{
		switch (bonus[bonusIndex].getBonusType())
		{
		case BonusType::SPRING:
			if (((doodlePosition.y + DOODLE_HEIGHT >= bonusPosition[bonusIndex].y) && (doodlePosition.y + DOODLE_HEIGHT <= bonusPosition[bonusIndex].y + SPRING_HEIGHT)
				&& (doodlePosition.x + DOODLE_WIDTH >= bonusPosition[bonusIndex].x) && (doodlePosition.x - SPRING_WIDTH <= bonusPosition[bonusIndex].x)))
			{
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
				return Collision::COLLISION_HAT_HELICOPTER;
			}
			break;
		case BonusType::ROCKET:
			if (((doodlePosition.y + DOODLE_HEIGHT >= bonusPosition[bonusIndex].y) && (doodlePosition.y + DOODLE_HEIGHT <= bonusPosition[bonusIndex].y + ROCKET_HEIGHT)
				&& (doodlePosition.x + DOODLE_WIDTH >= bonusPosition[bonusIndex].x) && (doodlePosition.x - ROCKET_WIDTH <= bonusPosition[bonusIndex].x)))
			{
				actualBonusId = bonusIndex;
				return Collision::COLLISION_ROCKET;
			}
			break;
		}
	}
	return Collision::NO_COLLISION;
}

uint64_t GameScene::getScore(void)
{
	return points;
}
