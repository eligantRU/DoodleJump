#include "stdafx.h"
#include "sheet.h"

GameScene::GameScene(Assets & assets, sf::View & view)
	:m_assets(assets)
	,m_view(view)
{
	m_hero = std::make_unique<Doodle>(m_assets);
	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		m_plates[i] = std::make_unique<Plate>(m_assets);
	}
	for (int i = 0; i < NUMBER_BONUSES; ++i)
	{
		m_bonuses[i] = std::make_unique<Bonus>();
	}

	m_actualBonus = BonusType::NO;
	m_view.reset(sf::FloatRect(0.f, 0.f, float(WINDOW_WIDTH), float(WINDOW_HEIGHT)));
	m_hero->setSpeedY(-50.f);
	m_offsetFallBonus.x = 0.f;
	m_offsetFallBonus.y = 0.f;

	m_hole = std::make_unique<sf::Sprite>();
	m_hole->setTextureRect(sf::IntRect(0, 0, 60, 54));
	m_hole->setTexture(m_assets.HOLE_TEXTURE);
	m_holePosition.x = float(rand() % (WINDOW_WIDTH - HOLE_WIDTH));
	m_holePosition.y = -1.f * float(rand() % 15000) - 10.f * 750.f;
	m_hole->setPosition(m_holePosition.x, m_holePosition.y);

	m_scoreNum.setFont(m_assets.ARIAL_FONT);
	m_scoreNum.setCharacterSize(20);
	m_scoreNum.setStyle(sf::Text::Bold);
	m_scoreNum.setColor(sf::Color(0, 0, 0));

	m_background = std::make_unique<sf::Sprite>();
	m_background->setTextureRect(sf::IntRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	m_background->setTexture(m_assets.BACKGROUND_TEXTURE);

	initBonuses();
	resetGame();
}

GameScene::~GameScene()
{

}


SGameResult GameScene::onGameFrame(sf::RenderWindow & window)
{
	if (m_result.status == GameStatus::GAME_OVER_SCENE)
	{
		{
			resetGame();
		}
	}

	if (!m_endOfGame)
	{
		tuneSceneAfterPause(window);

		checkEvents(window);
		update(window);
		window.setView(m_view);
		render(window);
		window.display();

		if (m_isPause) // TODO: pause handler
		{
			m_view.setCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
			m_assets.pauseSound();
			window.setView(m_view);
			m_result.status = GameStatus::PAUSE_SCENE;
		}
		else
		{
			m_result.status = GameStatus::GAME_SCENE;
		}
	}
	else
	{
		m_view.setCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
		window.setView(m_view);
		m_result.status = GameStatus::GAME_OVER_SCENE; 
	}
	return m_result;
}

void GameScene::tuneSceneAfterPause(sf::RenderWindow & window)
{
	if (m_isPause) // TODO: pause handler
	{
		m_isPause = false;
		m_assets.removeSoundFromPause();
		m_view.setCenter(WINDOW_WIDTH / 2, m_background->getPosition().y + WINDOW_HEIGHT / 2);
		window.setView(m_view);
	}
}

void GameScene::moveDoodle()
{
	sf::Vector2f position(0.f, 0.f);
	position.x = moveDoodleHorizontal();
	position.y = moveDoodleVertical();
	m_hero->move(position);
}

float GameScene::moveDoodleHorizontal()
{
	DirectionX doodleDirection = m_hero->getDirection();
	float positionX = 0;
	if (doodleDirection == DirectionX::RIGHT)
	{
		positionX += STEP;
	}
	else if (doodleDirection  == DirectionX::LEFT)
	{
		positionX -= STEP;
	}
	return positionX;
}

float GameScene::moveDoodleVertical()
{
	float positionY = 0;
	if (m_hero->getSpeedY() < 0)
	{
		m_hero->setSpeedY(m_hero->getSpeedY() + ACCELERATION);
		positionY = m_hero->getSpeedY();
	}
	else
	{
		float testingFall = checkDoodleFall();
		if (testingFall == 0)
		{
			m_actualBonus = BonusType::NO;
			m_hero->setSpeedY(m_hero->getSpeedY() + ACCELERATION / 8);
			positionY = m_hero->getSpeedY();
		}
		else
		{
			m_hero->setSpeedY(-testingFall);
		}
	}
	return positionY;
}

void GameScene::updatePositionBeforeDown()
{
	if (m_hero->getPosition().y < m_hero->getPositionBeforeDown().y)
	{
		m_hero->setPositionBeforeDown(m_hero->getPosition());
	}
}

void GameScene::animateBonus()
{
	switch (m_actualBonus)
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
	case BonusType::NO:
		break;
	default:
		break;
	}
}

