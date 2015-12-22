#include "stdafx.h"
#include "sheet.h"


void generPlates(Game & game)
{
	sf::Vector2f doodlePosition = game.hero.body->getPosition();
	sf::Vector2f platePosition[NUMBER_PLATES];
	float x, y;
	int randomNum;

	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		platePosition[i] = game.plate[i].body->getPosition();
		x = float(rand() % (550 - PLATE_WIDTH));
		y = float(-1 * rand() % 150);               // ���� �������� ������� ��� ����������� ��������� ���� �� ������

		if (platePosition[i].y >= doodlePosition.y + DOODLE_HEIGHT + 275 + 2*PLATE_HEIGHT)
		{
			randomNum = rand() % 3;
			switch (randomNum)
			{
			case 0:
				game.plate[i].type = PlateType::STATIC;
				game.plate[i].direction.x = DirectionX::NONE;
				game.plate[i].body->setTexture(g_Assets.PLATE_STATIC_TEXTURE);
				break;
			case 1:
				game.plate[i].type = PlateType::DYNAMIC_X;
				randomNum = rand() % 2;
				switch (randomNum)
				{
				case 0:
					game.plate[i].direction.x = DirectionX::LEFT;
					break;
				case 1:
					game.plate[i].direction.x = DirectionX::RIGHT;
					break;
				}
				game.plate[i].body->setTexture(g_Assets.PLATE_DYNAMIC_TEXTURE);
				break;
			case 2:
				game.plate[i].type = PlateType::CLOUD;
				game.plate[i].direction.x = DirectionX::NONE;
				game.plate[i].body->setTexture(g_Assets.PLATE_CLOUD_TEXTURE);
				break;
			}
			game.plate[i].body->setPosition(x, doodlePosition.y + y - 380.f);  // 380?! What is it?
		}
	}
}

void initialPlates(Game & game) // ��� ������� ����� ������, ���� � �� �������� generPlates() + � ����� ������ ��������� ���������� + ��������� �������������
{
	float x, y;
	int randomNum;
	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		game.plate[i].body = new sf::Sprite;
		randomNum = rand() % 3;
		switch (randomNum)
		{
		case 0:
			game.plate[i].type = PlateType::STATIC;
			game.plate[i].direction.x = DirectionX::NONE;
			game.plate[i].body->setTexture(g_Assets.PLATE_STATIC_TEXTURE);
			break;
		case 1:
			game.plate[i].type = PlateType::DYNAMIC_X;
			randomNum = rand() % 2;
			switch (randomNum)
			{
			case 0:
				game.plate[i].direction.x = DirectionX::LEFT;
				break;
			case 1:
				game.plate[i].direction.x = DirectionX::RIGHT;
				break;
			}
			game.plate[i].body->setTexture(g_Assets.PLATE_DYNAMIC_TEXTURE);
			break;
		case 2:
			game.plate[i].type = PlateType::CLOUD;
			game.plate[i].direction.x = DirectionX::NONE;
			game.plate[i].body->setTexture(g_Assets.PLATE_CLOUD_TEXTURE);
			break;
		}
		x = float(rand() % (550 - PLATE_WIDTH));
		y = float(rand() % (700 - PLATE_HEIGHT)); // ���� �������� ������� ��� ����������� ��������� ���� �� ������
		game.plate[i].body->setPosition(x, y);
	}
}

void moveDynamicPlates(Game & game)
{
	sf::Vector2f position(0.f, 0.f);
	sf::Vector2f platePosition[NUMBER_PLATES];

	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		platePosition[i] = game.plate[i].body->getPosition();
		if (game.plate[i].type == PlateType::DYNAMIC_X) // ������ �������, �� ��� ���������
		{
			switch (game.plate[i].direction.x)
			{
			case DirectionX::LEFT:
				if (platePosition[i].x <= STEP)
				{
					game.plate[i].direction.x = DirectionX::RIGHT;
				}
				else
				{
					position.x -= 0.5f * STEP;
				}
				break;
			case DirectionX::RIGHT:
				if (platePosition[i].x >= 550 - PLATE_WIDTH - STEP) // 550 - ��� ������ ������
				{
					game.plate[i].direction.x = DirectionX::LEFT;
				}
				else
				{
					position.x += 0.5f * STEP;
				}
				break;
			default:
				break;
			}
			game.plate[i].body->move(position);
			position.x = 0;
			position.y = 0;
		}
	}
}
