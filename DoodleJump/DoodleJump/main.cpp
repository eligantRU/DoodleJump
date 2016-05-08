#include "stdafx.h"
#include "sheet.h"

int main()
{
	srand(unsigned(time(nullptr)));
	std::unique_ptr<Game> game = std::make_unique<Game>();
	game->launch();

	return 0;
}