void GameScene::animateSpring()
{
	sf::Vector2f actualBonusPosition = m_bonuses[m_actualBonusId]->getPosition();
	if ((m_hero->getSpeedY() >= 0) || (actualBonusPosition.y < m_view.getCenter().y - WINDOW_HEIGHT / 2 - SPRING_HEIGHT))
	{
		m_actualBonus = BonusType::NO;
	}
	else
	{
		m_bonuses[m_actualBonusId]->setPosition(sf::Vector2f(actualBonusPosition.x, actualBonusPosition.y - 4.f));
		m_bonuses[m_actualBonusId]->setTexture(m_assets.SPRING_2_TEXTURE);
	}
}

void GameScene::animateTrampoline()
{
	if (m_hero->getSpeedY() >= 0)
	{
		m_hero->setRotation(0.f);
		m_actualBonus = BonusType::NO;
	}
	else
	{
		m_hero->rotate(360.f / TRAMPLANE_DELTA_HEIGHT);
	}
}

void GameScene::animateRocket() // TODO: handlers...this code NEED MORE HANDLERS!
{
	DirectionX doodleLastDirection = m_hero->getLastDirection();
	sf::Vector2f doodlePosition = m_hero->getPosition();
	
	if ((m_hero->getSpeedY() >= 0) || (m_bonuses[m_actualBonusId]->getPosition().y < m_view.getCenter().y - WINDOW_HEIGHT / 2 - ROCKET_HEIGHT))
	{
		m_animationCounter = 0;
		m_actualBonus = BonusType::NO;
		m_offsetFallBonus.x = 0.f;
		m_offsetFallBonus.y = 0.f;
		m_bonuses[m_actualBonusId]->setRotation(0.f);
		m_bonuses[m_actualBonusId]->move(sf::Vector2f(0.f, float(WINDOW_HEIGHT)));
	}

	if ((m_animationCounter >= 0) && (m_animationCounter <= 2))
	{
		if (doodleLastDirection == DirectionX::RIGHT)
		{
			m_bonuses[m_actualBonusId]->setTexture(m_assets.ROCKET_0_LEFT_TEXTURE);
		}
		else if (doodleLastDirection == DirectionX::LEFT)
		{
			m_bonuses[m_actualBonusId]->setTexture(m_assets.ROCKET_0_RIGHT_TEXTURE);
		}
		++m_animationCounter;
	}
	if ((m_animationCounter >= 3) && (m_animationCounter <= 5))
	{
		if (doodleLastDirection == DirectionX::RIGHT)
		{
			m_bonuses[m_actualBonusId]->setTexture(m_assets.ROCKET_1_LEFT_TEXTURE);
		}
		else if (doodleLastDirection == DirectionX::LEFT)
		{
			m_bonuses[m_actualBonusId]->setTexture(m_assets.ROCKET_1_RIGHT_TEXTURE);
		}
		++m_animationCounter;
	}
	if ((m_animationCounter >= 6) && (m_animationCounter <= 8))
	{
		if (doodleLastDirection == DirectionX::RIGHT)
		{
			m_bonuses[m_actualBonusId]->setTexture(m_assets.ROCKET_2_LEFT_TEXTURE);
		}
		else if (doodleLastDirection == DirectionX::LEFT)
		{
			m_bonuses[m_actualBonusId]->setTexture(m_assets.ROCKET_2_RIGHT_TEXTURE);
		}
		++m_animationCounter;
	}
	if ((m_animationCounter >= 9) && (m_animationCounter <= 11))
	{
		if (doodleLastDirection == DirectionX::RIGHT)
		{
			m_bonuses[m_actualBonusId]->setTexture(m_assets.ROCKET_3_LEFT_TEXTURE);
		}
		else if (doodleLastDirection == DirectionX::LEFT)
		{
			m_bonuses[m_actualBonusId]->setTexture(m_assets.ROCKET_3_RIGHT_TEXTURE);
		}
		++m_animationCounter;
	}
	if (m_animationCounter == 11)
	{
		m_animationCounter = 0;
	}

	if ((m_animationCounter >= 0) && (m_animationCounter <= 11) && (m_actualBonus != BonusType::NO) && (m_hero->getSpeedY() < -0.05f * ROCKET_DELTA_HEIGHT))
	{
		if (doodleLastDirection == DirectionX::RIGHT)
		{
			if ((m_animationCounter >= 0) && (m_animationCounter <= 2))
			{
				m_bonuses[m_actualBonusId]->setPosition(sf::Vector2f(doodlePosition.x - 13, doodlePosition.y));
			}
			if ((m_animationCounter >= 3) && (m_animationCounter <= 5))
			{
				m_bonuses[m_actualBonusId]->setPosition(sf::Vector2f(doodlePosition.x - 13, doodlePosition.y));
			}
			if ((m_animationCounter >= 6) && (m_animationCounter <= 8))
			{
				m_bonuses[m_actualBonusId]->setPosition(sf::Vector2f(doodlePosition.x - 15, doodlePosition.y));
			}
			if ((m_animationCounter >= 9) && (m_animationCounter <= 11))
			{
				m_bonuses[m_actualBonusId]->setPosition(sf::Vector2f(doodlePosition.x - 17, doodlePosition.y));
			}
		}
		else if (doodleLastDirection == DirectionX::LEFT)
		{
			if ((m_animationCounter >= 0) && (m_animationCounter <= 2))
			{
				m_bonuses[m_actualBonusId]->setPosition(sf::Vector2f(doodlePosition.x + DOODLE_WIDTH + 1, doodlePosition.y));
			}
			if ((m_animationCounter >= 3) && (m_animationCounter <= 5))
			{
				m_bonuses[m_actualBonusId]->setPosition(sf::Vector2f(doodlePosition.x + DOODLE_WIDTH + 1, doodlePosition.y));
			}
			if ((m_animationCounter >= 6) && (m_animationCounter <= 8))
			{
				m_bonuses[m_actualBonusId]->setPosition(sf::Vector2f(doodlePosition.x + DOODLE_WIDTH, doodlePosition.y));
			}
			if ((m_animationCounter >= 9) && (m_animationCounter <= 11))
			{
				m_bonuses[m_actualBonusId]->setPosition(sf::Vector2f(doodlePosition.x + DOODLE_WIDTH - 5, doodlePosition.y));
			}
		}
	}

	if (m_hero->getSpeedY() >= -0.05f * ROCKET_DELTA_HEIGHT && m_actualBonus != BonusType::NO)
	{
		m_bonuses[m_actualBonusId]->setTexture(m_assets.ROCKET_NONE_TEXTURE);
		if (m_actualBonus != BonusType::NO)
		{
			m_bonuses[m_actualBonusId]->setPosition(doodlePosition);
		}
		m_bonuses[m_actualBonusId]->rotate(-10.f);
		m_offsetFallBonus.x += -2.f * STEP;
		m_offsetFallBonus.y += 6.f * STEP;
		m_bonuses[m_actualBonusId]->move(sf::Vector2f(m_offsetFallBonus));
	}
}

