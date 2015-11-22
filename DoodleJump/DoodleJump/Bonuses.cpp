void initialBonuses(Game & game);
void generBonuses(Game & game);

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
		if (game.plate[N].type == STATIC)
		{
			randomNum = rand() % 2;

			switch (randomNum)
			{
			case 0:
				x = rand() % (PLATE_WIDTH - SPRING_WIDTH);
				game.bonus[i].body = new sf::Sprite;
				game.bonus[i].type = SPRING;
				game.bonus[i].body->setPosition(platePosition[N].x + x, platePosition[N].y - SPRING_HEIGHT); 
				game.bonus[i].body->setTexture(SPRING_TEXTURE);
				break;
			case 1:
				x = rand() % (PLATE_WIDTH - 15); // 50 -- ширина плиты, 15 -- ширина батута
				game.bonus[i].body = new sf::Sprite;
				game.bonus[i].type = TRAMPLANE;
				game.bonus[i].body->setPosition(platePosition[N].x + x, platePosition[N].y - 7);
				//game.bonus[i].body->setFillColor(sf::Color(255, 0, 0));
				break;
			}
		}
		else
		{
			--i;
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
		bonusPosition[i] = game.bonus[i].body->getPosition();

		if (bonusPosition[i].y >= doodlePosition.y + DOODLE_HEIGHT + 275 + 10 + 2*PLATE_HEIGHT)                 // WHAT IS IT?! BUG!!!
		{
			for (int j = 0; j < NUMBER_PLATES; ++j)
			{
				platePosition = game.plate[j].body->getPosition();
				if ((platePosition.y <= doodlePosition.y - 275) && (game.plate[j].type == STATIC))
				{
					randomNum = rand() % 3;
					switch (randomNum)
					{
					case 0:
						x = rand() % (PLATE_WIDTH - SPRING_WIDTH);
						game.bonus[i].body = new sf::Sprite;
						game.bonus[i].type = SPRING;
						game.bonus[i].body->setPosition(platePosition.x + x, platePosition.y - SPRING_HEIGHT);
						game.bonus[i].body->setTexture(SPRING_TEXTURE);
						break;
					case 1:
						x = rand() % (PLATE_WIDTH - 15); // 15 -- ширина батута
						game.bonus[i].body = new sf::Sprite;
						game.bonus[i].type = TRAMPLANE;
						game.bonus[i].body->setPosition(platePosition.x + x, platePosition.y - 7);
						//game.bonus[i].body->setFillColor(sf::Color(255, 0, 0));
						break;
					case 2:
						randomNum = rand() % 2;
						x = rand() % (PLATE_WIDTH - SPRING_WIDTH);
						game.bonus[i].body = new sf::Sprite;
						game.bonus[i].type = HAT_HELICOPTER;
						game.bonus[i].body->setPosition(platePosition.x + x, platePosition.y - HAT_HELICOPTER_HEIGHT);
						switch (randomNum)
						{
							case 0:
								game.bonus[i].body->setTexture(HAT_HELOCPTER_NONE_LEFT_TEXTURE);
								break;
							case 1:
								game.bonus[i].body->setTexture(HAT_HELOCPTER_NONE_RIGHT_TEXTURE);
								break;
						}
						break;
					}
				}
			}
		}
	}
}
