#include "stdafx.h"
#include "bases.h"

extern Assets g_Assets;
extern sf::Vector2f g_positionBeforeDown;
extern bool g_noJumps;
extern bool g_endOfGame;

void startGame(void)
{
	srand(time(NULL));
	initAssets();
	sf::RenderWindow window(sf::VideoMode(550, 700), "Doodle Jump");

	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	sf::View view;
	
	Game game;
	game.points = 0;
M_Start:
	view.reset(sf::FloatRect(0, 0, 550, 700));
	g_noJumps = true;
	g_endOfGame = false;
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
			if (g_endOfGame == false)
			{
				window.setView(view);
				update(window, game, view);
			}
			else
			{
				// Menu();
			}
		}
		Marker = 60;
		window.setView(view);
		render(window, game);
		if (g_endOfGame == true)
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
			game.hero.direction.x = DirectionX::LEFT;
			game.hero.lastDirectionX = DirectionX::LEFT;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			game.hero.direction.x = DirectionX::RIGHT;
			game.hero.lastDirectionX = DirectionX::RIGHT;
		}
		else
		{
			game.hero.direction.x = DirectionX::NONE;
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
	if (g_noJumps == true)
	{
		while (g_noJumps)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				game.hero.direction.y = DirectionY::DOWN;
				g_noJumps = false;
			}
		}
	}
}

void initialGame(Game & game, sf::View view)
{
	initialHero(game, view);
	initialPlates(game);
	initialBonuses(game);
	game.actualBonus = BonusType::NO;
}

void render(sf::RenderWindow & window, Game & game)
{
	window.clear(sf::Color(230, 230, 230));
	window.draw(*g_Assets.BACKGROUND);

	for (int i = 0; i < NUMBER_PLATES; ++i)
	{
		window.draw(*game.plate[i].body);
	}

	window.draw(*game.hero.body);

	for (int i = 0; i < NUMBER_BONUSES; ++i)
	{
		window.draw(*game.bonus[i].body);
	}

	game.text.setFont(g_Assets.font);
	game.text.setCharacterSize(20);
	std::string str = "Bonuses: " + std::to_string(game.points);
	game.text.setString(str);
	game.text.setStyle(sf::Text::Bold);
	game.text.move(0.f, 0.f);
	game.text.setColor(sf::Color(0, 0, 0));
	window.draw(game.text);

	window.display();
}

