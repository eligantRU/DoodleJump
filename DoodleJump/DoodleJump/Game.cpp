bool checkGameEnd(Game & game);
void starter(sf::RenderWindow & window, Game & game);
void initialGame(Game & game, sf::View view);
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
	

	Game game;
M_Start:
	view.reset(sf::FloatRect(0, 0, 550, 700));
	G_noJumps = true;
	G_endOfGame = false;
	initialGame(game, view);
	update(window, game, view);
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
				// конец игры, выкидываем на Menu
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
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					window.close();
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
			game.hero.lastDirectionX = LEFT;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			game.hero.direction.x = RIGHT;
			game.hero.lastDirectionX = RIGHT;
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

		if (platePosition[i].y >= doodlePosition.y + DOODLE_HEIGHT - PLATE_HEIGHT - game.hero.deltaHeight*STEP)
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

void initialGame(Game & game, sf::View view)
{
	initialHero(game, view);
	initialPlates(game);
	initialBonuses(game);
	game.actualBonus = NO;
}

void render(sf::RenderWindow & window, Game & game)
{
	window.clear(sf::Color(230, 230, 230));
	// FIX IT! Костыль!
	sf::Vector2f position = game.hero.body->getPosition();
	BACKGROUND->setPosition(0, position.y - 350);
	window.draw(*BACKGROUND);

	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		window.draw(*game.plate[i].body);
	}

	window.draw(*game.hero.body);

	for (int i = 0; i < NUMBER_BONUSES; ++i)
	{
		window.draw(*game.bonus[i].body);
	}

	window.display();
}

