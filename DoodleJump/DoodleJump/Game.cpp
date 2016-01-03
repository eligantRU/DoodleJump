#include "stdafx.h"
#include "sheet.h"

bool g_noJumps; // костыльменная, уйдёт с вводом Menu, как и функция starter()
Game game;
sf::View view;
sf::Vector2f kostil;

void resetGame(Game & game, sf::View & view)
{
	view.reset(sf::FloatRect(0, 0, 550, 700));
	game.text.setPosition(0, 0);
	g_noJumps = true;
	game.endOfGame = false;
	initialGame(game, view);
	game.points = 0;
}

bool waitRestartChoosen(sf::RenderWindow & window)
{
	sf::Event event;
	while (window.waitEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			return false;
		}
		if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Space:
				return true;
			case sf::Keyboard::Return:
				return true;
			case sf::Keyboard::Escape:
				return false;
			default:
				break;
			}
		}
	}
	return false;
}

void onPauseMenu(sf::RenderWindow & window)
{
	// It's no working!
	kostil = game.assets.BACKGROUND->getPosition();

	sf::Text backText;
	backText.setFont(game.assets.font);
	backText.setCharacterSize(20);
	backText.setString("Back");
	backText.setStyle(sf::Text::Bold);
	backText.setPosition(255.f, kostil.y + 225.f);
	backText.setColor(sf::Color(0, 0, 0));

	sf::RectangleShape back(sf::Vector2f(120, 50));
	back.setPosition(215.f, kostil.y + 210.f);


	window.clear(sf::Color(255, 255, 255));
	window.draw(*game.assets.BACKGROUND);
	window.draw(back);
	window.draw(backText);
	window.display();

	sf::Event event;

	if (window.pollEvent(event) && sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

		if (((mousePosition.y >= 210) && (mousePosition.y <= 260)
			&& (mousePosition.x >= 215) && (mousePosition.x <= 335)))
		{
			view.setCenter(275, kostil.y-350); // 350 -- половина экрана
			game.frameFunc = onGameFrame;
		}
	}
}

void onStartMenu(sf::RenderWindow & window)
{
	game.assets.BACKGROUND->setPosition(0, 0);

	sf::Text playText;
	playText.setFont(game.assets.font);
	playText.setCharacterSize(20);
	playText.setString("Play");
	playText.setStyle(sf::Text::Bold);
	playText.setPosition(255.f, 225.f);
	playText.setColor(sf::Color(0, 0, 0));

	sf::Text exitText;
	exitText.setFont(game.assets.font);
	exitText.setCharacterSize(20);
	exitText.setString("Exit");
	exitText.setStyle(sf::Text::Bold);
	exitText.setPosition(255.f, 405.f);
	exitText.setColor(sf::Color(0, 0, 0));

	sf::RectangleShape play(sf::Vector2f(120, 50));
	play.setPosition(215.f, 210.f);

	sf::RectangleShape records(sf::Vector2f(120, 50));
	records.setPosition(215.f, 300.f);

	sf::RectangleShape exit(sf::Vector2f(120, 50));
	exit.setPosition(215.f, 390.f);


	window.clear(sf::Color(255, 255, 255));
	window.draw(*game.assets.BACKGROUND);
	window.draw(play);
	window.draw(exit);
	window.draw(playText);
	window.draw(exitText);
	window.display();

	sf::Event event;

	if (window.pollEvent(event) && sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

		if (((mousePosition.y >= 210) && (mousePosition.y <= 260)
			&& (mousePosition.x >= 215) && (mousePosition.x <= 335)))
		{
			game.frameFunc = onGameFrame;
		}

		if (((mousePosition.y >= 390) && (mousePosition.y <= 440)
			&& (mousePosition.x >= 215) && (mousePosition.x <= 335)))
		{
			window.close();
		}		
	}
}

