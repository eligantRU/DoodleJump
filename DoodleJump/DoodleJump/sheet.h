#pragma once

#include "stdafx.h"
#include <string>
#include <functional>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

static const int NUMBER_PLATES = 25; // TODO: You can get 'integer devision zero'...Fix initBonuses()! 
static const int NUMBER_BONUSES = 3;
static const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);
static const float STEP = 3.f;
static const int DOODLE_WIDTH = 45;
static const int DOODLE_HEIGHT = 45;
static const int PLATE_WIDTH = 63;
static const int PLATE_HEIGHT = 15;
static const int SPRING_WIDTH = 16;
static const int SPRING_HEIGHT = 12;
static const int HAT_HELICOPTER_WIDTH = 30;
static const int HAT_HELICOPTER_HEIGHT = 18;
static const int ROCKET_WIDTH = 23;
static const int ROCKET_HEIGHT = 36;
static const int TRAMPOLINE_WIDTH = 20;
static const int TRAMPOLINE_HEIGHT = 7;
static const int MAX_NUMBER_OF_ITEMS = 3;
static const int PLATE_DELTA_HEIGHT = 100;
static const int SPRING_DELTA_HEIGHT = 75;
static const int TRAMPLANE_DELTA_HEIGHT = 100;
static const int HAT_HELICOPTER_DELTA_HEIGHT = 300;
static const int ROCKET_DELTA_HEIGHT = 400;

struct Assets
{
	sf::Sprite * BACKGROUND;
	sf::Texture BACKGROUND_TEXTURE;
	sf::Texture PLATE_STATIC_TEXTURE;
	sf::Texture PLATE_DYNAMIC_TEXTURE;
	sf::Texture PLATE_CLOUD_TEXTURE;
	sf::Texture SPRING_TEXTURE;
	sf::Texture SPRING_2_TEXTURE;
	sf::Texture DOODLE_LEFT_TEXTURE;
	sf::Texture DOODLE_RIGHT_TEXTURE;
	sf::Texture DOODLE_JUMP_LEFT_TEXTURE;
	sf::Texture DOODLE_JUMP_RIGHT_TEXTURE;
	sf::Texture HAT_HELOCPTER_DIAGONAL_RIGHT_TEXTURE;
	sf::Texture HAT_HELOCPTER_DIAGONAL_LEFT_TEXTURE;
	sf::Texture HAT_HELOCPTER_FLY_RIGHT_TEXTURE;
	sf::Texture HAT_HELOCPTER_FLY_LEFT_TEXTURE;
	sf::Texture HAT_HELOCPTER_NONE_RIGHT_TEXTURE;
	sf::Texture HAT_HELOCPTER_NONE_LEFT_TEXTURE;
	sf::Texture ROCKET_NONE_TEXTURE;
	sf::Texture ROCKET_1_LEFT_TEXTURE;
	sf::Texture ROCKET_1_RIGHT_TEXTURE;
	sf::Texture ROCKET_2_LEFT_TEXTURE;
	sf::Texture ROCKET_2_RIGHT_TEXTURE;
	sf::Texture ROCKET_3_LEFT_TEXTURE;
	sf::Texture ROCKET_3_RIGHT_TEXTURE;
	sf::Texture TRAMPOLINE_TEXTURE;
	sf::Font font;
};

enum class PlateType
{
	STATIC,
	DYNAMIC_X,
	CLOUD
};

enum class Collision
{
	COLLISION_SPRING,
	COLLISION_HAT_HELICOPTER,
	COLLISION_TRAMPLANE,
	COLLISION_MISSLE,
	COLLISION_PLATE,
	COLLISION_ROCKET,
	NO_COLLISION
};

enum class DirectionY
{
	UP,
	DOWN
};

enum class DirectionX
{
	NONE,
	LEFT,
	RIGHT
};

enum class BonusType
{
	HAT_HELICOPTER,
	SPRING,
	TRAMPOLINE,
	MISSILE,
	ROCKET,
	NO
};

struct Direction
{
	DirectionX x;
	DirectionY y;
};

struct Doodle
{
	sf::Sprite * body;
	sf::Texture texture;
	Direction direction;
	Collision collision;
	int deltaHeight;
	DirectionX lastDirectionX;
	sf::Vector2f positionBeforeDown;
};

struct Plate
{
	sf::Sprite * body;
	sf::Texture texture;
	PlateType type;
	Direction direction;
};

struct Bonus
{
	BonusType type;
	sf::Sprite * body;
	int plateIndex;
	Direction direction;
};

typedef std::function<void(sf::RenderWindow &)> RenderFrameFunc;

struct Game
{
	Doodle hero;
	BonusType actualBonus;
	int actualBonusId;
	int qwerty; // What?
	Plate plate[NUMBER_PLATES];
	Bonus bonus[NUMBER_BONUSES];
	sf::Text text;
	uint64_t points;
	bool endOfGame;
	RenderFrameFunc frameFunc;
	Assets assets;
};

bool checkGameEnd(Game & game);

void initialGame(Game & game, sf::View view);

void keyPressed(sf::RenderWindow & window, Game & game);

void render(sf::RenderWindow & window, Game & game);

int checkDoodleFall(Game & game);

void generPlates(Game & game);

void initialPlates(Game & game);

void moveDynamicPlates(Game & game);

void initialHero(Game & game, sf::View & view);

void initBonuses(Game & game);

void generBonuses(Game & game);

void buildBonus(Game & game, BonusType bonusType, int bonusIndex, sf::Vector2f platePosition, int plateIndex);

void moveBonuses(Game & game);

// TODO: fix it!
// костыль
extern Game game;
extern sf::View view;
extern sf::Vector2f kostil;

// TODO: All struct must be declare in separate file (Nick)
// костыль
#include "PauseScene.h"
#include "StartScene.h"
#include "GameOverScene.h"
#include "GameScene.h"