#include "stdafx.h"
#include "GameScene.h"

void resetGame(Game & game, sf::View & view)
{
	view.reset(sf::FloatRect(0, 0, 550, 700));
	game.text.setPosition(0, 0);
	game.endOfGame = false;
	initialGame(game, view);
	game.points = 0;
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

	sf::Clock clock; // TODO: not used -- fix it or delete
	// Game game; 
	initAssets(game);
	resetGame(game, view);

	game.frameFunc = onStartMenu;
	gameLoop(window, game);
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
		boostFactor = 2.5f;
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

	if (unstablePlateID != -1)
	{
		game.plate[unstablePlateID].body->rotate(-1.f);
		game.plate[unstablePlateID].body->move(sf::Vector2f(-1 * STEP, 4 * STEP));
		--kostil2;
		if (kostil2 == 0)
		{
			game.plate[unstablePlateID].body->setRotation(0);
			unstablePlateID = -1;
		}
	}

	if (game.actualBonus == BonusType::HAT_HELICOPTER) // и это тоже в отдельную функцию
	{
		if (game.hero.deltaHeight <= 20)
		{
			game.qwerty = -1;
			game.bonus[game.actualBonusId].body->setTexture(game.assets.HAT_HELOCPTER_FLY_LEFT_TEXTURE);
			game.bonus[game.actualBonusId].body->rotate(-0.07f);
			game.bonus[game.actualBonusId].body->move(sf::Vector2f(-2 * STEP, 3 * STEP));
		}
		if (game.hero.deltaHeight == 0)
		{
			game.qwerty = 0;
			game.actualBonus = BonusType::NO;
			game.bonus[game.actualBonusId].body->setPosition(0.f, doodlePosition.y + DOODLE_HEIGHT + 275 + 2 * PLATE_HEIGHT); // костыль
		}

		if ((game.qwerty >= 0) && (game.qwerty <= 5))
		{
			game.bonus[game.actualBonusId].body->setTexture(game.assets.HAT_HELOCPTER_FLY_LEFT_TEXTURE);
			++game.qwerty;
		}
		if ((game.qwerty >= 6) && (game.qwerty <= 10))
		{
			game.bonus[game.actualBonusId].body->setTexture(game.assets.HAT_HELOCPTER_DIAGONAL_LEFT_TEXTURE);
			++game.qwerty;
		}
		if ((game.qwerty >= 11) && (game.qwerty <= 15))
		{
			game.bonus[game.actualBonusId].body->setTexture(game.assets.HAT_HELOCPTER_DIAGONAL_RIGHT_TEXTURE);
			++game.qwerty;
		}
		if ((game.qwerty >= 16) && (game.qwerty <= 20))
		{
			game.bonus[game.actualBonusId].body->setTexture(game.assets.HAT_HELOCPTER_FLY_RIGHT_TEXTURE);
			++game.qwerty;
		}
		
		if (game.qwerty == 20)
		{
			game.qwerty = 0;
		}

		if ((game.qwerty >= 0) && (game.qwerty <= 20) && (game.actualBonus != BonusType::NO))
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
			game.bonus[game.actualBonusId].body->setPosition(0.f, doodlePosition.y + DOODLE_HEIGHT + 275 + 2 * PLATE_HEIGHT); // костыль
		}

		if ((game.qwerty >= 0) && (game.qwerty <= 5))
		{
			game.bonus[game.actualBonusId].body = new sf::Sprite; // костыль
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
		if ((game.qwerty >= 6) && (game.qwerty <= 10))
		{
			game.bonus[game.actualBonusId].body = new sf::Sprite; // костыль
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
		if ((game.qwerty >= 11) && (game.qwerty <= 15))
		{
			game.bonus[game.actualBonusId].body = new sf::Sprite; // костыль
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
		if (game.qwerty == 15)
		{
			game.qwerty = 0;
		}

		if ((game.qwerty >= 0) && (game.qwerty <= 15) && (game.actualBonus != BonusType::NO))
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
		game.assets.BACKGROUND->setPosition(0, doodlePosition.y - 350);
		game.text.setPosition(0, doodlePosition.y - 350);
		++game.points;
	}

	moveDynamicPlates(game);
	moveBonuses(game);
	generPlates(game);
	generBonuses(game);

	if (checkGameEnd(game))
	{
		game.endOfGame = true;
	}
}

void initAssets(Game & game) // TODO: fix it! For example: void attachFile(string); And create folder /resource/images & /resourse/font
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

	if (!game.assets.PLATE_UNSTABLE_TEXTURE.loadFromFile("images/Plate_63_15_Unstable.png"))
	{
		printf("Error loaded file");
	}
	game.assets.PLATE_UNSTABLE_TEXTURE.setSmooth(true);

	//sf::SoundBuffer soundBuffer;

	/*if (soundBuffer.loadFromFile("/sounds/trampoline.mp3"))
	{
		game.assets.SOUND_TRAMPOLINE.setBuffer(soundBuffer);
	}
	else
	{
		printf("Error loaded sound\n"); //_exit();
	}

	if (soundBuffer.loadFromFile("/sounds/propeller.mp3"))
	{
		game.assets.SOUND_HAT_HELICOPTER.setBuffer(soundBuffer);
	}

	if (soundBuffer.loadFromFile("/sounds/feder.mp3"))
	{
		game.assets.SOUND_SPRING.setBuffer(soundBuffer);
	}*/
}