void update(sf::RenderWindow & window, Game & game, sf::View & view) // смену текстур в отдельную функцию...убожество!
{
	sf::Vector2f position(0.f, 0.f);
	sf::Vector2f doodlePosition = game.hero.body->getPosition();
	sf::Vector2f textPosition = game.text.getPosition();

	if (game.hero.direction.x == DirectionX::RIGHT)
	{
		position.x += STEP;
		if (false) //(position.y == DOWN) WHAT THE HELL?!
		{
			game.hero.body->setTexture(g_Assets.DOODLE_RIGHT_TEXTURE);
		}
		else
		{
			game.hero.body->setTexture(g_Assets.DOODLE_JUMP_RIGHT_TEXTURE);
		}
	}
	else if (game.hero.direction.x == DirectionX::LEFT)
	{
		position.x -= STEP;
		if (false) //(position.y == DOWN) WHAT THE HELL?!
		{
			game.hero.body->setTexture(g_Assets.DOODLE_LEFT_TEXTURE);
		}
		else
		{
			game.hero.body->setTexture(g_Assets.DOODLE_JUMP_LEFT_TEXTURE);
		}
	}
	if (game.hero.direction.y == DirectionY::DOWN)
	{
		if (game.hero.deltaHeight = checkDoodleFall(game))
		{
			game.hero.direction.y = DirectionY::UP;
		}
		else
		{
			position.y += STEP;
			if (game.hero.lastDirectionX == DirectionX::RIGHT)
			{
				game.hero.body->setTexture(g_Assets.DOODLE_RIGHT_TEXTURE);
			}
			else if (game.hero.lastDirectionX == DirectionX::LEFT)
			{
				game.hero.body->setTexture(g_Assets.DOODLE_LEFT_TEXTURE);
			}
		}
	}
	else if (game.hero.direction.y == DirectionY::UP)
	{
		if (game.hero.lastDirectionX == DirectionX::LEFT)
		{
			game.hero.body->setTexture(g_Assets.DOODLE_JUMP_LEFT_TEXTURE);
		}
		else if (game.hero.lastDirectionX == DirectionX::RIGHT)
		{
			game.hero.body->setTexture(g_Assets.DOODLE_JUMP_RIGHT_TEXTURE);
		}

		if (game.hero.deltaHeight > 0)
		{
			position.y -= STEP;
			--game.hero.deltaHeight;
		}
		else
		{
			game.hero.direction.y = DirectionY::DOWN;
			if (game.hero.body->getPosition().y < g_positionBeforeDown.y)
			{
				g_positionBeforeDown = game.hero.body->getPosition();
			}
		}
	}

	// в отдельную функцию
	int k = 1;
	switch (game.actualBonus)
	{
	case BonusType::NO:
		k = 1;
		break;
	case  BonusType::SPRING:
		k = 2;
		break;
	case  BonusType::TRAMPOLINE:
		k = 2;
		break;
	case  BonusType::HAT_HELICOPTER:
		k = 2;
		break;
	case  BonusType::ROCKET:
		k = 3;
		break;
	}
	game.hero.body->move(position * (k * TIME_PER_FRAME.asSeconds()));
	//

	// В отдельную функцию
	if (doodlePosition.x <= -1 * DOODLE_WIDTH)
	{
		game.hero.body->setPosition(550 - DOODLE_WIDTH, doodlePosition.y);
	}
	if (doodlePosition.x >= 550)
	{
		game.hero.body->setPosition(0, doodlePosition.y);
	}
	//

	if (game.actualBonus == BonusType::HAT_HELICOPTER) // и это тоже в отдельную функцию
	{
		if (game.hero.deltaHeight <= 1000)
		{
			game.qwerty = -1;
			game.bonus[game.actualBonusId].body->setTexture(g_Assets.HAT_HELOCPTER_FLY_LEFT_TEXTURE);
			game.bonus[game.actualBonusId].body->rotate(-0.07f);
			game.bonus[game.actualBonusId].body->move(sf::Vector2f(-2*STEP, 6*STEP) * TIME_PER_FRAME.asSeconds());
		}
		if (game.hero.deltaHeight == 0)
		{
			game.qwerty = 0;
			game.actualBonus = BonusType::NO;
		}

		if ((game.qwerty >= 0) && (game.qwerty <= 200))
		{
			game.bonus[game.actualBonusId].body->setTexture(g_Assets.HAT_HELOCPTER_FLY_LEFT_TEXTURE);
			++game.qwerty;
		}
		else if((game.qwerty >= 201) && (game.qwerty <= 400))
		{
			game.bonus[game.actualBonusId].body->setTexture(g_Assets.HAT_HELOCPTER_DIAGONAL_LEFT_TEXTURE);
			++game.qwerty;
		}
		else if ((game.qwerty >= 401) && (game.qwerty <= 600))
		{
			game.bonus[game.actualBonusId].body->setTexture(g_Assets.HAT_HELOCPTER_DIAGONAL_RIGHT_TEXTURE);
			++game.qwerty;
		}
		else if ((game.qwerty >= 601) && (game.qwerty <= 800))
		{
			game.bonus[game.actualBonusId].body->setTexture(g_Assets.HAT_HELOCPTER_FLY_RIGHT_TEXTURE);
			++game.qwerty;
		}
		else if (game.qwerty == 801)
		{
			game.qwerty = 0;
		}

		if ((game.qwerty >= 0) && (game.qwerty <= 800) && (game.actualBonus != BonusType::NO))
		{
			if (game.hero.lastDirectionX == DirectionX::RIGHT)
			{
				game.bonus[game.actualBonusId].body->setPosition(game.hero.body->getPosition().x, game.hero.body->getPosition().y - 13);
			}
			else if (game.hero.lastDirectionX == DirectionX::LEFT)
			{
				game.bonus[game.actualBonusId].body->setPosition(game.hero.body->getPosition().x + 15, game.hero.body->getPosition().y - 13);
			}
		}
	}
	
	if (game.actualBonus == BonusType::ROCKET) // в отдельную функцию
	{
		if (game.hero.deltaHeight <= 1000)
		{
			game.qwerty = -1;
			game.bonus[game.actualBonusId].body->setTexture(g_Assets.ROCKET_NONE_TEXTURE);
			game.bonus[game.actualBonusId].body->rotate(-0.07f);
			game.bonus[game.actualBonusId].body->move(sf::Vector2f(-2 * STEP, 6 * STEP) * TIME_PER_FRAME.asSeconds());
		}
		if (game.hero.deltaHeight == 0)
		{
			game.qwerty = 0;
			game.actualBonus = BonusType::NO;
		}

		if ((game.qwerty >= 0) && (game.qwerty <= 200))
		{
			if (game.hero.lastDirectionX == DirectionX::RIGHT)
			{
				game.bonus[game.actualBonusId].body->setTexture(g_Assets.ROCKET_1_LEFT_TEXTURE);
			} 
			else if (game.hero.lastDirectionX == DirectionX::LEFT)
			{
				game.bonus[game.actualBonusId].body->setTexture(g_Assets.ROCKET_1_RIGHT_TEXTURE);
			}
			++game.qwerty;
		}
		if ((game.qwerty >= 201) && (game.qwerty <= 400))
		{
			if (game.hero.lastDirectionX == DirectionX::RIGHT)
			{
				game.bonus[game.actualBonusId].body->setTexture(g_Assets.ROCKET_2_LEFT_TEXTURE);
			}
			else if (game.hero.lastDirectionX == DirectionX::LEFT)
			{
				game.bonus[game.actualBonusId].body->setTexture(g_Assets.ROCKET_2_RIGHT_TEXTURE);
			}
			++game.qwerty;
		}
		if ((game.qwerty >= 401) && (game.qwerty <= 600))
		{
			if (game.hero.lastDirectionX == DirectionX::RIGHT)
			{
				game.bonus[game.actualBonusId].body->setTexture(g_Assets.ROCKET_3_LEFT_TEXTURE);
			}
			else if (game.hero.lastDirectionX == DirectionX::LEFT)
			{
				game.bonus[game.actualBonusId].body->setTexture(g_Assets.ROCKET_3_RIGHT_TEXTURE);
			}
			++game.qwerty;
		}
		if (game.qwerty == 601)
		{
			game.qwerty = 0;
		}

		if ((game.qwerty >= 0) && (game.qwerty <= 600) && (game.actualBonus != BonusType::NO))
		{
			if (game.hero.lastDirectionX == DirectionX::RIGHT)
			{
				game.bonus[game.actualBonusId].body->setPosition(game.hero.body->getPosition().x - ROCKET_WIDTH, game.hero.body->getPosition().y);
			}
			else if (game.hero.lastDirectionX == DirectionX::LEFT)
			{
				game.bonus[game.actualBonusId].body->setPosition(game.hero.body->getPosition().x + DOODLE_WIDTH, game.hero.body->getPosition().y);
			}
		}
	} //

	if ((game.hero.direction.y == DirectionY::UP) && (doodlePosition.y <= g_positionBeforeDown.y))
	{
		view.setCenter(275, doodlePosition.y);
		g_Assets.BACKGROUND->setPosition(0, doodlePosition.y-350);
		game.text.setPosition(0, doodlePosition.y-350);
		++game.points;
	}
	
	moveDynamicPlates(game);
	generPlates(game);
	generBonuses(game);

	if (checkGameEnd(game))
	{
		g_endOfGame = true;
	}
}