void GameScene::animateHatHelicopter() // TODO: handlers...this code NEED MORE HANDLERS!
{
	sf::Vector2f doodlePosition = m_hero->getPosition();

	if ((m_hero->getSpeedY() >= 0) || (m_bonuses[m_actualBonusId]->getPosition().y < m_view.getCenter().y - WINDOW_HEIGHT / 2 - HAT_HELICOPTER_HEIGHT))
	{
		m_animationCounter = 0;
		m_actualBonus = BonusType::NO;
		m_offsetFallBonus.x = 0.f;
		m_offsetFallBonus.y = 0.f;
		m_bonuses[m_actualBonusId]->setRotation(0.f);
		m_bonuses[m_actualBonusId]->move(sf::Vector2f(0.f, float(WINDOW_HEIGHT)));
	}

	if (m_hero->getSpeedY() < -0.05f * HAT_HELICOPTER_DELTA_HEIGHT)
	{
		if ((m_animationCounter >= 0) && (m_animationCounter <= 5))
		{
			m_bonuses[m_actualBonusId]->setTexture(m_assets.HAT_HELOCPTER_FLY_LEFT_TEXTURE);
			++m_animationCounter;
		}
		if ((m_animationCounter >= 6) && (m_animationCounter <= 10))
		{
			m_bonuses[m_actualBonusId]->setTexture(m_assets.HAT_HELOCPTER_DIAGONAL_LEFT_TEXTURE);
			++m_animationCounter;
		}
		if ((m_animationCounter >= 11) && (m_animationCounter <= 15))
		{
			m_bonuses[m_actualBonusId]->setTexture(m_assets.HAT_HELOCPTER_DIAGONAL_RIGHT_TEXTURE);
			++m_animationCounter;
		}
		if ((m_animationCounter >= 16) && (m_animationCounter <= 20))
		{
			m_bonuses[m_actualBonusId]->setTexture(m_assets.HAT_HELOCPTER_FLY_RIGHT_TEXTURE);
			++m_animationCounter;
		}
		if (m_animationCounter == 20)
		{
			m_animationCounter = 0;
		}
	}
	if ((m_animationCounter >= 0) && (m_animationCounter <= 20) && (m_actualBonus != BonusType::NO) && (m_hero->getSpeedY() < -0.05f * HAT_HELICOPTER_DELTA_HEIGHT))
	{
		DirectionX doodleLastDirection = m_hero->getLastDirection();
		if (doodleLastDirection == DirectionX::RIGHT)
		{
			m_bonuses[m_actualBonusId]->setPosition(sf::Vector2f(doodlePosition.x, doodlePosition.y - 14));
		}
		else if (doodleLastDirection == DirectionX::LEFT)
		{
			m_bonuses[m_actualBonusId]->setPosition(sf::Vector2f(doodlePosition.x + 15, doodlePosition.y - 14));
		}
	}

	if (m_hero->getSpeedY() >= -0.05f * HAT_HELICOPTER_DELTA_HEIGHT && m_actualBonus != BonusType::NO)
	{
		m_bonuses[m_actualBonusId]->setTexture(m_assets.HAT_HELOCPTER_NONE_LEFT_TEXTURE);
		if (m_actualBonus != BonusType::NO)
		{
			m_bonuses[m_actualBonusId]->setPosition(sf::Vector2f(doodlePosition.x, doodlePosition.y - 14));
		}
		m_bonuses[m_actualBonusId]->rotate(-10.f);
		m_offsetFallBonus.x += -2.f * STEP;
		m_offsetFallBonus.y += 6.f * STEP;
		m_bonuses[m_actualBonusId]->move(sf::Vector2f(m_offsetFallBonus));
	}
}

