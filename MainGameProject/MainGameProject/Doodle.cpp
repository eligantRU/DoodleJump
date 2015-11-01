void initialHero(Game & game);

void initialHero(Game & game)
{
	Doodle & hero = game.hero;

	hero.body = new sf::RectangleShape(sf::Vector2f(40, 70));
	hero.body->setFillColor(sf::Color(0, 8 * 16 + 4, 16 + 7));
	hero.body->setPosition(260, 70);
	hero.direction.x = NONE;
	hero.deltaHeight = 0;
}
