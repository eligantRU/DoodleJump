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
		x = rand() % (550 - PLATE_WIDTH);
		y = -1 * rand() % (150);               // —юда запилить функцию дл€ равномерной генерации плит по высоте

		if (platePosition[i].y >= doodlePosition.y + DOODLE_HEIGHT + 275)
		{
			randomNum = rand() % 3;
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
				game.plate[i].body->setFillColor(sf::Color(00, 7 * 16 + 15, 255));
				break;
			case 2:
				game.plate[i].type = CLOUD;
				game.plate[i].direction.x = NONE;
				game.plate[i].body->setFillColor(sf::Color(13 * 16, 160, 13 * 16));
				break;
			}
			game.plate[i].body->setPosition(x, doodlePosition.y + y - 380);
		}
	}
}

void initialPlates(Game & game) // эту функцию можно убрать, либо в неЄ засунуть generPlates() + в конце мен€ть начальные координаты + создавать пр€моугольник
{
	double x, y;
	srand(time(NULL));
	int randomNum;
	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		game.plate[i].body = new sf::RectangleShape(sf::Vector2f(PLATE_WIDTH, PLATE_HEIGHT));
		randomNum = rand() % 3;
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
			game.plate[i].body->setFillColor(sf::Color(00, 7 * 16 + 15, 255));
			break;
		case 2:
			game.plate[i].type = CLOUD;
			game.plate[i].direction.x = NONE;
			game.plate[i].body->setFillColor(sf::Color(13 * 16, 160, 13 * 16));
			break;
		}
		x = rand() % (550 - PLATE_WIDTH);
		y = rand() % (700 - PLATE_HEIGHT) - 250;                // —юда запилить функцию дл€ равномерной генерации плит по высоте
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
		if (game.plate[i].type == DYNAMIC_X) // лишнее условие, но так нагл€днее
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
				if (platePosition[i].x >= 550 - PLATE_WIDTH - STEP) // ширина экрана - ширина плиты
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