void GameScene::update(sf::RenderWindow & window)
{
	(void)window;
	moveDoodle();
	m_hero->correctSkin();
	checkCylinderEffect();
	animateBonus();

	updatePositionBeforeDown();
	sf::Vector2f doodlePosition = m_hero->getPosition();
	if ((m_hero->getSpeedY() <= 0) && (doodlePosition.y <= m_hero->getPositionBeforeDown().y)) // TODO: this code need handler
	{
		m_view.setCenter(WINDOW_WIDTH/2, doodlePosition.y);
		m_background->setPosition(0, doodlePosition.y - WINDOW_HEIGHT / 2);
		m_scoreNum.setPosition(0, doodlePosition.y - WINDOW_HEIGHT / 2);
		++m_points;
	}

	moveBonuses();
	dropUnstablePlates();
	moveDynamicPlates();
	generPlates();
	generBonuses();
	generHole();

	m_endOfGame = checkGameEnd();
}

void GameScene::resetGame()
{
	m_view.reset(sf::FloatRect(0.f, 0.f, float(WINDOW_WIDTH), float(WINDOW_HEIGHT)));
	m_scoreNum.setPosition(0, 0);
	m_endOfGame = false;
	m_points = 0;
	m_actualBonus = BonusType::NO;
	m_offsetFallBonus.x = 0.f;
	m_offsetFallBonus.y = 0.f;
	m_isLeft = false;
	m_isRight = false;
	m_hero->setDirection(DirectionX::NONE);

	m_hero->setTexture(m_assets.DOODLE_LEFT_TEXTURE);
	m_hero->setPosition(sf::Vector2f(260.f, 350.f));
	m_hero->setSpeedY(-50.f);
	m_animationCounter = 0;
	m_hero->setPositionBeforeDown(m_hero->getPosition());
	m_view.setCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

	m_plates[0]->setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - PLATE_WIDTH/2, WINDOW_HEIGHT - PLATE_HEIGHT));
	for (int i = 1; i < NUMBER_PLATES/2; ++(++i))
	{
		m_plates[i]->setType(PlateType::STATIC);
		m_plates[i]->setTexture(m_assets.PLATE_STATIC_TEXTURE);

		float y1 = float((rand() % 152) + 90);
		float x1 = (sqrt(484*484 - y1*y1))/2;
		float y2 = float((rand() % 152) + 90);
		float x2 = (sqrt(484 * 484 - y1*y1)) / 2;
		if ((m_plates[i - 1]->getPosition().x + x1 >= WINDOW_WIDTH - PLATE_WIDTH) && (m_plates[i - 1]->getPosition().x - x1 <= 0))
		{
			x1 = float(rand() % (WINDOW_WIDTH - PLATE_WIDTH));
		}

		m_plates[i]->setPosition(sf::Vector2f(x1, m_plates[i-1]->getPosition().y - y1));
		m_plates[i]->setPosition(sf::Vector2f(x2, m_plates[i-1]->getPosition().y - y2));
	}
	m_view.setCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	initBonuses();
}

