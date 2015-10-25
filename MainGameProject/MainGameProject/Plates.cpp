int checkDoodleFall(Game & game);
void generPlates(Game & game);
void initialPlates(Game & game);

int checkDoodleFall(Game & game)
{
	sf::Vector2f doodlePosition = game.hero.body->getPosition();
	sf::Vector2f platePosition[NUMBER_PLATES];
	sf::Vector2f bonusPosition[NUMBER_BONUSES];
	Collision collision = NO_COLLISION;

	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		platePosition[i] = game.plate[i].body->getPosition();
	}
	for (int i = 0; i < NUMBER_BONUSES; ++i)
	{
		bonusPosition[i] = game.bonus[i].body->getPosition();
	}

	for (int i = 0; i < NUMBER_PLATES; ++i) // в отдельную функцию collisionPlate() засунь, выглядит ущербно 
	{
		if (((doodlePosition.y + 70 + 10 + 0.5 >= platePosition[i].y + 10 - 0.5) && (doodlePosition.y - 0.5 <= platePosition[i].y - 70 + 0.5)
			&& (doodlePosition.x + 40 >= platePosition[i].x) && (doodlePosition.x - 50 <= platePosition[i].x)))
		{
			collision = COLLISION_PLATE;
		}
	}

	for (int i = 0; i < NUMBER_BONUSES; ++i) // в отдельную функцию collisionBonus() засунь, выглядит ущербно 
	{
		if (((doodlePosition.y + 70 + 15 + 0.5 >= bonusPosition[i].y + 15 - 0.5) && (doodlePosition.y - 0.5 <= bonusPosition[i].y - 70 + 0.5)
			&& (doodlePosition.x + 47 >= bonusPosition[i].x) && (doodlePosition.x - 7 <= bonusPosition[i].x)))
		{
			collision = COLLISION_SPRING;
		}
	}

	switch (collision)
	{
		case COLLISION_PLATE:
			return 4500;
		case COLLISION_SPRING:
			return 9000;
		default:
			return 0;
	}
}

void generPlates(Game & game)
{
	sf::Vector2f doodlePosition = game.hero.body->getPosition();
	sf::Vector2f platePosition[NUMBER_PLATES];
	float x, y;

	srand(time(NULL));

	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		x = rand() % (550 - 50);
		y = -1 * rand() % (150);
		platePosition[i] = game.plate[i].body->getPosition();

		if (platePosition[i].y >= doodlePosition.y + 70 + 275)
		{
			game.plate[i].body->setPosition(x, doodlePosition.y + y - 380);
		}
	}
}

void initialPlates(Game & game)
{
	double x, y;
	srand(time(NULL));

	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		game.plate[i].body = new sf::RectangleShape(sf::Vector2f(50, 10));
		x = rand() % (550 - 50);
		y = rand() % (700 - 10) - 250;
		game.plate[i].body->setPosition(x, y);
		game.plate[i].body->setFillColor(sf::Color(184, 122, 88));
	}
}