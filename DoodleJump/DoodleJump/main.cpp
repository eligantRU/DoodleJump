#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "sheet.h"

Assets * assets = new Assets(); // TODO: ���������������� ������� ��������� ��������
sf::View view; // TODO: ���������������� ������� ��������� ��������

int main(void)
{
	srand(unsigned(time(NULL)));

	Game * game = new Game();
	game->launch();
	delete game;
	game = NULL;

	return 0;
}
