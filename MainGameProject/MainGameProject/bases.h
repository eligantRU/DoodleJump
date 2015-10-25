#include <SFML/Graphics.hpp>

const int NUMBER_PLATES = 25;
const int NUMBER_BONUSES = 3;
int DELTA_HEIGHT = 0;
const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);
const float STEP = 2.f;

bool noJumps = true;
bool endOfGame = false;
int upping = DELTA_HEIGHT;

typedef enum
{
	COLLISION_SPRING,
	COLLISION_HAT_HELICOPTER,
	COLLISION_TRAMPLANE,
	COLLISION_MISSLE,
	COLLISION_PLATE,
	NO_COLLISION
} Collision;

typedef enum
{
	UP,
	DOWN
} DirectionY;

typedef enum
{
	NONE,
	LEFT,
	RIGHT
} DirectionX;

typedef enum
{
	HAT_HELICOPTER,
	SPRING,
	TRAMPLANE,
	MISSILE,
	NO
} BonusType;

struct Direction
{
	DirectionX x;
	DirectionY y;
};

struct Doodle
{
	sf::RectangleShape * body;
	Direction direction;
	Collision collision;
};

struct Plate
{
	sf::RectangleShape * body;
};

struct Bonus
{
	BonusType type;
	sf::RectangleShape * body;
};

struct Game
{
	Doodle hero;
	Plate plate[NUMBER_PLATES];
	Bonus bonus[NUMBER_BONUSES];
};