void GameScene::generPlates()
{
	if (m_plates[0]->getPosition().y > m_view.getCenter().x + WINDOW_HEIGHT / 2)
	{
		m_plates[0]->setType(PlateType::STATIC);
		m_plates[0]->setTexture(m_assets.PLATE_DYNAMIC_TEXTURE);
		m_plates[0]->setPosition(sf::Vector2f(float(rand() % (WINDOW_WIDTH - PLATE_WIDTH)), m_view.getCenter().y - WINDOW_HEIGHT / 2 - PLATE_HEIGHT));
	}

	sf::Vector2f platePosition[NUMBER_PLATES];
	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		platePosition[i] = m_plates[i]->getPosition();
	}
	std::array<float, NUMBER_PLATES> platePositionY;
	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		platePositionY[i] = m_plates[i]->getPosition().y;
	}
	std::sort(platePositionY.begin(), platePositionY.end(), std::greater<float>());

	for (int i = 1; i < NUMBER_PLATES / 2; ++(++i))
	{
		float y1 = float((rand() % 182) + 60);
		float x1 = float(rand() % (WINDOW_WIDTH - PLATE_WIDTH));	//float x1 = (sqrt(484 * 484 - y1 * y1)) / 2;

		if (platePosition[i].y > m_view.getCenter().y + WINDOW_HEIGHT / 2 + ROCKET_HEIGHT)
		{
			if ((m_plates[i]->getPosition().x + x1 >= WINDOW_WIDTH - PLATE_WIDTH) && (m_plates[i]->getPosition().x - x1 <= 0))
			{
				x1 = float(rand() % (WINDOW_WIDTH - PLATE_WIDTH));
			}

			if ((m_plates[i]->getType() == PlateType::UNSTABLE) || (m_plates[i]->getType() == PlateType::UNSTABLE_DYNAMIC_X))
			{
				--m_unstablePlatesCounter;
			}

			m_plates[i]->setRotation(0);
			switch (rand() % 3)
			{
			case 0:
				m_plates[i]->setType(PlateType::STATIC);
				m_plates[i]->setTexture(m_assets.PLATE_STATIC_TEXTURE);
				m_plates[i]->setSpeedX(0);
				break;
			case 1:
				m_plates[i]->setType(PlateType::STATIC_DYNAMIC_X);
				m_plates[i]->setTexture(m_assets.PLATE_DYNAMIC_TEXTURE);

				m_plates[i]->setSpeedX((rand() % 3) + 1);
				if (rand() % 2)
				{
					m_plates[i]->setSpeedX(-m_plates[i]->getSpeedX());
				}
				break;
			case 2:
				m_plates[i]->setType(PlateType::CLOUD);
				m_plates[i]->setTexture(m_assets.PLATE_CLOUD_TEXTURE);
				m_plates[i]->setSpeedX(0);
				break;
			}
			m_plates[i]->setPosition(sf::Vector2f(x1, platePositionY[NUMBER_PLATES-1] - y1));

			for (int j = 1; j < NUMBER_PLATES/ 2; ++(++j)) // NOTE: Oh my God...What the f*ck r u doing?
			{
				float y2 = float((rand() % 182) + 60);
				float x2 = float(rand() % (WINDOW_WIDTH - PLATE_WIDTH));

				if (platePosition[j].y > m_view.getCenter().y + WINDOW_HEIGHT / 2 + ROCKET_HEIGHT)
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
					m_plates[i]->setRotation(0);
					switch (rand() % 3)
					{
					case 0:
						m_plates[i]->setType(PlateType::STATIC);
						m_plates[i]->setTexture(m_assets.PLATE_STATIC_TEXTURE);
						m_plates[i]->setSpeedX(0);
						break;
					case 1:
						m_plates[i]->setType(PlateType::STATIC_DYNAMIC_X);
						m_plates[i]->setTexture(m_assets.PLATE_DYNAMIC_TEXTURE);

						m_plates[i]->setSpeedX((rand() % 3) + 1);
						if (rand() % 2)
						{
							m_plates[i]->setSpeedX(-m_plates[i]->getSpeedX());
						}
						break;
					case 2:
						m_plates[i]->setType(PlateType::CLOUD);
						m_plates[i]->setTexture(m_assets.PLATE_CLOUD_TEXTURE);
						m_plates[i]->setSpeedX(0);
						break;
					case 3:
						m_plates[i]->setType(PlateType::UNSTABLE);
						m_plates[i]->setTexture(m_assets.PLATE_UNSTABLE_TEXTURE);
						m_plates[i]->setSpeedX(0);
						++m_unstablePlatesCounter;
						break;
					case 4:
						m_plates[i]->setType(PlateType::UNSTABLE_DYNAMIC_X);
						m_plates[i]->setTexture(m_assets.PLATE_UNSTABLE_TEXTURE);

						m_plates[i]->setSpeedX((rand() % 3) + 1);
						if (rand() % 2)
						{
							m_plates[i]->setSpeedX(-m_plates[i]->getSpeedX());
						}
						++m_unstablePlatesCounter;
						break;
					}

					m_plates[j]->setPosition(sf::Vector2f(x2, platePositionY[NUMBER_PLATES - 1] - y2));
					break;
				}
			}
		}
	}
}

void GameScene::generHole()
{
	if (m_hole->getPosition().y >= m_view.getCenter().y + WINDOW_HEIGHT / 2)
	{
		m_holePosition.x = float(rand() % (WINDOW_WIDTH - HOLE_WIDTH));
		m_holePosition.y = m_hero->getPosition().y -1.f * float(rand() % 15000) - 10.f * 750.f;
		m_hole->setPosition(sf::Vector2f(m_holePosition.x, m_holePosition.y));
	}
}

