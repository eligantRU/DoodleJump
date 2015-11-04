int checkDoodleFall(Game & game);
void generPlates(Game & game);
void initialPlates(Game & game);
void moveDynamicPlates(Game & game);

void generPlates(Game & game)
{
	sf::Vector2f doodlePosition = game.hero.body->getPosition();
	sf::Vector2f platePosition[NUMBER_PLATES];
	float x, y;
	int randomNum;
	srand(time(NULL));

	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		platePosition[i] = game.plate[i].body->getPosition();
		x = rand() % (550 - 50);
		y = -1 * rand() % (150);

		if (platePosition[i].y >= doodlePosition.y + 70 + 275)
		{
			randomNum = rand() % 2;
			switch (randomNum)
			{
				case 0:
					game.plate[i].type = STATIC;
					game.plate[i].direction.x = NONE;
					game.plate[i].body->setFillColor(sf::Color(184, 122, 88));
					break;
				case 1:
					game.plate[i].type = DYNAMIC_X;
					randomNum = rand() % 2;
					switch (randomNum)
					{
						case 0:
							game.plate[i].direction.x = LEFT;
							break;
						case 1:
							game.plate[i].direction.x = RIGHT;
							break;
					}
					game.plate[i].body->setFillColor(sf::Color(00, 7*16+15, 255));
					break;
			}
			game.plate[i].body->setPosition(x, doodlePosition.y + y - 380);
		}
	}
}

void initialPlates(Game & game) // эту функцию можно убрать, либо в неё засунуть generPlates() + в конце менять начальные координаты + создавать прямоугольник
{
	double x, y;
	srand(time(NULL));
	int randomNum;
	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		game.plate[i].body = new sf::RectangleShape(sf::Vector2f(50, 10));
		randomNum = rand() % 2;
		switch (randomNum)
		{
			case 0:
				game.plate[i].type = STATIC;
				game.plate[i].direction.x = NONE;
				game.plate[i].body->setFillColor(sf::Color(184, 122, 88));
				break;
			case 1:
				game.plate[i].type = DYNAMIC_X;
				randomNum = rand() % 2;
				switch (randomNum)
				{
					case 0:
						game.plate[i].direction.x = LEFT;
						break;
					case 1:
						game.plate[i].direction.x = RIGHT;
						break;
				}
				game.plate[i].body->setFillColor(sf::Color(00, 7*16+15, 255));
				break;
		}
		x = rand() % (550 - 50);
		y = rand() % (700 - 10) - 250;
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
		if (game.plate[i].type = DYNAMIC_X) // лишнее условие, но так нагляднее
		{
			switch (game.plate[i].direction.x)
			{
			case LEFT:
				if (platePosition[i].x <= STEP)
				{
					game.plate[i].direction.x = RIGHT;
				}
				else
				{
					position.x -= 0.5*STEP;
				}
				break;
			case RIGHT:
				if (platePosition[i].x >= 550-50-STEP) // ширина экрана - ширина плиты
				{
					game.plate[i].direction.x = LEFT;
				}
				else
				{
					position.x += 0.5*STEP;
				}
				break;
			default:
				break;
			}
			game.plate[i].body->move(position * TIME_PER_FRAME.asSeconds());
			position.x = 0;
			position.y = 0;
		}
	}
}
