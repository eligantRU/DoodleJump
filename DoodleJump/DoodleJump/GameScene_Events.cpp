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
