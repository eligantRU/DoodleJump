#include "stdafx.h"
#include "sheet.h"

int main(void)
{
	srand(unsigned(time(NULL)));

	Game * game = new Game();
	game->launch();
	delete game;
	game = NULL;
	
	return 0;
}
