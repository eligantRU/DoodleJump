#include <SFML/Graphics.hpp>

const int NUMBER_PLATES = 30;
const int NUMBER_BONUSES = 9;
const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);
const float STEP = 3.f;
const int DOODLE_WIDTH = 45;
const int DOODLE_HEIGHT = 45;
const int PLATE_WIDTH = 63;
const int PLATE_HEIGHT = 15;
const int SPRING_WIDTH = 16;
const int SPRING_HEIGHT = 12;
const int HAT_HELICOPTER_WIDTH = 30;
const int HAT_HELICOPTER_HEIGHT = 18;

bool G_noJumps;
bool G_endOfGame;
sf::Vector2f positionBeforeDown;

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
	sf::Sprite * body;
	sf::Texture texture;
	Direction direction;
	Collision collision;
	int deltaHeight;
	DirectionX lastDirectionX;
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
};

struct Game
{
	Doodle hero;
	BonusType actualBonus;
	int actualBonusId;
	int qwerty;
	Plate plate[NUMBER_PLATES];
	Bonus bonus[NUMBER_BONUSES];
};