int checkDoodleFall(Game & game)
{
	sf::Vector2f doodlePosition = game.hero.body->getPosition();
	sf::Vector2f platePosition[NUMBER_PLATES];
	sf::Vector2f bonusPosition[NUMBER_BONUSES];
	Collision collision = Collision::NO_COLLISION;

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
			if (game.plate[i].type == PlateType::CLOUD)
			{
				// здесь и должна была бы появиться функция генерации одной новой плиты, которая бала бы частью генерации двух и более плит
				// костылёк
				game.plate[i].body->setPosition(platePosition[i].x, platePosition[i].y + 550);
			}
			collision = Collision::COLLISION_PLATE;
			break;
		}
	}

	for (int i = 0; i < NUMBER_BONUSES; ++i) // в отдельную функцию collisionBonus() засунь, выглядит ущербно 
	{
		switch (game.bonus[i].type)
		{
		case BonusType::SPRING:
			if (((doodlePosition.y + DOODLE_HEIGHT + SPRING_HEIGHT + 0.5 >= bonusPosition[i].y + SPRING_HEIGHT - 0.5) && (doodlePosition.y - 0.5 <= bonusPosition[i].y - DOODLE_HEIGHT + 0.5)
				&& (doodlePosition.x + DOODLE_WIDTH + SPRING_WIDTH >= bonusPosition[i].x) && (doodlePosition.x - SPRING_WIDTH <= bonusPosition[i].x)))
			{
				collision = Collision::COLLISION_SPRING;
				game.bonus[i].body->setTexture(g_Assets.SPRING_2_TEXTURE);
				game.actualBonusId = i;
			}
			break;
		case BonusType::TRAMPOLINE:
			if (((doodlePosition.y + DOODLE_HEIGHT + TRAMPOLINE_HEIGHT + 0.5 >= bonusPosition[i].y + TRAMPOLINE_HEIGHT - 0.5) && (doodlePosition.y - 0.5 <= bonusPosition[i].y - DOODLE_HEIGHT + 0.5)
				&& (doodlePosition.x + DOODLE_WIDTH + TRAMPOLINE_WIDTH >= bonusPosition[i].x) && (doodlePosition.x - TRAMPOLINE_WIDTH <= bonusPosition[i].x)))
			{
				collision = Collision::COLLISION_TRAMPLANE;
				game.actualBonusId = i;
			}
			break;
		case BonusType::HAT_HELICOPTER:
			if (((doodlePosition.y + DOODLE_HEIGHT + HAT_HELICOPTER_HEIGHT + 0.5 >= bonusPosition[i].y + HAT_HELICOPTER_HEIGHT - 0.5) && (doodlePosition.y - 0.5 <= bonusPosition[i].y - DOODLE_HEIGHT + 0.5)
				&& (doodlePosition.x + DOODLE_WIDTH + HAT_HELICOPTER_WIDTH >= bonusPosition[i].x) && (doodlePosition.x - HAT_HELICOPTER_WIDTH <= bonusPosition[i].x)))
			{
				collision = Collision::COLLISION_HAT_HELICOPTER;
				game.actualBonusId = i;

				if (game.hero.direction.x == DirectionX::RIGHT)
				{
					game.bonus[i].body->setPosition(doodlePosition.x + 15, doodlePosition.y - 15);     // что такое 15?!
				}
				else if ((game.hero.direction.x == DirectionX::LEFT) || (game.hero.direction.x == DirectionX::NONE))
				{
					game.bonus[i].body->setPosition(doodlePosition.x + 15, doodlePosition.y - 15);     // ЧТО ЭТО?! ПОЧЕМУ ОНО СОВПАДАЕТ С ТЕМ, ЧТО ВЫШЕ?! АААААААА!!!
				}
			}
			break;
		case BonusType::ROCKET:
			if (((doodlePosition.y + DOODLE_HEIGHT + ROCKET_HEIGHT + 0.5 >= bonusPosition[i].y + ROCKET_HEIGHT - 0.5) && (doodlePosition.y - 0.5 <= bonusPosition[i].y - DOODLE_HEIGHT + 0.5)
				&& (doodlePosition.x + DOODLE_WIDTH + ROCKET_WIDTH >= bonusPosition[i].x) && (doodlePosition.x - ROCKET_WIDTH <= bonusPosition[i].x)))
			{
				collision = Collision::COLLISION_ROCKET;
				game.actualBonusId = i;

				if (game.hero.direction.x == DirectionX::RIGHT)
				{
					game.bonus[i].body->setPosition(doodlePosition.x - ROCKET_WIDTH, doodlePosition.y);
				}
				else if ((game.hero.direction.x == DirectionX::LEFT) || (game.hero.direction.x == DirectionX::NONE))
				{
					game.bonus[i].body->setPosition(doodlePosition.x + DOODLE_WIDTH, doodlePosition.y);
				}
			}
			break;
		}
	}

	switch (collision)
	{
	case Collision::COLLISION_PLATE:
		game.actualBonus = BonusType::NO;
		return 5500;
	case Collision::COLLISION_SPRING:
		game.actualBonus = BonusType::SPRING;
		return 4500;
	case Collision::COLLISION_TRAMPLANE:
		game.actualBonus = BonusType::TRAMPOLINE;
		return 6000;
	case Collision::COLLISION_HAT_HELICOPTER:
		game.actualBonus = BonusType::HAT_HELICOPTER;
		return 12000;
	case Collision::COLLISION_ROCKET:
		game.actualBonus = BonusType::ROCKET;
		return 24000;
	default:
	//	game.actualBonus = NO;            // кто-нибудь помнит, зачем я это закомментил? Нет? Кто-нибудь...
		return 0;
	}
}