void onGameOverMenu(sf::RenderWindow & window)
{
	game.assets.BACKGROUND->setPosition(0, 0);

	sf::Text menuText;
	menuText.setFont(game.assets.font);
	menuText.setCharacterSize(20);
	menuText.setString("Menu");
	menuText.setStyle(sf::Text::Bold);
	menuText.setPosition(255.f, 225.f);
	menuText.setColor(sf::Color(0, 0, 0));

	sf::Text recordsText;
	recordsText.setFont(game.assets.font);
	recordsText.setCharacterSize(20);
	recordsText.setString("Records");
	recordsText.setStyle(sf::Text::Bold);
	recordsText.setPosition(240.f, 315.f);
	recordsText.setColor(sf::Color(0, 0, 0));

	sf::RectangleShape menu(sf::Vector2f(120, 50));
	menu.setPosition(215.f, 210.f);

	sf::RectangleShape records(sf::Vector2f(120, 50));
	records.setPosition(215.f, 300.f);


	window.clear(sf::Color(255, 255, 255));
	window.draw(*game.assets.BACKGROUND);
	window.draw(menu);
	window.draw(records);
	window.draw(recordsText);
	window.draw(menuText);
	window.display();

	sf::Event event;

	if (window.pollEvent(event) && sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

		if (((mousePosition.y >= 210) && (mousePosition.y <= 260)
			&& (mousePosition.x >= 215) && (mousePosition.x <= 335)))
		{
			game.frameFunc = onGameFrame;
		}
	}
}

void onGameFrame(sf::RenderWindow & window)
{
	if (!game.endOfGame)
	{
		render(window, game);
		keyPressed(window, game);
		update(window, game, view);
		window.setView(view);
	}
	else
	{
		resetGame(game, view);
		view.setCenter(275, 350);
		window.setView(view);
		game.frameFunc = onGameOverMenu;
	}
}

void gameLoop(sf::RenderWindow & window, Game & game)
{
	while (window.isOpen())
	{
		game.frameFunc(window);
	}
}

void enterGameLoop(void)
{
	sf::RenderWindow window(sf::VideoMode(550, 700), "Doodle Jump");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	sf::Clock clock;
	// Game game; 
	initAssets(game);
	resetGame(game, view);
	update(window, game, view);

	bool needUpdate = false;

	game.frameFunc = onStartMenu;
	gameLoop(window, game);
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

		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			view.setCenter(275, 350);
			game.frameFunc = onPauseMenu; // It's no working!
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
	initBonuses(game);
	game.actualBonus = BonusType::NO;
}

