#pragma once

#include "stdafx.h"

static const int NUMBER_PLATES = 40; 
static const int NUMBER_BONUSES = 1;
static const int NUMBER_INSECTS = 5;
static const float STEP = 6.f;
static const float ACCELERATION = 1.f;
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

enum class PlateType
{
	STATIC,
	STATIC_DYNAMIC_X,
	UNSTABLE,
	UNSTABLE_DYNAMIC_X,
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
	MISSILE,
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

struct SDirection
{
	DirectionX x;
	DirectionY y;
};

struct SGameResult
{
	uint64_t points;
	GameStatus status;
	Collision collision;
};