void GameScene::generBonuses()
{
	sf::Vector2f bonusPosition[NUMBER_BONUSES];
	sf::Vector2f platePosition;

	for (int bonusIndex = 0; bonusIndex < NUMBER_BONUSES; ++bonusIndex)
	{
		bonusPosition[bonusIndex] = m_bonuses[bonusIndex]->getPosition();

		if (bonusPosition[bonusIndex].y > m_view.getCenter().y + WINDOW_HEIGHT / 2)
		{
			for (int plateIndex = 0; plateIndex < NUMBER_PLATES; ++plateIndex)
			{
				platePosition = m_plates[plateIndex]->getPosition();
				if ((platePosition.y < m_view.getCenter().y - WINDOW_HEIGHT / 2 - ROCKET_HEIGHT) &&
					((m_plates[plateIndex]->getType() == PlateType::STATIC) || (m_plates[plateIndex]->getType() == PlateType::STATIC_DYNAMIC_X)))
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

void GameScene::dropUnstablePlates()
{
	for (int plateIndex = 0; plateIndex < NUMBER_PLATES; ++plateIndex)
	{
		if (m_plates[plateIndex]->getFallStatus() == true)
		{
			m_plates[plateIndex]->rotate(-1.f);
			m_plates[plateIndex]->move(sf::Vector2f(-1 * STEP, 4 * STEP));
			if (m_plates[plateIndex]->getPosition().y >= m_view.getCenter().y + WINDOW_HEIGHT / 2)
			{
				m_plates[plateIndex]->setRotation(0);
				m_plates[plateIndex]->setFallStatus(false);
			}
		}
	}
}

bool GameScene::checkGameEnd()
{
	sf::Vector2f doodlePosition = m_hero->getPosition();
	if ((checkCollisionHole() == Collision::COLLISION_HOLE) && ((m_actualBonus == BonusType::NO)))
	{
		m_assets.playSound(m_assets.HOLE_SOUND);
		return true;
	}
	if (doodlePosition.y < m_view.getCenter().y + WINDOW_HEIGHT / 2 - DOODLE_HEIGHT)
	{
		return false;
	}
	m_assets.playSound(m_assets.GAME_OVER_SOUND);
	return true;
}

void GameScene::render(sf::RenderWindow & window)
{
	window.clear(sf::Color(255, 255, 255));
	
	window.draw(*m_background);
	for (auto &plate : m_plates)
	{
		plate->draw(window);
	}
	m_hero->draw(window);
	for (auto &bonus : m_bonuses)
	{
		bonus->draw(window);
	}
	window.draw(*m_hole);
	m_scoreNum.setString("Score: " + std::to_string(m_points));
	window.draw(m_scoreNum);
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
			m_isPause = true;
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
		m_hero->updateDirection(m_isLeft, m_isRight);
	}
}

void GameScene::checkKeyPressed(sf::Event event, bool & isNeedUpdate)
{
	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::A:
			m_isLeft = true;
			isNeedUpdate = true;
			break;
		case sf::Keyboard::D:
			m_isRight = true;
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
			m_isLeft = false;
			isNeedUpdate = true;
			break;
		case sf::Keyboard::D:
			m_isRight = false;
			isNeedUpdate = true;
			break;
		default:
			break;
		}
	}
}

void GameScene::moveDynamicPlates() 
{
	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		sf::Vector2f platePosition = m_plates[i]->getPosition();
		int speedX = m_plates[i]->getSpeedX();
		if (speedX < 0)
		{
			if (platePosition.x <= speedX)
			{
				m_plates[i]->setSpeedX(-speedX);
			}
		}
		if (speedX > 0)
		{
			if (platePosition.x >= WINDOW_WIDTH - PLATE_WIDTH - speedX)
			{
				m_plates[i]->setSpeedX(-speedX);
			}
		}
		m_plates[i]->move(sf::Vector2f(float(speedX), 0.f));
	}
}

void GameScene::moveBonuses()
{
	for (int bonusIndex = 0; bonusIndex < NUMBER_BONUSES; ++bonusIndex)
	{
		m_bonuses[bonusIndex]->setSpeedX(m_plates[m_bonuses[bonusIndex]->getPlateIndex()]->getSpeedX());

		if (m_bonuses[bonusIndex]->getSpeedX() != 0)
		{
			m_bonuses[bonusIndex]->move(sf::Vector2f(float(m_bonuses[bonusIndex]->getSpeedX()), 0.f));
		}
	}
}

void GameScene::checkCylinderEffect()
{
	auto doodlePosition = m_hero->getPosition();

	if (doodlePosition.x <= -DOODLE_WIDTH)
	{
		m_hero->setPosition(sf::Vector2f(float(WINDOW_WIDTH - DOODLE_WIDTH), doodlePosition.y));
	}
	if (doodlePosition.x >= WINDOW_WIDTH)
	{
		m_hero->setPosition(sf::Vector2f(0.f, doodlePosition.y));
	}
}

