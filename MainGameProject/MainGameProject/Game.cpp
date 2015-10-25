bool checkGameEnd(Game & game);
void starter(sf::RenderWindow & window, Game & game);
void initialGame(Game & game);
void startGame(void);
void keyPressed(sf::RenderWindow & window, Game & game);
void update(sf::RenderWindow & window, Game & game, sf::View & view);
void render(sf::RenderWindow & window, Game & game);
bool checkDoodleFall(Game & game);

void startGame(void)
{
	sf::RenderWindow window(sf::VideoMode(550, 700), "Doodle Jump");

	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	sf::View view;
	view.reset(sf::FloatRect(0, 0, 550, 700));

	Game game;
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
			if (endOfGame == false)
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

		if (platePosition[i].y >= doodlePosition.y + 70 - 10)
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
	if (noJumps == true)
	{
		while (noJumps)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				game.hero.direction.y = DOWN;
				noJumps = false;
			}
		}
	}
}

void initialGame(Game & game)
{
	initialHero(game);
	initialPlates(game);
}

void render(sf::RenderWindow & window, Game & game)
{
	window.clear(sf::Color(255, 255, 255));

	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		window.draw(*game.plate[i].body);
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
		if (upping > 0)
		{
			position.y -= STEP;
			--upping;
		}
		else
		{
			game.hero.direction.y = DOWN;
			upping = JUMP_HEIGHT;
		}
	}
	game.hero.body->move(position * TIME_PER_FRAME.asSeconds());

	view.setCenter(275, doodlePosition.y);
	generPlates(game);

	if (checkGameEnd(game))
	{
		endOfGame = true;
	}
}