bool checkGameEnd(Game & game);
void starter(sf::RenderWindow & window, Game & game);
void initialGame(Game & game);
void startGame(void);
void keyPressed(sf::RenderWindow & window, Game & game);
void update(sf::RenderWindow & window, Game & game, sf::View & view);
void render(sf::RenderWindow & window, Game & game);

void startGame(void)
{
	sf::RenderWindow window(sf::VideoMode(550, 700), "Doodle Jump");

	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	sf::View view;
	view.reset(sf::FloatRect(0, 0, 550, 700));

	Game game; 
M_Start:
	G_noJumps = true;
	G_endOfGame = false;
	initialGame(game);

	sf::Clock clock;
	float timeSinceLastUpdate = clock.getElapsedTime().asSeconds();
	int Marker = 60;
	while (window.isOpen())
	{
		keyPressed(window, game);
		timeSinceLastUpdate += clock.getElapsedTime().asSeconds();
		while ((timeSinceLastUpdate > TIME_PER_FRAME.asSeconds()) && (Marker != 0))
		{
			timeSinceLastUpdate -= TIME_PER_FRAME.asSeconds();
			--Marker;

			starter(window, game);
			if (G_endOfGame == false)
			{
				window.setView(view);
				update(window, game, view);
			}
			else
			{
				game.hero.body->setFillColor(sf::Color(255, 0, 0));
			}
		}
		Marker = 60;
		window.setView(view);
		render(window, game);
		if (G_endOfGame == true)
		{
			while (true)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
				{
					goto M_Start;
				}
			}
		}
	}
}

void keyPressed(sf::RenderWindow & window, Game & game)
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			game.hero.direction.x = LEFT;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			game.hero.direction.x = RIGHT;
		}
		else
		{
			game.hero.direction.x = NONE;
		}

		if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
		{
			window.close();
		}
	}
}

bool checkGameEnd(Game & game)
{
	sf::Vector2f doodlePosition = game.hero.body->getPosition();
	sf::Vector2f platePosition[NUMBER_PLATES];

	int flag = 0;

	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		platePosition[i] = game.plate[i].body->getPosition();

		if(platePosition[i].y >= doodlePosition.y + 70 - 10 - game.hero.deltaHeight*STEP)
		{
			flag = 0;
		}
		else
		{
			++flag;
		}
	}

	if (flag == NUMBER_PLATES)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void starter(sf::RenderWindow & window, Game & game)
{
	if (G_noJumps == true)
	{
		while (G_noJumps)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				game.hero.direction.y = DOWN;
				G_noJumps = false;
			}
		}
	}
}

void initialGame(Game & game)
{
	initialHero(game);
	initialPlates(game);
	initialBonuses(game);
}

void render(sf::RenderWindow & window, Game & game)
{
	window.clear(sf::Color(255, 255, 255));

	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		window.draw(*game.plate[i].body);
	}

	for (int i = 0; i < NUMBER_BONUSES; ++i)
	{
		window.draw(*game.bonus[i].body);
	}

	window.draw(*game.hero.body);
	window.display();
}

void update(sf::RenderWindow & window, Game & game, sf::View & view)
{
	sf::Vector2f position(0.f, 0.f);
	sf::Vector2f doodlePosition = game.hero.body->getPosition();

	if (game.hero.direction.x == RIGHT)
	{
		position.x += STEP;
	}
	if (game.hero.direction.x == LEFT)
	{
		position.x -= STEP;
	}
	if (game.hero.direction.y == DOWN)
	{
		if (checkDoodleFall(game))
		{
			game.hero.direction.y = UP;
		}
		else
		{
			position.y += STEP;
		}
	}
	else if (game.hero.direction.y == UP)
	{
		if (game.hero.deltaHeight > 0)
		{
			position.y -= STEP;
			--game.hero.deltaHeight;
		}
		else
		{
			game.hero.direction.y = DOWN;
			game.hero.deltaHeight = checkDoodleFall(game);
		}
	}
	game.hero.body->move(position * TIME_PER_FRAME.asSeconds());

	view.setCenter(275, doodlePosition.y);
	
	moveDynamicPlates(game);
	generPlates(game);
	generBonuses(game);

	if (checkGameEnd(game))
	{
		G_endOfGame = true;
	}
}



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
		switch (game.bonus[i].type)
		{
			case SPRING:
				if (((doodlePosition.y + 70 + 15 + 0.5 >= bonusPosition[i].y + 15 - 0.5) && (doodlePosition.y - 0.5 <= bonusPosition[i].y - 70 + 0.5)
					&& (doodlePosition.x + 47 >= bonusPosition[i].x) && (doodlePosition.x - 7 <= bonusPosition[i].x)))
				{
					collision = COLLISION_SPRING;
				}
			case TRAMPLANE:
				if (((doodlePosition.y + 70 + 7 + 0.5 >= bonusPosition[i].y + 7 - 0.5) && (doodlePosition.y - 0.5 <= bonusPosition[i].y - 70 + 0.5)
					&& (doodlePosition.x + 55 >= bonusPosition[i].x) && (doodlePosition.x - 15 <= bonusPosition[i].x)))
				{
					collision = COLLISION_TRAMPLANE;
				}
		}
	}

	switch (collision)
	{
		case COLLISION_PLATE:
			return 4500;
		case COLLISION_SPRING:
			return 9000;
		case COLLISION_TRAMPLANE:
			return 18000;
		default:
			return 0;
	}
}
