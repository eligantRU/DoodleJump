#include "stdafx.h"
#include "sheet.h"

void buildBonus(Game & game, BonusType bonusType, int bonusIndex, sf::Vector2f platePosition)
{
	Bonus & bonus = game.bonus[bonusIndex];

	switch (bonusType)
	{
		case BonusType::SPRING:
		{
			int x = rand() % (PLATE_WIDTH - SPRING_WIDTH);
			bonus.body = new sf::Sprite;
			bonus.type = BonusType::SPRING;
			bonus.body->setPosition(platePosition.x + x, platePosition.y - SPRING_HEIGHT);
			bonus.body->setTexture(game.assets.SPRING_TEXTURE);
			break;
		}
		case BonusType::TRAMPOLINE:
		{
			int x = rand() % (PLATE_WIDTH - TRAMPOLINE_WIDTH);
			bonus.body = new sf::Sprite;
			bonus.type = BonusType::TRAMPOLINE;
			bonus.body->setPosition(platePosition.x + x, platePosition.y - TRAMPOLINE_HEIGHT);
			bonus.body->setTexture(game.assets.TRAMPOLINE_TEXTURE);
			break;
		}
		case BonusType::HAT_HELICOPTER:
		{
			int x = rand() % (PLATE_WIDTH - SPRING_WIDTH);
			bonus.body = new sf::Sprite;
			bonus.type = BonusType::HAT_HELICOPTER;
			bonus.body->setPosition(platePosition.x + x, platePosition.y - HAT_HELICOPTER_HEIGHT);
			switch (rand() % 2)
			{
			case 0:
				bonus.body->setTexture(game.assets.HAT_HELOCPTER_NONE_LEFT_TEXTURE);
				break;
			case 1:
				bonus.body->setTexture(game.assets.HAT_HELOCPTER_NONE_RIGHT_TEXTURE);
				break;
			}
			break;
		}
		case BonusType::ROCKET:
		{
			int x = rand() % (PLATE_WIDTH - ROCKET_WIDTH);
			bonus.body = new sf::Sprite;
			bonus.type = BonusType::ROCKET;
			bonus.body->setPosition(platePosition.x + x, platePosition.y - ROCKET_HEIGHT);
			bonus.body->setTexture(game.assets.ROCKET_NONE_TEXTURE);
			break;
		}
	}
}

void initBonuses(Game & game)
{
	std::vector<sf::Vector2f> platePosition;

	for (Plate & plate : game.plate)
	{
		if (plate.type == PlateType::STATIC)
		{
			platePosition.push_back(plate.body->getPosition());
		}
	}
	for (int i = 0; i < NUMBER_BONUSES; ++i)
	{
		BonusType type = (rand() % 2) ? BonusType::SPRING : BonusType::TRAMPOLINE;
		buildBonus(game, type, i, platePosition[rand() % platePosition.size()]);
	}
}

void generBonuses(Game & game)
{
	sf::Vector2f doodlePosition = game.hero.body->getPosition();
	sf::Vector2f bonusPosition[NUMBER_BONUSES];
	sf::Vector2f platePosition;

	for (int bonusIndex = 0; bonusIndex < NUMBER_BONUSES; ++bonusIndex)
	{
		bonusPosition[bonusIndex] = game.bonus[bonusIndex].body->getPosition();

		if (bonusPosition[bonusIndex].y >= doodlePosition.y + DOODLE_HEIGHT + 275 + DOODLE_HEIGHT) // DOODLE_HEIGHT в конце -- подгонка
		{
			for (int plateIndex = 0; plateIndex < NUMBER_PLATES; ++plateIndex)
			{
				platePosition = game.plate[plateIndex].body->getPosition();
				if ((platePosition.y <= doodlePosition.y - 275) && (game.plate[plateIndex].type == PlateType::STATIC))
				{
					int randomNum = rand() % 4;
					switch (randomNum)
					{
					case 0:
						buildBonus(game, BonusType::SPRING, bonusIndex, platePosition);
						break;
					case 1:
						buildBonus(game, BonusType::TRAMPOLINE, bonusIndex, platePosition);
						break;
					case 2:
						buildBonus(game, BonusType::HAT_HELICOPTER, bonusIndex, platePosition);
						break;
					case 3:
						buildBonus(game, BonusType::ROCKET, bonusIndex, platePosition);
						break;
					}
				}
			}
		}
	}
}