void GameScene::initBonuses()
{
	std::vector<sf::Vector2f> platePosition;
	for (int plateIndex = 0; plateIndex < NUMBER_PLATES; ++plateIndex)
	{
		platePosition.push_back(m_plates[plateIndex]->getPosition());
	}

	for (int bonusIndex = 0; bonusIndex < NUMBER_BONUSES; ++bonusIndex)
	{
		int plateIndex = rand() % platePosition.size();
		BonusType type = (rand() % 2) ? BonusType::SPRING : BonusType::TRAMPOLINE;
		buildBonus(type, bonusIndex, platePosition[plateIndex], plateIndex);
	}
}

void GameScene::buildBonus(BonusType bonusType, int bonusIndex, sf::Vector2f platePosition, int plateIndex) // TODO: this code really want to be refactored
{
	m_bonuses[bonusIndex]->setPlateIndex(plateIndex);
	m_bonuses[bonusIndex]->setRotation(0.f);

	switch (bonusType)
	{
	case BonusType::SPRING:
	{
		int x = rand() % (PLATE_WIDTH - SPRING_WIDTH);
		m_bonuses[bonusIndex]->setBonusType(BonusType::SPRING);
		m_bonuses[bonusIndex]->setPosition(sf::Vector2f(platePosition.x + x, platePosition.y - SPRING_HEIGHT));
		m_bonuses[bonusIndex]->setTexture(m_assets.SPRING_TEXTURE);
		break;
	}
	case BonusType::TRAMPOLINE:
	{
		int x = rand() % (PLATE_WIDTH - TRAMPOLINE_WIDTH);
		m_bonuses[bonusIndex]->setBonusType(BonusType::TRAMPOLINE);
		m_bonuses[bonusIndex]->setPosition(sf::Vector2f(platePosition.x + x, platePosition.y - TRAMPOLINE_HEIGHT));
		m_bonuses[bonusIndex]->setTexture(m_assets.TRAMPOLINE_TEXTURE);
		break;
	}
	case BonusType::HAT_HELICOPTER:
	{
		int x = rand() % (PLATE_WIDTH - SPRING_WIDTH);
		m_bonuses[bonusIndex]->setBonusType(BonusType::HAT_HELICOPTER);
		m_bonuses[bonusIndex]->setPosition(sf::Vector2f(platePosition.x + x, platePosition.y - HAT_HELICOPTER_HEIGHT));
		switch (rand() % 2)
		{
		case 0:
			m_bonuses[bonusIndex]->setTexture(m_assets.HAT_HELOCPTER_NONE_LEFT_TEXTURE);
			break;
		case 1:
			m_bonuses[bonusIndex]->setTexture(m_assets.HAT_HELOCPTER_NONE_RIGHT_TEXTURE);
			break;
		}
		break;
	}
	case BonusType::ROCKET:
	{
		int x = rand() % (PLATE_WIDTH - ROCKET_WIDTH);
		m_bonuses[bonusIndex]->setBonusType(BonusType::ROCKET);
		m_bonuses[bonusIndex]->setPosition(sf::Vector2f(platePosition.x + x, platePosition.y - ROCKET_HEIGHT));
		m_bonuses[bonusIndex]->setTexture(m_assets.ROCKET_NONE_TEXTURE);
		break;
	}
	}
}

float GameScene::checkDoodleFall() // TODO: try to write handler else not too bad
{
	Collision collision = Collision::NO_COLLISION;

	collision = checkCollisionBonus();
	if (collision == Collision::NO_COLLISION)
	{
		collision = checkCollisionPlate();
	}

	switch (collision)
	{
	case Collision::COLLISION_PLATE:
		m_actualBonus = BonusType::NO; 
		m_assets.playSound(m_assets.JUMP_SOUND);
		return PLATE_DELTA_HEIGHT;
	case Collision::COLLISION_GHOST_PLATE:
		m_actualBonus = BonusType::NO;
		m_assets.playSound(m_assets.PLATE_GHOST_SOUND);
		return PLATE_DELTA_HEIGHT;
	case Collision::COLLISION_SPRING:
		m_actualBonus = BonusType::SPRING;
		m_assets.playSound(m_assets.SPRING_SOUND);
		return SPRING_DELTA_HEIGHT;
	case Collision::COLLISION_TRAMPLANE:
		m_actualBonus = BonusType::TRAMPOLINE;
		m_assets.playSound(m_assets.TRAMPOLINE_SOUND);
		return TRAMPLANE_DELTA_HEIGHT;
	case Collision::COLLISION_HAT_HELICOPTER:
		m_actualBonus = BonusType::HAT_HELICOPTER;
		m_assets.playSound(m_assets.HAT_HELICOPTER_SOUND);
		return HAT_HELICOPTER_DELTA_HEIGHT;
	case Collision::COLLISION_ROCKET:
		m_actualBonus = BonusType::ROCKET;
		m_assets.playSound(m_assets.ROCKET_SOUND);
		return ROCKET_DELTA_HEIGHT;
	default:
		return 0.f;
	}
}