void update(sf::RenderWindow & window, Game & game, sf::View & view) // смену текстур в отдельную функцию...убожество!
{
	sf::Vector2f position(0.f, 0.f);
	sf::Vector2f doodlePosition = game.hero.body->getPosition();

	if (game.hero.direction.x == RIGHT)
	{
		position.x += STEP;
		if (position.y == DOWN)
		{
			game.hero.body->setTexture(DOODLE_RIGHT_TEXTURE);
		}
		else
		{
			game.hero.body->setTexture(DOODLE_JUMP_RIGHT_TEXTURE);
		}
	}
	else if (game.hero.direction.x == LEFT)
	{
		position.x -= STEP;
		if (position.y == DOWN)
		{
			game.hero.body->setTexture(DOODLE_LEFT_TEXTURE);
		}
		else
		{
			game.hero.body->setTexture(DOODLE_JUMP_LEFT_TEXTURE);
		}
	}
	if (game.hero.direction.y == DOWN)
	{
		if (game.hero.deltaHeight = checkDoodleFall(game))
		{
			game.hero.direction.y = UP;
		}
		else
		{
			position.y += STEP;
			if (game.hero.lastDirectionX == RIGHT)
			{
				game.hero.body->setTexture(DOODLE_RIGHT_TEXTURE);
			}
			else if (game.hero.lastDirectionX == LEFT)
			{
				game.hero.body->setTexture(DOODLE_LEFT_TEXTURE);
			}
		}
	}
	else if (game.hero.direction.y == UP)
	{
		if (game.hero.lastDirectionX == LEFT)
		{
			game.hero.body->setTexture(DOODLE_JUMP_LEFT_TEXTURE);
		}
		else if (game.hero.lastDirectionX == RIGHT)
		{
			game.hero.body->setTexture(DOODLE_JUMP_RIGHT_TEXTURE);
		}

		if (game.hero.deltaHeight > 0)
		{
			position.y -= STEP;
			--game.hero.deltaHeight;
		}
		else
		{
			game.hero.direction.y = DOWN;
			if (game.hero.body->getPosition().y < positionBeforeDown.y)
			{
				positionBeforeDown = game.hero.body->getPosition();
			}
		}
	}

	int k = 1;
	switch (game.actualBonus)
	{
		case NO:
			k = 1;
			break;
		case SPRING:
			k = 2;
			break;
		case TRAMPLANE:
			k = 2;
			break;
		case HAT_HELICOPTER:
			k = 2;
			break;
	}
	game.hero.body->move(position * (k * TIME_PER_FRAME.asSeconds()));

	// В отдельную функцию + стоит добавить плавности? // В оригинале дудла так же резко
	if (doodlePosition.x <= -1 * DOODLE_WIDTH)
	{
		game.hero.body->setPosition(550 - DOODLE_WIDTH, doodlePosition.y);
	}
	if (doodlePosition.x >= 550)
	{
		game.hero.body->setPosition(0, doodlePosition.y);
	}
	//

	if (game.actualBonus == HAT_HELICOPTER) 
	{
		if (game.hero.deltaHeight == 0)
		{
			game.actualBonus = NO;
			game.qwerty = 0;
		}
		if ((game.qwerty >= 0) && (game.qwerty <= 100))
		{
			game.bonus[game.actualBonusId].body->setTexture(HAT_HELOCPTER_FLY_LEFT_TEXTURE);
			++game.qwerty;
		}
		else if((game.qwerty >= 101) && (game.qwerty <= 200))
		{
			game.bonus[game.actualBonusId].body->setTexture(HAT_HELOCPTER_DIAGONAL_LEFT_TEXTURE);
			++game.qwerty;
		}
		else if ((game.qwerty >= 201) && (game.qwerty <= 300))
		{
			game.bonus[game.actualBonusId].body->setTexture(HAT_HELOCPTER_DIAGONAL_RIGHT_TEXTURE);
			++game.qwerty;
		}
		else if ((game.qwerty >= 301) && (game.qwerty <= 400))
		{
			game.bonus[game.actualBonusId].body->setTexture(HAT_HELOCPTER_FLY_RIGHT_TEXTURE);
			game.qwerty = 0;
		}

		if (game.hero.lastDirectionX == RIGHT)
		{
			game.bonus[game.actualBonusId].body->setPosition(game.hero.body->getPosition().x, game.hero.body->getPosition().y - 13);
		}
		else if (game.hero.lastDirectionX == LEFT)
		{
			game.bonus[game.actualBonusId].body->setPosition(game.hero.body->getPosition().x + 15, game.hero.body->getPosition().y - 13);
		}
	}

	if ((game.hero.direction.y == UP) && (doodlePosition.y <= positionBeforeDown.y))
	{
		view.setCenter(275, doodlePosition.y);
	}

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
		if (((doodlePosition.y + DOODLE_HEIGHT + PLATE_HEIGHT + 0.5 >= platePosition[i].y + PLATE_HEIGHT - 0.5) && (doodlePosition.y - 0.5 <= platePosition[i].y - DOODLE_HEIGHT + 0.5)
			&& (doodlePosition.x + DOODLE_WIDTH >= platePosition[i].x) && (doodlePosition.x - PLATE_WIDTH <= platePosition[i].x)))
		{
			if (game.plate[i].type == CLOUD)
			{
				// здесь и должна была бы появиться функция генерации одной новой плиты, которая бала бы частью генерации двух и более плит
				// костылёк
				game.plate[i].body->setPosition(platePosition[i].x, platePosition[i].y + 550);
			}
			collision = COLLISION_PLATE;
			break;
		}
	}

	for (int i = 0; i < NUMBER_BONUSES; ++i) // в отдельную функцию collisionBonus() засунь, выглядит ущербно 
	{
		switch (game.bonus[i].type)
		{
		case SPRING:
			if (((doodlePosition.y + DOODLE_HEIGHT + SPRING_HEIGHT + 0.5 >= bonusPosition[i].y + SPRING_HEIGHT - 0.5) && (doodlePosition.y - 0.5 <= bonusPosition[i].y - DOODLE_HEIGHT + 0.5)
				&& (doodlePosition.x + DOODLE_WIDTH + SPRING_WIDTH >= bonusPosition[i].x) && (doodlePosition.x - SPRING_WIDTH <= bonusPosition[i].x)))
			{
				collision = COLLISION_SPRING;
				game.bonus[i].body->setTexture(SPRING_2_TEXTURE);
				game.actualBonusId = i;
			}
			break;
		case TRAMPLANE:
			if (((doodlePosition.y + DOODLE_HEIGHT + 7 + 0.5 >= bonusPosition[i].y + 7 - 0.5) && (doodlePosition.y - 0.5 <= bonusPosition[i].y - DOODLE_HEIGHT + 0.5)
				&& (doodlePosition.x + DOODLE_WIDTH + 15 >= bonusPosition[i].x) && (doodlePosition.x - 15 <= bonusPosition[i].x)))
			{
				collision = COLLISION_TRAMPLANE;
				game.actualBonusId = i;
			}
			break;
		case HAT_HELICOPTER:
			if (((doodlePosition.y + DOODLE_HEIGHT + HAT_HELICOPTER_HEIGHT + 0.5 >= bonusPosition[i].y + HAT_HELICOPTER_HEIGHT - 0.5) && (doodlePosition.y - 0.5 <= bonusPosition[i].y - DOODLE_HEIGHT + 0.5)
				&& (doodlePosition.x + DOODLE_WIDTH + HAT_HELICOPTER_WIDTH >= bonusPosition[i].x) && (doodlePosition.x - HAT_HELICOPTER_WIDTH <= bonusPosition[i].x)))
			{
				collision = COLLISION_HAT_HELICOPTER;
				game.actualBonusId = i;

				if (game.hero.direction.x == RIGHT)
				{
					game.bonus[i].body->setPosition(doodlePosition.x + 15, doodlePosition.y - 15);
				}
				else if ((game.hero.direction.x == LEFT) || (game.hero.direction.x == NONE))
				{
					game.bonus[i].body->setPosition(doodlePosition.x+15, doodlePosition.y-15);
				}
			}
		}
	}

	switch (collision)
	{
	case COLLISION_PLATE:
		game.actualBonus = NO;
		return 5500;
	case COLLISION_SPRING:
		game.actualBonus = SPRING;
		return 4500;
	case COLLISION_TRAMPLANE:
		game.actualBonus = TRAMPLANE;
		return 6000;
	case COLLISION_HAT_HELICOPTER:
		game.actualBonus = HAT_HELICOPTER;
		return 12000;
	default:
	//	game.actualBonus = NO;
		return 0;
	}
}
