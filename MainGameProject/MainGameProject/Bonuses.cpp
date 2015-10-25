//  од ниже ацтой, рисует только "пружинки"

void initialBonuses(Game & game);
void generBonuses(Game & game);
bool collisionSpring(Game & game);

void initialBonuses(Game & game)
{
	srand(time(NULL));
	sf::Vector2f platePosition[NUMBER_PLATES];

	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		platePosition[i] = game.plate[i].body->getPosition();
	}

	double x;
	int N;

	for (int i = 0; i < NUMBER_BONUSES; ++i)
	{
		game.bonus[i].body = new sf::RectangleShape(sf::Vector2f(7, 15));

		N = rand() % NUMBER_PLATES;
		x = rand() % (50-7); // 50 -- ширина плиты, 7 -- ширина пружины

		game.bonus[i].body->setPosition(platePosition[N].x+x, platePosition[N].y-15); // 15 -- высота пружины
		game.bonus[i].body->setFillColor(sf::Color(64, 64, 64));
		game.bonus[i].type = SPRING;
	}
}

void generBonuses(Game & game)
{
	sf::Vector2f doodlePosition = game.hero.body->getPosition();
	sf::Vector2f bonusPosition[NUMBER_BONUSES];
	sf::Vector2f platePosition;
	float x;

	srand(time(NULL));
	
	for (int i = 0; i < NUMBER_BONUSES; ++i)
	{
		x = rand() % (50 - 10); // 50 -- ширина плиты, 7 -- ширина пружины

		bonusPosition[i] = game.bonus[i].body->getPosition();
		
		if (bonusPosition[i].y >= doodlePosition.y + 70 + 275 - 15)
		{
			for (int j = 0; j < NUMBER_PLATES; ++j)
			{
				platePosition = game.plate[j].body->getPosition();
				if (platePosition.y <= doodlePosition.y - 275)
				{
					game.bonus[i].body->setPosition(platePosition.x+x, platePosition.y-15);
					break;
				}
			}
		}
	}
}

bool collisionSpring(Game & game)
{

}