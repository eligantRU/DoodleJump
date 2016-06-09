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
		m_hero->setRotation(0);
		m_actualBonus = BonusType::NO;
	}
	else
	{
		m_hero->rotate(360 / TRAMPLANE_DELTA_HEIGHT);
	}
}

void GameScene::applyAnimationStep(SAnimationStep animationStep)
{
	DirectionX doodleLastDirection = m_hero->getLastDirection();
	sf::Vector2f doodlePosition = m_hero->getPosition();
	
	if (doodleLastDirection == DirectionX::RIGHT)
	{
		m_bonuses[m_actualBonusId]->setTexture(animationStep.m_leftTexture); 
		m_bonuses[m_actualBonusId]->setPosition(sf::Vector2f(doodlePosition.x + animationStep.m_leftOffset.x, doodlePosition.y + animationStep.m_leftOffset.y));
	}
	else if (doodleLastDirection == DirectionX::LEFT)
	{
		m_bonuses[m_actualBonusId]->setTexture(animationStep.m_rightTexture);
		m_bonuses[m_actualBonusId]->setPosition(sf::Vector2f(doodlePosition.x + DOODLE_WIDTH + animationStep.m_rightOffset.x, doodlePosition.y + animationStep.m_rightOffset.y));
	}
}

void GameScene::fallBonus(int bonusID)
{
	BonusType bonusType = m_bonuses[bonusID]->getBonusType();
	
	switch (bonusType)
	{
	case BonusType::HAT_HELICOPTER:
		m_bonuses[bonusID]->setTexture(m_assets.HAT_HELOCPTER_NONE_LEFT_TEXTURE);
		break;
	case BonusType::ROCKET:
		m_bonuses[bonusID]->setTexture(m_assets.ROCKET_NONE_TEXTURE);
		break;
	default:
		assert(0);
	}
	m_bonuses[bonusID]->setPosition(m_hero->getPosition());
	m_bonuses[bonusID]->rotate(-10.f);
	m_offsetFallBonus += sf::Vector2f(-6 * STEP, 8 * STEP);
    m_bonuses[bonusID]->move(m_offsetFallBonus);
}

void GameScene::animateRocket()
{
	const std::vector<SAnimationStep> ROCKET_ANIMATION_STEPS = {
		SAnimationStep(0, 1, m_assets.ROCKET_0_LEFT_TEXTURE, m_assets.ROCKET_0_RIGHT_TEXTURE, sf::Vector2f(-13.f, 0), sf::Vector2f(1.f, 0)),
		SAnimationStep(2, 4, m_assets.ROCKET_1_LEFT_TEXTURE, m_assets.ROCKET_1_RIGHT_TEXTURE, sf::Vector2f(-13.f, 0), sf::Vector2f(1.f, 0)),
		SAnimationStep(5, 7, m_assets.ROCKET_2_LEFT_TEXTURE, m_assets.ROCKET_2_RIGHT_TEXTURE, sf::Vector2f(-15.f, 0), sf::Vector2f(0, 0)),
		SAnimationStep(8, 10, m_assets.ROCKET_3_LEFT_TEXTURE, m_assets.ROCKET_3_RIGHT_TEXTURE, sf::Vector2f(-17.f, 0), sf::Vector2f(-5.f, 0))
	};

	if ((m_hero->getSpeedY() >= 0) || (m_bonuses[m_actualBonusId]->getPosition().y < m_view.getCenter().y - WINDOW_HEIGHT / 2 - ROCKET_HEIGHT))
	{
		m_animationCounter = 0;
		m_actualBonus = BonusType::NO;
		m_offsetFallBonus = sf::Vector2f(0, 0);
		m_bonuses[m_actualBonusId]->setRotation(0);
		m_bonuses[m_actualBonusId]->setPosition(sf::Vector2f(0, 0));
	}

	auto stepIt = std::find_if(ROCKET_ANIMATION_STEPS.begin(), ROCKET_ANIMATION_STEPS.end(), std::bind(&SAnimationStep::IsActive, std::placeholders::_1, m_animationCounter));
	if (stepIt == ROCKET_ANIMATION_STEPS.end())
	{
		m_animationCounter = 0;
	}
	else if (m_actualBonus != BonusType::NO)
	{
		applyAnimationStep(ROCKET_ANIMATION_STEPS[std::distance(ROCKET_ANIMATION_STEPS.begin(), stepIt)]);
		++m_animationCounter;
	}

	if ((m_hero->getSpeedY() >= -0.25 * ROCKET_DELTA_HEIGHT) && (m_actualBonus != BonusType::NO))
	{
		fallBonus(m_actualBonusId);
	}
}

void GameScene::animateHatHelicopter()
{
	const std::vector<SAnimationStep> HAT_HELICOPTER_ANIMATION_STEPS = {
		SAnimationStep(0, 1, m_assets.HAT_HELOCPTER_FLY_LEFT_TEXTURE, m_assets.HAT_HELOCPTER_FLY_LEFT_TEXTURE, sf::Vector2f(0, -14.f), sf::Vector2f(-28.f, -14.f)),
		SAnimationStep(2, 4, m_assets.HAT_HELOCPTER_DIAGONAL_LEFT_TEXTURE, m_assets.HAT_HELOCPTER_DIAGONAL_LEFT_TEXTURE, sf::Vector2f(0, -14.f), sf::Vector2f(-28.f, -14.f)),
		SAnimationStep(5, 7, m_assets.HAT_HELOCPTER_DIAGONAL_RIGHT_TEXTURE, m_assets.HAT_HELOCPTER_DIAGONAL_RIGHT_TEXTURE, sf::Vector2f(0, -14.f), sf::Vector2f(-28.f, -14.f)),
		SAnimationStep(8, 10, m_assets.HAT_HELOCPTER_FLY_RIGHT_TEXTURE, m_assets.HAT_HELOCPTER_FLY_RIGHT_TEXTURE, sf::Vector2f(0, -14.f), sf::Vector2f(-28.f, -20.f))
	};

	if ((m_hero->getSpeedY() >= 0) || (m_bonuses[m_actualBonusId]->getPosition().y < m_view.getCenter().y - WINDOW_HEIGHT / 2 - HAT_HELICOPTER_HEIGHT))
	{
		m_animationCounter = 0;
		m_actualBonus = BonusType::NO;
		m_offsetFallBonus = sf::Vector2f(0, 0);
		m_bonuses[m_actualBonusId]->setRotation(0);
		m_bonuses[m_actualBonusId]->setPosition(sf::Vector2f(0, 0));
	}

	auto stepIt = std::find_if(HAT_HELICOPTER_ANIMATION_STEPS.begin(), HAT_HELICOPTER_ANIMATION_STEPS.end(), std::bind(&SAnimationStep::IsActive, std::placeholders::_1, m_animationCounter));
	if (stepIt == HAT_HELICOPTER_ANIMATION_STEPS.end())
	{
		m_animationCounter = 0;
	}
	else if (m_actualBonus != BonusType::NO)
	{
		applyAnimationStep(HAT_HELICOPTER_ANIMATION_STEPS[std::distance(HAT_HELICOPTER_ANIMATION_STEPS.begin(), stepIt)]);
		++m_animationCounter;
	}

	if ((m_hero->getSpeedY() >= -0.3 * HAT_HELICOPTER_DELTA_HEIGHT) && (m_actualBonus != BonusType::NO))
	{
		fallBonus(m_actualBonusId);
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
