#pragma once

void initialHero(Game & game);

void initialHero(Game & game, sf::View & view)
{
	game.hero.body = new sf::Sprite;
	game.hero.body->setTexture(G_ASSETS.DOODLE_LEFT_TEXTURE);
	game.hero.body->setScale(sf::Vector2f(1.f, 1.f));
	game.hero.body->setPosition(260, 350);  // +DOODLE_HEIGHT -- ����� ����� �� ����
	game.hero.direction.x = NONE;
	game.hero.deltaHeight = 0;
	game.hero.lastDirectionX = LEFT;
	game.qwerty = 0;
	sf::Vector2f doodlePosition = game.hero.body->getPosition();
	g_positionBeforeDown.y = doodlePosition.y;
	view.setCenter(275, doodlePosition.y);
}