void initAssets(void) // а внутри ещё функцию, которая принимает переменную и путь к файлу в виде строки
{
	if (!g_Assets.BACKGROUND_TEXTURE.loadFromFile("images/background.png"))
	{
		printf("Error loaded file");
	}
	g_Assets.BACKGROUND_TEXTURE.setSmooth(true);
	g_Assets.BACKGROUND_TEXTURE.setRepeated(true);
	
	g_Assets.BACKGROUND = new sf::Sprite;
	g_Assets.BACKGROUND->setTextureRect(sf::IntRect(0, 0, 550, 700));
	g_Assets.BACKGROUND->setTexture(g_Assets.BACKGROUND_TEXTURE);

	if (!g_Assets.TRAMPOLINE_TEXTURE.loadFromFile("images/TRAMPOLINE_20_7.png"))
	{
		printf("Error loaded file");
	}
	g_Assets.TRAMPOLINE_TEXTURE.setSmooth(true);

	if (!g_Assets.ROCKET_NONE_TEXTURE.loadFromFile("images/Rocket_none_23_36.png"))
	{
		printf("Error loaded file");
	}
	g_Assets.ROCKET_NONE_TEXTURE.setSmooth(true);

	if (!g_Assets.ROCKET_1_LEFT_TEXTURE.loadFromFile("images/Rocket_left_1_12_40.png"))
	{
		printf("Error loaded file");
	}
	g_Assets.ROCKET_1_LEFT_TEXTURE.setSmooth(true);

	if (!g_Assets.ROCKET_1_RIGHT_TEXTURE.loadFromFile("images/Rocket_right_1_12_40.png"))
	{
		printf("Error loaded file");
	}
	g_Assets.ROCKET_1_RIGHT_TEXTURE.setSmooth(true);

	if (!g_Assets.ROCKET_2_LEFT_TEXTURE.loadFromFile("images/Rocket_left_2_15_52.png"))
	{
		printf("Error loaded file");
	}
	g_Assets.ROCKET_2_LEFT_TEXTURE.setSmooth(true);

	if (!g_Assets.ROCKET_2_RIGHT_TEXTURE.loadFromFile("images/Rocket_right_2_15_52.png"))
	{
		printf("Error loaded file");
	}
	g_Assets.ROCKET_2_RIGHT_TEXTURE.setSmooth(true);

	if (!g_Assets.ROCKET_3_LEFT_TEXTURE.loadFromFile("images/Rocket_left_3_23_61.png"))
	{
		printf("Error loaded file");
	}
	g_Assets.ROCKET_3_LEFT_TEXTURE.setSmooth(true);

	if (!g_Assets.ROCKET_3_RIGHT_TEXTURE.loadFromFile("images/Rocket_right_3_23_61.png"))
	{
		printf("Error loaded file");
	}
	g_Assets.ROCKET_3_RIGHT_TEXTURE.setSmooth(true);

	if (!g_Assets.HAT_HELOCPTER_NONE_RIGHT_TEXTURE.loadFromFile("images/Hat_Helicopter_None_Right_30_18.png"))
	{
		printf("Error loaded file");
	}
	g_Assets.HAT_HELOCPTER_NONE_RIGHT_TEXTURE.setSmooth(true);

	if (!g_Assets.HAT_HELOCPTER_NONE_LEFT_TEXTURE.loadFromFile("images/Hat_Helicopter_None_Left_30_18.png"))
	{
		printf("Error loaded file");
	}
	g_Assets.HAT_HELOCPTER_NONE_LEFT_TEXTURE.setSmooth(true);

	if (!g_Assets.HAT_HELOCPTER_DIAGONAL_LEFT_TEXTURE.loadFromFile("images/Hat_Helicopter_Fly_Diagonal_Left_29_26.png"))
	{
		printf("Error loaded file");
	}
	g_Assets.HAT_HELOCPTER_DIAGONAL_LEFT_TEXTURE.setSmooth(true);

	if (!g_Assets.HAT_HELOCPTER_DIAGONAL_RIGHT_TEXTURE.loadFromFile("images/Hat_Helicopter_Fly_Diagonal_Right_29_26.png"))
	{
		printf("Error loaded file");
	}
	g_Assets.HAT_HELOCPTER_DIAGONAL_RIGHT_TEXTURE.setSmooth(true);
	
	if (!g_Assets.HAT_HELOCPTER_FLY_LEFT_TEXTURE.loadFromFile("images/Hat_Helicopter_Left_29_23.png"))
	{
		printf("Error loaded file");
	}
	g_Assets.HAT_HELOCPTER_FLY_LEFT_TEXTURE.setSmooth(true);

	if (!g_Assets.HAT_HELOCPTER_FLY_RIGHT_TEXTURE.loadFromFile("images/Hat_Helicopter_Right_29_23.png"))
	{
		printf("Error loaded file");
	}
	g_Assets.HAT_HELOCPTER_FLY_RIGHT_TEXTURE.setSmooth(true);

	if (!g_Assets.DOODLE_LEFT_TEXTURE.loadFromFile("images/Doodle45_45Left.png"))
	{
		printf("Error loaded file");
	}
	g_Assets.DOODLE_LEFT_TEXTURE.setSmooth(true);

	if (!g_Assets.DOODLE_RIGHT_TEXTURE.loadFromFile("images/Doodle45_45Right.png"))
	{
		printf("Error loaded file");
	}
	g_Assets.DOODLE_RIGHT_TEXTURE.setSmooth(true);
	
	if (!g_Assets.DOODLE_JUMP_LEFT_TEXTURE.loadFromFile("images/Doodle45_42Left_Jump.png"))
	{
		printf("Error loaded file");
	}
	g_Assets.DOODLE_JUMP_LEFT_TEXTURE.setSmooth(true);

	if (!g_Assets.DOODLE_JUMP_RIGHT_TEXTURE.loadFromFile("images/Doodle45_42Right_Jump.png"))
	{
		printf("Error loaded file");
	}
	g_Assets.DOODLE_JUMP_RIGHT_TEXTURE.setSmooth(true);
	
	if (!g_Assets.PLATE_STATIC_TEXTURE.loadFromFile("images/Plate_63_15_Green.png"))
	{
		printf("Error loaded file");
	}
	g_Assets.PLATE_STATIC_TEXTURE.setSmooth(true);

	if (!g_Assets.PLATE_DYNAMIC_TEXTURE.loadFromFile("images/Plate_63_15_Blue.png"))
	{
		printf("Error loaded file");
	}
	g_Assets.PLATE_DYNAMIC_TEXTURE.setSmooth(true);

	if (!g_Assets.PLATE_CLOUD_TEXTURE.loadFromFile("images/Plate_63_15_Cloud.png"))
	{
		printf("Error loaded file");
	}
	g_Assets.PLATE_CLOUD_TEXTURE.setSmooth(true);

	if (!g_Assets.SPRING_TEXTURE.loadFromFile("images/Spring16_12.png"))
	{
		printf("Error loaded file");
	}
	g_Assets.SPRING_TEXTURE.setSmooth(true);
	
	if (!g_Assets.SPRING_2_TEXTURE.loadFromFile("images/Spring16_26.png"))
	{
		printf("Error loaded file");
	}
	g_Assets.SPRING_2_TEXTURE.setSmooth(true);

	if (!g_Assets.font.loadFromFile("arial.ttf"))
	{
		printf("Error loaded arial\n");
	}
}