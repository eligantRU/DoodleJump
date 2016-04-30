#include "stdafx.h"
#include "sheet.h"

int main(void)
{
	srand(unsigned(time(nullptr)));
	Game * game = new Game();
	game->launch();
	delete game;
	game = nullptr;

	return 0;
}