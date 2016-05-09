#include "stdafx.h"
#include "sheet.h"

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
	else if (doodleDirection == DirectionX::LEFT)
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

float GameScene::checkDoodleFall()
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
		m_soundHandler.playSound(m_assets.JUMP_SOUND);
		return PLATE_DELTA_HEIGHT;
	case Collision::COLLISION_GHOST_PLATE:
		m_actualBonus = BonusType::NO;
		m_soundHandler.playSound(m_assets.PLATE_GHOST_SOUND);
		return PLATE_DELTA_HEIGHT;
	case Collision::COLLISION_SPRING:
		m_actualBonus = BonusType::SPRING;
		m_soundHandler.playSound(m_assets.SPRING_SOUND);
		return SPRING_DELTA_HEIGHT;
	case Collision::COLLISION_TRAMPLANE:
		m_actualBonus = BonusType::TRAMPOLINE;
		m_soundHandler.playSound(m_assets.TRAMPOLINE_SOUND);
		return TRAMPLANE_DELTA_HEIGHT;
	case Collision::COLLISION_HAT_HELICOPTER:
		m_actualBonus = BonusType::HAT_HELICOPTER;
		m_soundHandler.playSound(m_assets.HAT_HELICOPTER_SOUND);
		return HAT_HELICOPTER_DELTA_HEIGHT;
	case Collision::COLLISION_ROCKET:
		m_actualBonus = BonusType::ROCKET;
		m_soundHandler.playSound(m_assets.ROCKET_SOUND);
		return ROCKET_DELTA_HEIGHT;
	default:
		return 0.f;
	}
}
