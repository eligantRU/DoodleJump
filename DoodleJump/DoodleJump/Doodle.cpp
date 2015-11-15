void initialHero(Game & game);

void initialHero(Game & game)
{
	game.hero.body = new sf::Sprite;
	game.hero.body->setTexture(DOODLE_LEFT_TEXTURE);
	game.hero.body->setScale(sf::Vector2f(1.f, 1.f));
	game.hero.body->setPosition(260, 70);
	game.hero.direction.x = NONE;
	game.hero.deltaHeight = 0;
}
