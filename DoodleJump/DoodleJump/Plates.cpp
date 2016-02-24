#include "stdafx.h"
#include "sheet.h"


void generPlates(Game & game)
{
	sf::Vector2f doodlePosition = game.hero.body->getPosition();
	sf::Vector2f platePosition[NUMBER_PLATES];

	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		platePosition[i] = game.plate[i].body->getPosition();
		float x = float(rand() % (550 - PLATE_WIDTH));
		float y = float(-1 * rand() % 150); // Сюда запилить функцию для равномерной генерации плит по высоте

		if (platePosition[i].y >= doodlePosition.y + DOODLE_HEIGHT + 275 + 2*PLATE_HEIGHT)
		{
			switch (rand() % 3)
			{
			case 0:
				game.plate[i].type = PlateType::STATIC;
				game.plate[i].direction.x = DirectionX::NONE;
				game.plate[i].body->setTexture(game.assets.PLATE_STATIC_TEXTURE);
				break;
			case 1:
				game.plate[i].type = PlateType::DYNAMIC_X;
				switch (rand() % 2)
				{
				case 0:
					game.plate[i].direction.x = DirectionX::LEFT;
					break;
				case 1:
					game.plate[i].direction.x = DirectionX::RIGHT;
					break;
				}
				game.plate[i].body->setTexture(game.assets.PLATE_DYNAMIC_TEXTURE);
				break;
			case 2:
				game.plate[i].type = PlateType::CLOUD;
				game.plate[i].direction.x = DirectionX::NONE;
				game.plate[i].body->setTexture(game.assets.PLATE_CLOUD_TEXTURE);
				break;
			}
			game.plate[i].body->setPosition(x, doodlePosition.y + y - 440.f);  // 40?! What is it?
		}
	}
}

void initialPlates(Game & game) // эту функцию можно убрать, либо в неё засунуть generPlates() + в конце менять начальные координаты + создавать прямоугольник
{
	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		game.plate[i].body = new sf::Sprite;
		/*switch (rand() % 3)
		{
		case 0:
			game.plate[i].type = PlateType::STATIC;
			game.plate[i].direction.x = DirectionX::NONE;
			game.plate[i].body->setTexture(game.assets.PLATE_STATIC_TEXTURE);
			break;
		case 1:
			game.plate[i].type = PlateType::DYNAMIC_X;
			switch (rand() % 2)
			{
			case 0:
				game.plate[i].direction.x = DirectionX::LEFT;
				break;
			case 1:
				game.plate[i].direction.x = DirectionX::RIGHT;
				break;
			}
			game.plate[i].body->setTexture(game.assets.PLATE_DYNAMIC_TEXTURE);
			break;
		case 2:
			game.plate[i].type = PlateType::CLOUD;
			game.plate[i].direction.x = DirectionX::NONE;
			game.plate[i].body->setTexture(game.assets.PLATE_CLOUD_TEXTURE);
			break;
		}*/
		game.plate[i].type = PlateType::STATIC;  // TODO: костыль...
		game.plate[i].direction.x = DirectionX::NONE;
		game.plate[i].body->setTexture(game.assets.PLATE_STATIC_TEXTURE);

		float x = float(rand() % (550 - PLATE_WIDTH));
		float y = float(rand() % (700 - PLATE_HEIGHT)); // Сюда запилить функцию для равномерной генерации плит по высоте
		game.plate[i].body->setPosition(x, y);
	}
}

void moveDynamicPlates(Game & game) // TODO: придётся дописать смену направления для бонусов
{
	sf::Vector2f position(0.f, 0.f);
	sf::Vector2f platePosition[NUMBER_PLATES];

	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		platePosition[i] = game.plate[i].body->getPosition();
		if (game.plate[i].type == PlateType::DYNAMIC_X) // лишнее условие, но так нагляднее
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
				if (platePosition[i].x >= 550 - PLATE_WIDTH - STEP) // 550 - это ширина экрана
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