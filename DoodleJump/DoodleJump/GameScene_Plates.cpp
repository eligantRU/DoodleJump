#include "stdafx.h"
#include "sheet.h"

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
			m_plates[i]->setPosition(sf::Vector2f(x1, platePositionY[NUMBER_PLATES - 1] - y1));

			for (int j = 1; j < NUMBER_PLATES / 2; ++(++j)) // NOTE: Oh my God...What the f*ck r u doing?
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
