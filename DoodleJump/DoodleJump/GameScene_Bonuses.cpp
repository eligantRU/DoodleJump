#include "stdafx.h"
#include "sheet.h"

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
		assert(0);
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
		m_bonuses[m_actualBonusId]->setRotation(0);
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

	if (m_hero->getSpeedY() >= -0.05 * ROCKET_DELTA_HEIGHT && m_actualBonus != BonusType::NO)
	{
		m_bonuses[m_actualBonusId]->setTexture(m_assets.ROCKET_NONE_TEXTURE);
		if (m_actualBonus != BonusType::NO)
		{
			m_bonuses[m_actualBonusId]->setPosition(doodlePosition);
		}
		m_bonuses[m_actualBonusId]->rotate(-10);
		m_offsetFallBonus.x += -5 * STEP;
		m_offsetFallBonus.y += 6 * STEP;
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
		m_bonuses[m_actualBonusId]->setRotation(0);
		m_bonuses[m_actualBonusId]->move(sf::Vector2f(0.f, float(WINDOW_HEIGHT)));
	}

	if (m_hero->getSpeedY() < -0.05 * HAT_HELICOPTER_DELTA_HEIGHT)
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

	if (m_hero->getSpeedY() >= -0.05 * HAT_HELICOPTER_DELTA_HEIGHT && m_actualBonus != BonusType::NO)
	{
		m_bonuses[m_actualBonusId]->setTexture(m_assets.HAT_HELOCPTER_NONE_LEFT_TEXTURE);
		if (m_actualBonus != BonusType::NO)
		{
			m_bonuses[m_actualBonusId]->setPosition(sf::Vector2f(doodlePosition.x, doodlePosition.y - 14));
		}
		m_bonuses[m_actualBonusId]->rotate(-10);
		m_offsetFallBonus.x += -5 * STEP;
		m_offsetFallBonus.y += 6 * STEP;
		m_bonuses[m_actualBonusId]->move(sf::Vector2f(m_offsetFallBonus));
	}
}

void GameScene::initBonuses()
{
	for (int bonusIndex = 0; bonusIndex < NUMBER_BONUSES; ++bonusIndex)
	{
		BonusType type = (rand() % 2) ? BonusType::SPRING : BonusType::TRAMPOLINE;
		buildBonus(type, bonusIndex, 0);
	}
}

void GameScene::buildBonus(BonusType bonusType, int bonusIndex, int plateIndex)
{
	sf::Vector2f platePosition = m_plates[plateIndex]->getPosition();
	int x = 0;
	switch (bonusType)
	{
	case BonusType::SPRING:
		x = rand() % (PLATE_WIDTH - SPRING_WIDTH);
		m_bonuses[bonusIndex]->setBonusType(BonusType::SPRING);
		m_bonuses[bonusIndex]->setPosition(sf::Vector2f(platePosition.x + x, platePosition.y - SPRING_HEIGHT));
		m_bonuses[bonusIndex]->setTexture(m_assets.SPRING_TEXTURE);
		break;
	case BonusType::TRAMPOLINE:
		x = rand() % (PLATE_WIDTH - TRAMPOLINE_WIDTH);
		m_bonuses[bonusIndex]->setBonusType(BonusType::TRAMPOLINE);
		m_bonuses[bonusIndex]->setPosition(sf::Vector2f(platePosition.x + x, platePosition.y - TRAMPOLINE_HEIGHT));
		m_bonuses[bonusIndex]->setTexture(m_assets.TRAMPOLINE_TEXTURE);
		break;
	case BonusType::HAT_HELICOPTER:
		x = rand() % (PLATE_WIDTH - SPRING_WIDTH);
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
		default:
			assert(0);
		}
		break;
	case BonusType::ROCKET:
		x = rand() % (PLATE_WIDTH - ROCKET_WIDTH);
		m_bonuses[bonusIndex]->setBonusType(BonusType::ROCKET);
		m_bonuses[bonusIndex]->setPosition(sf::Vector2f(platePosition.x + x, platePosition.y - ROCKET_HEIGHT));
		m_bonuses[bonusIndex]->setTexture(m_assets.ROCKET_NONE_TEXTURE);
		break;
	default:
		assert(0);
	}
	m_bonuses[bonusIndex]->setPlateIndex(plateIndex);
	m_bonuses[bonusIndex]->setSpeedX(m_plates[plateIndex]->getSpeedX());
	m_bonuses[bonusIndex]->setRotation(0);
	m_bonuses[bonusIndex]->setPlateOffset(x);
}

void GameScene::moveBonuses()
{
	for (auto &bonus : m_bonuses)
	{
		sf::Vector2f bonusPosition = bonus->getPosition();
		int speedX = bonus->getSpeedX();
		int plateOffset = bonus->getPlateOffset();
		if (speedX < 0)
		{
			if (bonusPosition.x <= plateOffset)
			{
				bonus->setSpeedX(-speedX);
			}
		}
		if (speedX > 0)
		{
			if (bonusPosition.x >= WINDOW_WIDTH - PLATE_WIDTH + plateOffset)
			{
				bonus->setSpeedX(-speedX);
			}
		}
		bonus->move(sf::Vector2f(float(speedX), 0));
	}
}