Collision GameScene::checkCollisionPlate()
{
	auto doodlePosition = m_hero->getPosition();
	std::array<sf::Vector2f, NUMBER_PLATES> platePosition;
	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		platePosition[i] = m_plates[i]->getPosition();
	}
	
	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		if (((doodlePosition.y + DOODLE_HEIGHT >= platePosition[i].y) && (doodlePosition.y + DOODLE_HEIGHT <= platePosition[i].y + PLATE_HEIGHT)
			&& (doodlePosition.x + DOODLE_WIDTH >= platePosition[i].x) && (doodlePosition.x - PLATE_WIDTH <= platePosition[i].x)))
		{
			if ((m_plates[i]->getType() == PlateType::UNSTABLE) || (m_plates[i]->getType() == PlateType::UNSTABLE_DYNAMIC_X))
			{
				m_plates[i]->setFallStatus(true);
				continue;
			}

			if (m_plates[i]->getType() == PlateType::CLOUD)
			{
				m_plates[i]->setPosition(sf::Vector2f(100.f, 1000.f));
				return Collision::COLLISION_GHOST_PLATE;
			}
			return  Collision::COLLISION_PLATE;
		}
	}
	return Collision::NO_COLLISION;
}

Collision GameScene::checkCollisionHole()
{
	auto doodlePosition = m_hero->getPosition();
	if (((doodlePosition.y + DOODLE_HEIGHT >= m_holePosition.y) && (doodlePosition.y + DOODLE_HEIGHT <= m_holePosition.y + HOLE_HEIGHT)
		&& (doodlePosition.x + DOODLE_WIDTH >= m_holePosition.x) && (doodlePosition.x - HOLE_WIDTH <= m_holePosition.x)))
	{
		return Collision::COLLISION_HOLE;
	}
	return Collision::NO_COLLISION;
}

Collision GameScene::checkCollisionBonus() // TODO: this code want to be refactored to
{
	auto doodlePosition = m_hero->getPosition();
	std::array<sf::Vector2f, NUMBER_BONUSES> bonusPosition;
	for (int i = 0; i < NUMBER_BONUSES; ++i)
	{
		bonusPosition[i] = m_bonuses[i]->getPosition();
	}

	for (int bonusIndex = 0; bonusIndex < NUMBER_BONUSES; ++bonusIndex)
	{
		switch (m_bonuses[bonusIndex]->getBonusType())
		{
		case BonusType::SPRING:
			if (((doodlePosition.y + DOODLE_HEIGHT >= bonusPosition[bonusIndex].y) && (doodlePosition.y + DOODLE_HEIGHT <= bonusPosition[bonusIndex].y + SPRING_HEIGHT)
				&& (doodlePosition.x + DOODLE_WIDTH >= bonusPosition[bonusIndex].x) && (doodlePosition.x - SPRING_WIDTH <= bonusPosition[bonusIndex].x)))
			{
				m_actualBonusId = bonusIndex;
				return Collision::COLLISION_SPRING;
			}
			break;
		case BonusType::TRAMPOLINE:
			if (((doodlePosition.y + DOODLE_HEIGHT >= bonusPosition[bonusIndex].y) && (doodlePosition.y + DOODLE_HEIGHT <= bonusPosition[bonusIndex].y + TRAMPOLINE_HEIGHT)
				&& (doodlePosition.x + DOODLE_WIDTH >= bonusPosition[bonusIndex].x) && (doodlePosition.x - TRAMPOLINE_WIDTH <= bonusPosition[bonusIndex].x)))
			{
				m_actualBonusId = bonusIndex;
				return Collision::COLLISION_TRAMPLANE;
			}
			break;
		case BonusType::HAT_HELICOPTER:
			if (((doodlePosition.y + DOODLE_HEIGHT >= bonusPosition[bonusIndex].y) && (doodlePosition.y + DOODLE_HEIGHT <= bonusPosition[bonusIndex].y + HAT_HELICOPTER_HEIGHT)
				&& (doodlePosition.x + DOODLE_WIDTH >= bonusPosition[bonusIndex].x) && (doodlePosition.x - HAT_HELICOPTER_WIDTH <= bonusPosition[bonusIndex].x)))
			{
				m_actualBonusId = bonusIndex;
				return Collision::COLLISION_HAT_HELICOPTER;
			}
			break;
		case BonusType::ROCKET:
			if (((doodlePosition.y + DOODLE_HEIGHT >= bonusPosition[bonusIndex].y) && (doodlePosition.y + DOODLE_HEIGHT <= bonusPosition[bonusIndex].y + ROCKET_HEIGHT)
				&& (doodlePosition.x + DOODLE_WIDTH >= bonusPosition[bonusIndex].x) && (doodlePosition.x - ROCKET_WIDTH <= bonusPosition[bonusIndex].x)))
			{
				m_actualBonusId = bonusIndex;
				return Collision::COLLISION_ROCKET;
			}
			break;
		}
	}
	return Collision::NO_COLLISION;
}

uint64_t GameScene::getScore() const
{
	return m_points;
}
