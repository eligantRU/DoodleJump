#include "stdafx.h"
#include "sheet.h"

void initialHero(Game & game, sf::View & view)
{
	game.hero.body = new sf::Sprite;
	game.hero.body->setTexture(g_Assets.DOODLE_LEFT_TEXTURE);
	game.hero.body->setScale(sf::Vector2f(1.f, 1.f));
	game.hero.body->setPosition(260, 350);
	game.hero.direction.x = DirectionX::NONE;
	game.hero.deltaHeight = 0;
	game.hero.lastDirectionX = DirectionX::LEFT;
	game.qwerty = 0; // TODO: do not optimize using this sheet
	sf::Vector2f doodlePosition = game.hero.body->getPosition();
	game.hero.positionBeforeDown.y = doodlePosition.y;
	view.setCenter(275, doodlePosition.y);
}
