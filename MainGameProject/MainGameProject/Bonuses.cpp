// Код ниже ацтой, рисует только "пружинки"

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
	int randomNum;

	for (int i = 0; i < NUMBER_BONUSES; ++i)
	{
		N = rand() % NUMBER_PLATES;
		randomNum = rand() % 2;

		switch(randomNum)
		{
			case 0:
				x = rand() % (50 - 7); // 50 -- ширина плиты, 7 -- ширина пружины
				game.bonus[i].body = new sf::RectangleShape(sf::Vector2f(7, 15));
				game.bonus[i].type = SPRING;
				game.bonus[i].body->setPosition(platePosition[N].x + x, platePosition[N].y - 15); // 15 -- высота пружины
				game.bonus[i].body->setFillColor(sf::Color(64, 64, 64));
				break;
			case 1:
				x = rand() % (50 - 15); // 50 -- ширина плиты, 15 -- ширина батута
				game.bonus[i].body = new sf::RectangleShape(sf::Vector2f(15, 7));
				game.bonus[i].type = TRAMPLANE;
				game.bonus[i].body->setPosition(platePosition[N].x + x, platePosition[N].y - 7);
				game.bonus[i].body->setFillColor(sf::Color(255, 0, 0));
				break;
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

	srand(time(NULL));
	
	for (int i = 0; i < NUMBER_BONUSES; ++i)
	{
		//x = rand() % (50 - 10); // 50 -- ширина плиты, 7 -- ширина пружины

		bonusPosition[i] = game.bonus[i].body->getPosition();
		
		if (bonusPosition[i].y >= doodlePosition.y + 70 + 275 - 15)
		{
			for (int j = 0; j < NUMBER_PLATES; ++j)
			{
				platePosition = game.plate[j].body->getPosition();
				if (platePosition.y <= doodlePosition.y - 275)
				{
					randomNum = rand() % 2;
					switch (randomNum)
					{
						case 0:
							x = rand() % (50 - 7); // 50 -- ширина плиты, 7 -- ширина пружины
							game.bonus[i].body = new sf::RectangleShape(sf::Vector2f(7, 15));
							game.bonus[i].type = SPRING;
							game.bonus[i].body->setPosition(platePosition.x + x, platePosition.y - 15); // 15 -- высота пружины
							game.bonus[i].body->setFillColor(sf::Color(64, 64, 64));
							break;
						case 1:
							x = rand() % (50 - 15); // 50 -- ширина плиты, 15 -- ширина батута
							game.bonus[i].body = new sf::RectangleShape(sf::Vector2f(15, 7));
							game.bonus[i].type = TRAMPLANE;
							game.bonus[i].body->setPosition(platePosition.x + x, platePosition.y - 7);
							game.bonus[i].body->setFillColor(sf::Color(255, 0, 0));
							break;
					}
					break;
				}
			}
		}
	}
}