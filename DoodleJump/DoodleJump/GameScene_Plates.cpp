#include "stdafx.h"
#include "sheet.h"

int GameScene::getLowermostPlateID() const
{
	int lowermostPlateID = 0;
	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		if (m_plates[i]->getPosition().y > m_plates[lowermostPlateID]->getPosition().y)
		{
			lowermostPlateID = i;
		}
	}
	return lowermostPlateID;
}

int GameScene::getUppermostPlateID() const
{
	int uppermostPlateID = 0;
	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		if (m_plates[i]->getPosition().y < m_plates[uppermostPlateID]->getPosition().y)
		{
			uppermostPlateID = i;
		}
	}
	return uppermostPlateID;
}

sf::Vector2f GameScene::getCenterPlatePosition(int plateID) const
{
	float x = m_plates[plateID]->getPosition().x + PLATE_WIDTH / 2;
	float y = m_plates[plateID]->getPosition().y + PLATE_HEIGHT / 2;

	return sf::Vector2f(x, y);
}

void GameScene::buildPlate(int startingPointPlateID, int plateIndex)
{
	sf::Vector2f startingPoint = getCenterPlatePosition(startingPointPlateID);

	float y = float((rand() % 191) + PLATE_HEIGHT + ROCKET_HEIGHT);
	float x = (sqrt(242 * 242 - y * y));

	if (startingPoint.x + x > WINDOW_WIDTH - PLATE_WIDTH)
	{
		x = float(rand() % (WINDOW_WIDTH - PLATE_WIDTH));
	}
	
	int divider = 3 + rand() % (1 + plateIndex % 2); // NOTE: interesting engineering solution
	switch (rand() % divider)
	{
	case 0:
		m_plates[plateIndex]->setType(PlateType::STATIC);
		m_plates[plateIndex]->setTexture(m_assets.PLATE_STATIC_TEXTURE);
		m_plates[plateIndex]->setSpeedX(0);
		break;
	case 1:
		m_plates[plateIndex]->setType(PlateType::STATIC_DYNAMIC_X);
		m_plates[plateIndex]->setTexture(m_assets.PLATE_DYNAMIC_TEXTURE);

		m_plates[plateIndex]->setSpeedX((rand() % 3) + 1);
		if (rand() % 2)
		{
			m_plates[plateIndex]->setSpeedX(-m_plates[plateIndex]->getSpeedX());
		}
		break;
	case 2:
		m_plates[plateIndex]->setType(PlateType::CLOUD);
		m_plates[plateIndex]->setTexture(m_assets.PLATE_CLOUD_TEXTURE);
		m_plates[plateIndex]->setSpeedX(0);
		break;
	case 3:
		m_plates[plateIndex]->setType(PlateType::UNSTABLE_DYNAMIC_X);
		m_plates[plateIndex]->setTexture(m_assets.PLATE_UNSTABLE_TEXTURE);

		m_plates[plateIndex]->setSpeedX((rand() % 3) + 1);
		if (rand() % 2)
		{
			m_plates[plateIndex]->setSpeedX(-m_plates[plateIndex]->getSpeedX());
		}
		break;
	default:
		break;
	}
	m_plates[plateIndex]->setRotation(0);
	m_plates[plateIndex]->setPosition(sf::Vector2f(x, startingPoint.y - y));
}

void GameScene::initPlates()
{
	int uppermostPlateID;
	float viewPositionY = m_view.getCenter().y;
	for (int i = 1; i < NUMBER_PLATES; ++(++i))
	{
		if ((m_plates[i]->getPosition().y < viewPositionY + 350) && (m_plates[i + 1]->getPosition().y < viewPositionY + 350))
		{
			uppermostPlateID = getUppermostPlateID();
			buildPlate(uppermostPlateID, i);
			buildPlate(uppermostPlateID, i + 1);
		}
	}
}

void GameScene::generPlates() // TODO: see on initPlates(): they r equal! NOTE: 0 not 1! > not <
{
	int uppermostPlateID;
	float viewPositionY = m_view.getCenter().y;
	for (int i = 0; i < NUMBER_PLATES; ++(++i))
	{
		if ((m_plates[i]->getPosition().y > viewPositionY + 350) && (m_plates[i + 1]->getPosition().y > viewPositionY + 350))
		{
			uppermostPlateID = getUppermostPlateID();
			buildPlate(uppermostPlateID, i);
			buildPlate(uppermostPlateID, i + 1);
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
			m_plates[plateIndex]->move(sf::Vector2f(-STEP, 4 * STEP));
			if (m_plates[plateIndex]->getPosition().y >= m_view.getCenter().y + WINDOW_HEIGHT / 2)
			{
				m_plates[plateIndex]->setRotation(0);
				m_plates[plateIndex]->setFallStatus(false);
			}
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
			if (platePosition.x <= 0)
			{
				m_plates[i]->setSpeedX(-speedX);
			}
		}
		if (speedX > 0)
		{
			if (platePosition.x >= WINDOW_WIDTH - PLATE_WIDTH)
			{
				m_plates[i]->setSpeedX(-speedX);
			}
		}
		m_plates[i]->move(sf::Vector2f(float(speedX), 0.f));
	}
}
