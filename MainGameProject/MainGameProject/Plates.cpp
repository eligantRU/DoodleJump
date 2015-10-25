int checkDoodleFall(Game & game);
void generPlates(Game & game);
void initialPlates(Game & game);

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