#include <SFML/Graphics.hpp>

const int NUMBER_PLATES = 25;
const int JUMP_HEIGHT = 4500;
const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);
const float STEP = 2.f;

bool noJumps = true;
bool endOfGame = false;
int upping = JUMP_HEIGHT;

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

struct Direction
{
	DirectionX x;
	DirectionY y;
};

struct Doodle
{
	sf::RectangleShape * body;
	Direction direction;
	bool jumping;
};

struct Plate
{
	sf::RectangleShape * body;
};

struct Game
{
	Doodle hero;
	Plate plate[NUMBER_PLATES];
};