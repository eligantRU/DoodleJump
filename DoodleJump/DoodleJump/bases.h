#pragma once

#include "stdafx.h"

static const int NUMBER_PLATES = 26; 
static const int NUMBER_BONUSES = 1;
static const int NUMBER_INSECTS = 5;
static const int NUMBER_UNSTABLE_PLATES = 3;
static const float STEP = 6.f;
static const float ACCELERATION = 1.f;
static const int RECORD_LINE_WIDTH = 49;
static const int RECORD_LINE_HEIGHT = 4;
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
static const int TRAMPOLINE_WIDTH = 36;
static const int TRAMPOLINE_HEIGHT = 13;
static const int HOLE_WIDTH = 60;
static const int HOLE_HEIGHT = 54;
static const float PLATE_DELTA_HEIGHT = 22.f;
static const float SPRING_DELTA_HEIGHT = 60.f;
static const float TRAMPLANE_DELTA_HEIGHT = 65.f;
static const float HAT_HELICOPTER_DELTA_HEIGHT = 200.f;
static const float ROCKET_DELTA_HEIGHT = 180.f;
static const int BUTTON_WIDTH = 100;
static const int BUTTON_HEIGHT = 29;
static const int WINDOW_WIDTH = 550;
static const int WINDOW_HEIGHT = 700;
static const sf::Vector2f DOODLE_START_POSITION((WINDOW_WIDTH - DOODLE_WIDTH) / 2, 0);
static const std::string API_HOST = "http://lorem-ipsum-dolor-sit-amet.xyz";
static const unsigned DEFAULT_NUMBER_RECORDS = 36;

enum class PlateType
{
	STATIC,
	STATIC_DYNAMIC_X,
	UNSTABLE,
	CLOUD
};

enum class Collision
{
	COLLISION_SPRING,
	COLLISION_HAT_HELICOPTER,
	COLLISION_TRAMPLANE,
	COLLISION_MISSLE,
	COLLISION_PLATE,
	COLLISION_GHOST_PLATE,
	COLLISION_ROCKET,
	COLLISION_UNSTABLE,
	COLLISION_HOLE,
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
	ROCKET,
	NO
};

enum class GameStatus
{
	START_SCENE,
	HELP_SCENE,
	GAME_SCENE,
	PAUSE_SCENE,
	GAME_OVER_SCENE
};

struct SGameResult // NOTE: in future u can use this to exchange data from scene to scene
{
	GameStatus status;
};