void GameScene::generBonuses()
{
	for (int bonusIndex = 0; bonusIndex < NUMBER_BONUSES; ++bonusIndex)
	{
		float bonusPositionY = m_bonuses[bonusIndex]->getPosition().y;
		if (bonusPositionY > m_view.getCenter().y + WINDOW_HEIGHT / 2)
		{
			for (int plateIndex = 0; plateIndex < NUMBER_PLATES; ++plateIndex)
			{
				sf::Vector2f platePosition = m_plates[plateIndex]->getPosition();
				PlateType plateType = m_plates[plateIndex]->getType();

				if ((platePosition.y < m_view.getCenter().y - WINDOW_HEIGHT / 2 - ROCKET_HEIGHT) &&
					((plateType == PlateType::STATIC) || (plateType == PlateType::STATIC_DYNAMIC_X)))
				{
					int randomNum = rand() % 4;
					switch (randomNum)
					{
					case 0:
						buildBonus(BonusType::SPRING, bonusIndex, plateIndex);
						break;
					case 1:
						buildBonus(BonusType::TRAMPOLINE, bonusIndex, plateIndex);
						break;
					case 2:
						buildBonus(BonusType::HAT_HELICOPTER, bonusIndex, plateIndex);
						break;
					case 3:
						buildBonus(BonusType::ROCKET, bonusIndex, plateIndex);
						break;
					default:
						assert(0);
					}
				}
			}
		}
	}
}

int GameScene::getBonusCollisionID() const
{
	sf::Vector2f doodlePosition = m_hero->getPosition();
	for (int bonusIndex = 0; bonusIndex < NUMBER_BONUSES; ++bonusIndex)
	{
		sf::Vector2f bonusPosition = m_bonuses[bonusIndex]->getPosition();
		switch (m_bonuses[bonusIndex]->getBonusType())
		{
		case BonusType::SPRING:
			if (((doodlePosition.y + DOODLE_HEIGHT >= bonusPosition.y) && (doodlePosition.y + DOODLE_HEIGHT <= bonusPosition.y + SPRING_HEIGHT)
				&& (doodlePosition.x + DOODLE_WIDTH >= bonusPosition.x) && (doodlePosition.x - SPRING_WIDTH <= bonusPosition.x)))
			{
				return bonusIndex;
			}
			break;
		case BonusType::TRAMPOLINE:
			if (((doodlePosition.y + DOODLE_HEIGHT >= bonusPosition.y) && (doodlePosition.y + DOODLE_HEIGHT <= bonusPosition.y + TRAMPOLINE_HEIGHT)
				&& (doodlePosition.x + DOODLE_WIDTH >= bonusPosition.x) && (doodlePosition.x - TRAMPOLINE_WIDTH <= bonusPosition.x)))
			{
				return bonusIndex;
			}
			break;
		case BonusType::HAT_HELICOPTER:
			if (((doodlePosition.y + DOODLE_HEIGHT >= bonusPosition.y) && (doodlePosition.y + DOODLE_HEIGHT <= bonusPosition.y + HAT_HELICOPTER_HEIGHT)
				&& (doodlePosition.x + DOODLE_WIDTH >= bonusPosition.x) && (doodlePosition.x - HAT_HELICOPTER_WIDTH <= bonusPosition.x)))
			{
				return bonusIndex;
			}
			break;
		case BonusType::ROCKET:
			if (((doodlePosition.y + DOODLE_HEIGHT >= bonusPosition.y) && (doodlePosition.y + DOODLE_HEIGHT <= bonusPosition.y + ROCKET_HEIGHT)
				&& (doodlePosition.x + DOODLE_WIDTH >= bonusPosition.x) && (doodlePosition.x - ROCKET_WIDTH <= bonusPosition.x)))
			{
				return bonusIndex;
			}
			break;
		default:
			assert(0);
		}
	}
	return -1;
}

void GameScene::getBonusJumping()
{
	int collisionBonudID = getBonusCollisionID();
	if (collisionBonudID != -1)
	{
		m_actualBonusId = collisionBonudID;
		switch (m_bonuses[collisionBonudID]->getBonusType())
		{
		case BonusType::ROCKET:
			m_actualBonus = BonusType::ROCKET;
			m_soundHandler.playSound(m_assets.ROCKET_SOUND);
			m_hero->setSpeedY(-ROCKET_DELTA_HEIGHT);
			break;
		case BonusType::HAT_HELICOPTER:
			m_actualBonus = BonusType::HAT_HELICOPTER;
			m_soundHandler.playSound(m_assets.HAT_HELICOPTER_SOUND);
			m_hero->setSpeedY(-HAT_HELICOPTER_DELTA_HEIGHT);
			break;
		default:
			break;
		}
	}
}
