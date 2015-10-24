bool checkDoodleFall(Game & game);
void generPlates(Game & game);
void initialPlates(Game & game);

bool checkDoodleFall(Game & game)
{
	sf::Vector2f doodlePosition = game.hero.body->getPosition();
	sf::Vector2f platePosition[NUMBER_PLATES];

	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		platePosition[i] = game.plate[i].body->getPosition();
	}

	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		if (((doodlePosition.y + 70 + 10 + 0.5 >= platePosition[i].y + 10 - 0.5) && (doodlePosition.y - 0.5 <= platePosition[i].y - 70 + 0.5)
			&& (doodlePosition.x + 40 >= platePosition[i].x) && (doodlePosition.x - 50 <= platePosition[i].x)))
		{
			return true;
		}
	}
	return false;
}

void generPlates(Game & game)
{
	sf::Vector2f doodlePosition = game.hero.body->getPosition();
	sf::Vector2f platePosition[NUMBER_PLATES];

	srand(time(NULL));
	float x, y;

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
	srand(time(NULL));

	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		game.plate[i].body = new sf::RectangleShape(sf::Vector2f(50, 10));
		double x, y;
		x = rand() % (550 - 50);
		y = rand() % (700 - 10) - 250;
		game.plate[i].body->setPosition(x, y);
		game.plate[i].body->setFillColor(sf::Color(184, 122, 88));
	}
}