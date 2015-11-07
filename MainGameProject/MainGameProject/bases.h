#include <SFML/Graphics.hpp>

const int NUMBER_PLATES = 15;
const int NUMBER_BONUSES = 2;
const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);
const float STEP = 3.f;

bool G_noJumps; // = true;
bool G_endOfGame; // = false;

typedef enum
{
	STATIC,
	DYNAMIC_X,
	CLOUD
} PlateType;

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
	int deltaHeight;
};

struct Plate
{
	sf::RectangleShape * body;
	PlateType type;
	Direction direction;
};

struct Bonus
{
	BonusType type;
	sf::RectangleShape * body;
};

struct Game
{
	Doodle hero;
	BonusType actualBonus;
	Plate plate[NUMBER_PLATES];
	Bonus bonus[NUMBER_BONUSES];
};
