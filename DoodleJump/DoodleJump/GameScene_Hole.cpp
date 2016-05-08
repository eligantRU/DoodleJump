#include "stdafx.h"
#include "sheet.h"

void GameScene::generHole()
{
	if (m_hole->getPosition().y >= m_view.getCenter().y + WINDOW_HEIGHT / 2)
	{
		m_holePosition.x = float(rand() % (WINDOW_WIDTH - HOLE_WIDTH));
		m_holePosition.y = m_hero->getPosition().y - 1.f * float(rand() % 15000) - 10.f * 750.f;
		m_hole->setPosition(sf::Vector2f(m_holePosition.x, m_holePosition.y));
	}
}
