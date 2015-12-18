#pragma once

void initialBonuses(Game & game);
void generBonuses(Game & game);
void buildBonus(Game & game, BonusType bonusType, int i);
void buildBonus(Game & game, BonusType bonusType, int i, sf::Vector2f platePosition);

void buildBonus(Game & game, BonusType bonusType, int i)
{
	// отдельная функция // getPlatesPositions() из getPlatePosition()
	sf::Vector2f platePosition[NUMBER_PLATES];

	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		platePosition[i] = game.plate[i].body->getPosition();
	} //
	int N = rand() % NUMBER_PLATES;

	int x;

	switch (bonusType)
	{
		case SPRING:
		{
			x = rand() % (PLATE_WIDTH - SPRING_WIDTH);
			game.bonus[i].body = new sf::Sprite;
			game.bonus[i].type = SPRING;
			game.bonus[i].body->setPosition(platePosition[N].x + x, platePosition[N].y - SPRING_HEIGHT);
			game.bonus[i].body->setTexture(g_Assets.SPRING_TEXTURE);
			break;
		}
		case TRAMPOLINE:
		{
			x = rand() % (PLATE_WIDTH - TRAMPOLINE_WIDTH);
			game.bonus[i].body = new sf::Sprite;
			game.bonus[i].type = TRAMPOLINE;
			game.bonus[i].body->setPosition(platePosition[N].x + x, platePosition[N].y - TRAMPOLINE_HEIGHT);
			game.bonus[i].body->setTexture(g_Assets.TRAMPOLINE_TEXTURE);
			break;
		}
	}
}

void buildBonus(Game & game, BonusType bonusType, int i, sf::Vector2f platePosition)
{
	int x, randomNum;

	switch (bonusType)
	{
		case SPRING:
		{
			x = rand() % (PLATE_WIDTH - SPRING_WIDTH);
			game.bonus[i].body = new sf::Sprite;
			game.bonus[i].type = SPRING;
			game.bonus[i].body->setPosition(platePosition.x + x, platePosition.y - SPRING_HEIGHT);
			game.bonus[i].body->setTexture(g_Assets.SPRING_TEXTURE);
			break;
		}
		case TRAMPOLINE:
		{
			x = rand() % (PLATE_WIDTH - TRAMPOLINE_WIDTH);
			game.bonus[i].body = new sf::Sprite;
			game.bonus[i].type = TRAMPOLINE;
			game.bonus[i].body->setPosition(platePosition.x + x, platePosition.y - TRAMPOLINE_HEIGHT);
			game.bonus[i].body->setTexture(g_Assets.TRAMPOLINE_TEXTURE);
			break;
		}
		case HAT_HELICOPTER:
		{
			randomNum = rand() % 2;
			x = rand() % (PLATE_WIDTH - SPRING_WIDTH);
			game.bonus[i].body = new sf::Sprite;
			game.bonus[i].type = HAT_HELICOPTER;
			game.bonus[i].body->setPosition(platePosition.x + x, platePosition.y - HAT_HELICOPTER_HEIGHT);
			switch (randomNum)
			{
			case 0:
				game.bonus[i].body->setTexture(g_Assets.HAT_HELOCPTER_NONE_LEFT_TEXTURE);
				break;
			case 1:
				game.bonus[i].body->setTexture(g_Assets.HAT_HELOCPTER_NONE_RIGHT_TEXTURE);
				break;
			}
			break;
		}
		case ROCKET:
		{
			x = rand() % (PLATE_WIDTH - ROCKET_WIDTH);
			game.bonus[i].body = new sf::Sprite;
			game.bonus[i].type = ROCKET;
			game.bonus[i].body->setPosition(platePosition.x + x, platePosition.y - ROCKET_HEIGHT);
			game.bonus[i].body->setTexture(g_Assets.ROCKET_NONE_TEXTURE);
			break;
		}
	}
}

void initialBonuses(Game & game)
{
	sf::Vector2f platePosition[NUMBER_PLATES];

	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		platePosition[i] = game.plate[i].body->getPosition();
	}

	double x;
	int N; // What the...
	int randomNum;

	for (int i = 0; i < NUMBER_BONUSES; ++i)
	{
		N = rand() % NUMBER_PLATES;
		if (game.plate[N].type == STATIC)
		{
			randomNum = rand() % 2;

			switch (randomNum)
			{
			case 0:
				buildBonus(game, SPRING, i);
				break;
			case 1:
				buildBonus(game, TRAMPOLINE, i);
				break;
			}
		}
		else
		{
			--i;   // What the hell r u doing?! Fix!
		}
	}
}

void generBonuses(Game & game)
{
	sf::Vector2f doodlePosition = game.hero.body->getPosition();
	sf::Vector2f bonusPosition[NUMBER_BONUSES];
	sf::Vector2f platePosition;
	float x;
	int randomNum;

	for (int i = 0; i < NUMBER_BONUSES; ++i)
	{
		bonusPosition[i] = game.bonus[i].body->getPosition();

		if (bonusPosition[i].y >= doodlePosition.y + DOODLE_HEIGHT + 275 + 10 + 2*PLATE_HEIGHT)                 // WHAT IS IT?! BUG!!!
		{
			for (int j = 0; j < NUMBER_PLATES; ++j)
			{
				platePosition = game.plate[j].body->getPosition();
				if ((platePosition.y <= doodlePosition.y - 275) && (game.plate[j].type == STATIC))
				{
					randomNum = rand() % 4;
					switch (randomNum)
					{
					case 0:
						buildBonus(game, SPRING, i, platePosition);
						break;
					case 1:
						buildBonus(game, TRAMPOLINE, i, platePosition);
						break;
					case 2:
						buildBonus(game, HAT_HELICOPTER, i, platePosition);
						break;
					case 3:
						buildBonus(game, ROCKET, i, platePosition);
						break;
					}
				}
			}
		}
	}
}
