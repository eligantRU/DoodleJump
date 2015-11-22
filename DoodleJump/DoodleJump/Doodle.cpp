void initialHero(Game & game);

void initialHero(Game & game, sf::View & view)
{
	game.hero.body = new sf::Sprite;
	game.hero.body->setTexture(DOODLE_LEFT_TEXTURE);
	game.hero.body->setScale(sf::Vector2f(1.f, 1.f));
	game.hero.body->setPosition(260, 350+DOODLE_HEIGHT);  // +DOODLE_HEIGHT -- этого здесь не было
	game.hero.direction.x = NONE;
	game.hero.deltaHeight = 0;
	sf::Vector2f doodlePosition = game.hero.body->getPosition();
	view.setCenter(275, doodlePosition.y);
}
