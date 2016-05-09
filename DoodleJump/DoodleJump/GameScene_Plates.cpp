#include "stdafx.h"
#include "sheet.h"

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
	float x, y;
	float offsetY = float((rand() % 100) + PLATE_HEIGHT + DOODLE_HEIGHT);
	float offsetX = (sqrt(242 * 242 - offsetY * offsetY));
	if (rand() % 2)
	{
		offsetX *= -1;
	}
	x = startingPoint.x + offsetX;
	y = startingPoint.y - offsetY;
	if ((startingPoint.x + offsetX > WINDOW_WIDTH - PLATE_WIDTH) || (startingPoint.x + offsetX < 0))
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
		m_plates[plateIndex]->setType(PlateType::UNSTABLE);
		m_plates[plateIndex]->setTexture(m_assets.PLATE_UNSTABLE_TEXTURE);

		m_plates[plateIndex]->setSpeedX(rand() % 3);
		if (rand() % 2)
		{
			m_plates[plateIndex]->setSpeedX(-m_plates[plateIndex]->getSpeedX());
		}
		break;
	default:
		break;
	}
	m_plates[plateIndex]->setRotation(0);
	m_plates[plateIndex]->setPosition(sf::Vector2f(x, y));
}

void GameScene::generPlates()
{
	int uppermostPlateID;
	float viewPositionY = m_view.getCenter().y;
	
	for (int i = 0; i < NUMBER_PLATES; ++(++i))
	{
		if ((m_plates[i]->getPosition().y > viewPositionY + WINDOW_HEIGHT / 2) && (m_plates[i + 1]->getPosition().y > viewPositionY + WINDOW_HEIGHT / 2))
		{
			uppermostPlateID = getUppermostPlateID();
			buildPlate(uppermostPlateID, i);
			buildPlate(uppermostPlateID, i + 1);
		}
	}
}

void GameScene::dropUnstablePlates()
{
	std::for_each(m_plates.begin(), m_plates.end(), [&](std::unique_ptr<Plate> & plate) {
		if (plate->getFallStatus() == true)
		{
			plate->rotate(-1.f);
			plate->move(sf::Vector2f(-STEP, 4 * STEP));
			if (plate->getPosition().y >= m_view.getCenter().y + WINDOW_HEIGHT / 2)
			{
				plate->setRotation(0);
				plate->setFallStatus(false);
			}
		}
	});
}

void GameScene::moveDynamicPlates()
{
	std::for_each(m_plates.begin(), m_plates.end(), [](std::unique_ptr<Plate> & plate) {
		sf::Vector2f platePosition = plate->getPosition();
		int speedX = plate->getSpeedX();
		if (speedX < 0)
		{
			if (platePosition.x <= 0)
			{
				plate->setSpeedX(-speedX);
			}
		}
		if (speedX > 0)
		{
			if (platePosition.x >= WINDOW_WIDTH - PLATE_WIDTH)
			{
				plate->setSpeedX(-speedX);
			}
		}
		plate->move(sf::Vector2f(float(speedX), 0));
	});
}
