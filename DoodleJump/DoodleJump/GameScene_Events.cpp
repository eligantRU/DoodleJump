#include "stdafx.h"
#include "sheet.h"

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
	checkKeyReleased(event, isNeedUpdate);

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

void GameScene::checkKeyReleased(sf::Event event, bool & isNeedUpdate)
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

bool GameScene::checkGameEnd()
{
	sf::Vector2f doodlePosition = m_hero->getPosition();
	if ((checkCollisionHole() == Collision::COLLISION_HOLE) && ((m_actualBonus == BonusType::NO)))
	{
		m_soundHandler.playSound(m_assets.HOLE_SOUND);
		return true;
	}
	if (doodlePosition.y < m_view.getCenter().y + WINDOW_HEIGHT / 2 - DOODLE_HEIGHT)
	{
		return false;
	}
	m_soundHandler.playSound(m_assets.GAME_OVER_SOUND);
	return true;
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

Collision GameScene::checkCollisionPlate()
{
	sf::Vector2f doodlePosition = m_hero->getPosition();

	for (auto &plate : m_plates)
	{
		sf::Vector2f platePosition = plate->getPosition();
		PlateType plateType = plate->getType();
		if (((doodlePosition.y + DOODLE_HEIGHT >= platePosition.y) && (doodlePosition.y + DOODLE_HEIGHT <= platePosition.y + PLATE_HEIGHT)
			&& (doodlePosition.x + DOODLE_WIDTH >= platePosition.x) && (doodlePosition.x - PLATE_WIDTH <= platePosition.x)))
		{
			switch (plateType)
			{
			case PlateType::UNSTABLE:
				plate->setFallStatus(true);
				m_soundHandler.playSound(m_assets.PLATE_BROKEN_SOUND);
				break;
			case PlateType::CLOUD:
				plate->setPosition(sf::Vector2f(100.f, 1000.f));
				return Collision::COLLISION_GHOST_PLATE;
			default:
				return  Collision::COLLISION_PLATE;
			}
		}
	}
	return Collision::NO_COLLISION;
}

Collision GameScene::checkCollisionHole()
{
	sf::Vector2f doodlePosition = m_hero->getPosition();
	if (((doodlePosition.y + DOODLE_HEIGHT >= m_holePosition.y) && (doodlePosition.y + DOODLE_HEIGHT <= m_holePosition.y + HOLE_HEIGHT)
		&& (doodlePosition.x + DOODLE_WIDTH >= m_holePosition.x) && (doodlePosition.x - HOLE_WIDTH <= m_holePosition.x)))
	{
		return Collision::COLLISION_HOLE;
	}
	return Collision::NO_COLLISION;
}

Collision GameScene::checkCollisionBonus()
{
	sf::Vector2f doodlePosition = m_hero->getPosition();

	int bonusIndex = 0;
	for (auto &bonus : m_bonuses)
	{
		sf::Vector2f bonusPosition = bonus->getPosition();
		switch (bonus->getBonusType())
		{
		case BonusType::SPRING:
			if (((doodlePosition.y + DOODLE_HEIGHT >= bonusPosition.y) && (doodlePosition.y + DOODLE_HEIGHT <= bonusPosition.y + SPRING_HEIGHT)
				&& (doodlePosition.x + DOODLE_WIDTH >= bonusPosition.x) && (doodlePosition.x - SPRING_WIDTH <= bonusPosition.x)))
			{
				m_actualBonusId = bonusIndex;
				return Collision::COLLISION_SPRING;
			}
			break;
		case BonusType::TRAMPOLINE:
			if (((doodlePosition.y + DOODLE_HEIGHT >= bonusPosition.y) && (doodlePosition.y + DOODLE_HEIGHT <= bonusPosition.y + TRAMPOLINE_HEIGHT)
				&& (doodlePosition.x + DOODLE_WIDTH >= bonusPosition.x) && (doodlePosition.x - TRAMPOLINE_WIDTH <= bonusPosition.x)))
			{
				m_actualBonusId = bonusIndex;
				return Collision::COLLISION_TRAMPLANE;
			}
			break;
		case BonusType::HAT_HELICOPTER:
			if (((doodlePosition.y + DOODLE_HEIGHT >= bonusPosition.y) && (doodlePosition.y + DOODLE_HEIGHT <= bonusPosition.y + HAT_HELICOPTER_HEIGHT)
				&& (doodlePosition.x + DOODLE_WIDTH >= bonusPosition.x) && (doodlePosition.x - HAT_HELICOPTER_WIDTH <= bonusPosition.x)))
			{
				m_actualBonusId = bonusIndex;
				return Collision::COLLISION_HAT_HELICOPTER;
			}
			break;
		case BonusType::ROCKET:
			if (((doodlePosition.y + DOODLE_HEIGHT >= bonusPosition.y) && (doodlePosition.y + DOODLE_HEIGHT <= bonusPosition.y + ROCKET_HEIGHT)
				&& (doodlePosition.x + DOODLE_WIDTH >= bonusPosition.x) && (doodlePosition.x - ROCKET_WIDTH <= bonusPosition.x)))
			{
				m_actualBonusId = bonusIndex;
				return Collision::COLLISION_ROCKET;
			}
			break;
		}
		++bonusIndex;
	}
	return Collision::NO_COLLISION;
}