void render(sf::RenderWindow & window, Game & game) // переписать под работу с вектором
{
	window.clear(sf::Color(230, 230, 230));
	window.draw(*game.assets.BACKGROUND);

	for (Plate &plate : game.plate)
	{
		window.draw(*plate.body);
	}

	window.draw(*game.hero.body);

	for (int i = 0; i < NUMBER_BONUSES; ++i)
	{
		window.draw(*game.bonus[i].body);
	}

	game.text.setFont(game.assets.font);
	game.text.setCharacterSize(20);
	game.text.setString("Bonuses: " + std::to_string(game.points));
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
		game.hero.body->setTexture(game.assets.DOODLE_JUMP_RIGHT_TEXTURE);
	}
	else if (game.hero.direction.x == DirectionX::LEFT)
	{
		position.x -= STEP;
		game.hero.body->setTexture(game.assets.DOODLE_JUMP_LEFT_TEXTURE);
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
				game.hero.body->setTexture(game.assets.DOODLE_RIGHT_TEXTURE);
			}
			else if (game.hero.lastDirectionX == DirectionX::LEFT)
			{
				game.hero.body->setTexture(game.assets.DOODLE_LEFT_TEXTURE);
			}
		}
	}
	else if (game.hero.direction.y == DirectionY::UP)
	{
		if (game.hero.lastDirectionX == DirectionX::LEFT)
		{
			game.hero.body->setTexture(game.assets.DOODLE_JUMP_LEFT_TEXTURE);
		}
		else if (game.hero.lastDirectionX == DirectionX::RIGHT)
		{
			game.hero.body->setTexture(game.assets.DOODLE_JUMP_RIGHT_TEXTURE);
		}

		if (game.hero.deltaHeight > 0)
		{
			position.y -= STEP;
			--game.hero.deltaHeight;
		}
		else
		{
			game.hero.direction.y = DirectionY::DOWN;
			if (game.hero.body->getPosition().y < game.hero.positionBeforeDown.y)
			{
				game.hero.positionBeforeDown = game.hero.body->getPosition();
			}
		}
	}

	// в отдельную функцию
	float boostFactor = 1.f;
	switch (game.actualBonus)
	{
	case  BonusType::SPRING:
		boostFactor = 2.f;
		break;
	case  BonusType::TRAMPOLINE:
		boostFactor = 2.f;
		break;
	case  BonusType::HAT_HELICOPTER:
		boostFactor = 2.f;
		break;
	case  BonusType::ROCKET:
		boostFactor = 3.f;
		break;
	case BonusType::NO:
	default:
		break;
	}
	game.hero.body->move(position * boostFactor);
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
		if (game.hero.deltaHeight <= 2)
		{
			game.qwerty = -1;
			game.bonus[game.actualBonusId].body->setTexture(game.assets.HAT_HELOCPTER_FLY_LEFT_TEXTURE);
			game.bonus[game.actualBonusId].body->rotate(-0.07f);
			game.bonus[game.actualBonusId].body->move(sf::Vector2f(-2*STEP, 6*STEP));
		}
		if (game.hero.deltaHeight == 0)
		{
			game.qwerty = 0;
			game.actualBonus = BonusType::NO;
		}

		if ((game.qwerty >= 0) && (game.qwerty <= 2))
		{
			game.bonus[game.actualBonusId].body->setTexture(game.assets.HAT_HELOCPTER_FLY_LEFT_TEXTURE);
			++game.qwerty;
		}
		else if((game.qwerty >= 3) && (game.qwerty <= 4))
		{
			game.bonus[game.actualBonusId].body->setTexture(game.assets.HAT_HELOCPTER_DIAGONAL_LEFT_TEXTURE);
			++game.qwerty;
		}
		else if ((game.qwerty >= 5) && (game.qwerty <= 6))
		{
			game.bonus[game.actualBonusId].body->setTexture(game.assets.HAT_HELOCPTER_DIAGONAL_RIGHT_TEXTURE);
			++game.qwerty;
		}
		else if ((game.qwerty >= 7) && (game.qwerty <= 8))
		{
			game.bonus[game.actualBonusId].body->setTexture(game.assets.HAT_HELOCPTER_FLY_RIGHT_TEXTURE);
			++game.qwerty;
		}
		else if (game.qwerty == 8)
		{
			game.qwerty = 0;
		}

		if ((game.qwerty >= 0) && (game.qwerty <= 8) && (game.actualBonus != BonusType::NO))
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
		if (game.hero.deltaHeight <= 15)
		{
			game.qwerty = -1;
			game.bonus[game.actualBonusId].body->setTexture(game.assets.ROCKET_NONE_TEXTURE);
			game.bonus[game.actualBonusId].body->rotate(-0.07f);
			game.bonus[game.actualBonusId].body->move(sf::Vector2f(-2 * STEP, 6 * STEP));
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
				game.bonus[game.actualBonusId].body->setTexture(game.assets.ROCKET_1_LEFT_TEXTURE);
			} 
			else if (game.hero.lastDirectionX == DirectionX::LEFT)
			{
				game.bonus[game.actualBonusId].body->setTexture(game.assets.ROCKET_1_RIGHT_TEXTURE);
			}
			++game.qwerty;
		}
		if ((game.qwerty >= 201) && (game.qwerty <= 400))
		{
			if (game.hero.lastDirectionX == DirectionX::RIGHT)
			{
				game.bonus[game.actualBonusId].body->setTexture(game.assets.ROCKET_2_LEFT_TEXTURE);
			}
			else if (game.hero.lastDirectionX == DirectionX::LEFT)
			{
				game.bonus[game.actualBonusId].body->setTexture(game.assets.ROCKET_2_RIGHT_TEXTURE);
			}
			++game.qwerty;
		}
		if ((game.qwerty >= 401) && (game.qwerty <= 600))
		{
			if (game.hero.lastDirectionX == DirectionX::RIGHT)
			{
				game.bonus[game.actualBonusId].body->setTexture(game.assets.ROCKET_3_LEFT_TEXTURE);
			}
			else if (game.hero.lastDirectionX == DirectionX::LEFT)
			{
				game.bonus[game.actualBonusId].body->setTexture(game.assets.ROCKET_3_RIGHT_TEXTURE);
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

	if ((game.hero.direction.y == DirectionY::UP) && (doodlePosition.y <= game.hero.positionBeforeDown.y))
	{
		view.setCenter(275, doodlePosition.y);
		game.assets.BACKGROUND->setPosition(0, doodlePosition.y-350);
		game.text.setPosition(0, doodlePosition.y-350);
		++game.points;
	}
	
	moveDynamicPlates(game);
	generPlates(game);
	generBonuses(game);

	if (checkGameEnd(game))
	{
		game.endOfGame = true;
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
				game.bonus[i].body->setTexture(game.assets.SPRING_2_TEXTURE);
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
		return 5500 / 60;
	case Collision::COLLISION_SPRING:
		game.actualBonus = BonusType::SPRING;
		return 4500 / 60;
	case Collision::COLLISION_TRAMPLANE:
		game.actualBonus = BonusType::TRAMPOLINE;
		return 6000 / 60;
	case Collision::COLLISION_HAT_HELICOPTER:
		game.actualBonus = BonusType::HAT_HELICOPTER;
		return 12000 / 60;
	case Collision::COLLISION_ROCKET:
		game.actualBonus = BonusType::ROCKET;
		return 24000 / 60;
	default:
		return 0;
	}
}

void initAssets(Game & game) // а внутри ещё функцию, которая принимает переменную и путь к файлу в виде строки
{
	if (!game.assets.BACKGROUND_TEXTURE.loadFromFile("images/background.png"))
	{
		printf("Error loaded file");
	}
	game.assets.BACKGROUND_TEXTURE.setSmooth(true);
	game.assets.BACKGROUND_TEXTURE.setRepeated(true);
	
	game.assets.BACKGROUND = new sf::Sprite;
	game.assets.BACKGROUND->setTextureRect(sf::IntRect(0, 0, 550, 700));
	game.assets.BACKGROUND->setTexture(game.assets.BACKGROUND_TEXTURE);

	if (!game.assets.TRAMPOLINE_TEXTURE.loadFromFile("images/TRAMPOLINE_20_7.png"))
	{
		printf("Error loaded file");
	}
	game.assets.TRAMPOLINE_TEXTURE.setSmooth(true);

	if (!game.assets.ROCKET_NONE_TEXTURE.loadFromFile("images/Rocket_none_23_36.png"))
	{
		printf("Error loaded file");
	}
	game.assets.ROCKET_NONE_TEXTURE.setSmooth(true);

	if (!game.assets.ROCKET_1_LEFT_TEXTURE.loadFromFile("images/Rocket_left_1_12_40.png"))
	{
		printf("Error loaded file");
	}
	game.assets.ROCKET_1_LEFT_TEXTURE.setSmooth(true);

	if (!game.assets.ROCKET_1_RIGHT_TEXTURE.loadFromFile("images/Rocket_right_1_12_40.png"))
	{
		printf("Error loaded file");
	}
	game.assets.ROCKET_1_RIGHT_TEXTURE.setSmooth(true);

	if (!game.assets.ROCKET_2_LEFT_TEXTURE.loadFromFile("images/Rocket_left_2_15_52.png"))
	{
		printf("Error loaded file");
	}
	game.assets.ROCKET_2_LEFT_TEXTURE.setSmooth(true);

	if (!game.assets.ROCKET_2_RIGHT_TEXTURE.loadFromFile("images/Rocket_right_2_15_52.png"))
	{
		printf("Error loaded file");
	}
	game.assets.ROCKET_2_RIGHT_TEXTURE.setSmooth(true);

	if (!game.assets.ROCKET_3_LEFT_TEXTURE.loadFromFile("images/Rocket_left_3_23_61.png"))
	{
		printf("Error loaded file");
	}
	game.assets.ROCKET_3_LEFT_TEXTURE.setSmooth(true);

	if (!game.assets.ROCKET_3_RIGHT_TEXTURE.loadFromFile("images/Rocket_right_3_23_61.png"))
	{
		printf("Error loaded file");
	}
	game.assets.ROCKET_3_RIGHT_TEXTURE.setSmooth(true);

	if (!game.assets.HAT_HELOCPTER_NONE_RIGHT_TEXTURE.loadFromFile("images/Hat_Helicopter_None_Right_30_18.png"))
	{
		printf("Error loaded file");
	}
	game.assets.HAT_HELOCPTER_NONE_RIGHT_TEXTURE.setSmooth(true);

	if (!game.assets.HAT_HELOCPTER_NONE_LEFT_TEXTURE.loadFromFile("images/Hat_Helicopter_None_Left_30_18.png"))
	{
		printf("Error loaded file");
	}
	game.assets.HAT_HELOCPTER_NONE_LEFT_TEXTURE.setSmooth(true);

	if (!game.assets.HAT_HELOCPTER_DIAGONAL_LEFT_TEXTURE.loadFromFile("images/Hat_Helicopter_Fly_Diagonal_Left_29_26.png"))
	{
		printf("Error loaded file");
	}
	game.assets.HAT_HELOCPTER_DIAGONAL_LEFT_TEXTURE.setSmooth(true);

	if (!game.assets.HAT_HELOCPTER_DIAGONAL_RIGHT_TEXTURE.loadFromFile("images/Hat_Helicopter_Fly_Diagonal_Right_29_26.png"))
	{
		printf("Error loaded file");
	}
	game.assets.HAT_HELOCPTER_DIAGONAL_RIGHT_TEXTURE.setSmooth(true);
	
	if (!game.assets.HAT_HELOCPTER_FLY_LEFT_TEXTURE.loadFromFile("images/Hat_Helicopter_Left_29_23.png"))
	{
		printf("Error loaded file");
	}
	game.assets.HAT_HELOCPTER_FLY_LEFT_TEXTURE.setSmooth(true);

	if (!game.assets.HAT_HELOCPTER_FLY_RIGHT_TEXTURE.loadFromFile("images/Hat_Helicopter_Right_29_23.png"))
	{
		printf("Error loaded file");
	}
	game.assets.HAT_HELOCPTER_FLY_RIGHT_TEXTURE.setSmooth(true);

	if (!game.assets.DOODLE_LEFT_TEXTURE.loadFromFile("images/Doodle45_45Left.png"))
	{
		printf("Error loaded file");
	}
	game.assets.DOODLE_LEFT_TEXTURE.setSmooth(true);

	if (!game.assets.DOODLE_RIGHT_TEXTURE.loadFromFile("images/Doodle45_45Right.png"))
	{
		printf("Error loaded file");
	}
	game.assets.DOODLE_RIGHT_TEXTURE.setSmooth(true);
	
	if (!game.assets.DOODLE_JUMP_LEFT_TEXTURE.loadFromFile("images/Doodle45_42Left_Jump.png"))
	{
		printf("Error loaded file");
	}
	game.assets.DOODLE_JUMP_LEFT_TEXTURE.setSmooth(true);

	if (!game.assets.DOODLE_JUMP_RIGHT_TEXTURE.loadFromFile("images/Doodle45_42Right_Jump.png"))
	{
		printf("Error loaded file");
	}
	game.assets.DOODLE_JUMP_RIGHT_TEXTURE.setSmooth(true);
	
	if (!game.assets.PLATE_STATIC_TEXTURE.loadFromFile("images/Plate_63_15_Green.png"))
	{
		printf("Error loaded file");
	}
	game.assets.PLATE_STATIC_TEXTURE.setSmooth(true);

	if (!game.assets.PLATE_DYNAMIC_TEXTURE.loadFromFile("images/Plate_63_15_Blue.png"))
	{
		printf("Error loaded file");
	}
	game.assets.PLATE_DYNAMIC_TEXTURE.setSmooth(true);

	if (!game.assets.PLATE_CLOUD_TEXTURE.loadFromFile("images/Plate_63_15_Cloud.png"))
	{
		printf("Error loaded file");
	}
	game.assets.PLATE_CLOUD_TEXTURE.setSmooth(true);

	if (!game.assets.SPRING_TEXTURE.loadFromFile("images/Spring16_12.png"))
	{
		printf("Error loaded file");
	}
	game.assets.SPRING_TEXTURE.setSmooth(true);
	
	if (!game.assets.SPRING_2_TEXTURE.loadFromFile("images/Spring16_26.png"))
	{
		printf("Error loaded file");
	}
	game.assets.SPRING_2_TEXTURE.setSmooth(true);

	if (!game.assets.font.loadFromFile("arial.ttf"))
	{
		printf("Error loaded arial\n");
	}
}