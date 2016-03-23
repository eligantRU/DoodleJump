#pragma once

#include "stdafx.h"
#pragma comment(lib,"Winmm.lib")
#include <string>
#include <functional>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>

#include "bases.h"
#include "audio.h"
#include "assets.h"
#include "bonus.h"
#include "plate.h"	
#include "doodle.h"
#include "pauseScene.h"
#include "gameFrame.h"
#include "gameOverScene.h"
#include "startScene.h"
#include "game.h"

extern Assets * assets; // TODO: узконаправленное решение возникшей проблемы
extern sf::View view; // TODO: узконаправленное решение возникшей проблемы