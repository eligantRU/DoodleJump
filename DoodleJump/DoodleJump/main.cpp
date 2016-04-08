#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "sheet.h"

sf::View view; // TODO: create view in Game & give view to other scenes like a parameter(like Assets)

int main(void)
{
	srand(unsigned(time(NULL)));

	Game * game = new Game();
	game->launch();
	delete game;
	game = NULL;

	return 0;
}
