#pragma once

#include "stdafx.h"
#include "sheet.h"

void onGameFrame(sf::RenderWindow &);

void gameLoop(sf::RenderWindow & window, Game & game);

void resetGame(Game & game, sf::View & view); 

void enterGameLoop(void);

void update(sf::RenderWindow & window, Game & game, sf::View & view);

void initAssets(Game & game);