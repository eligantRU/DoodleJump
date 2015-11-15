void initialHero(Game & game);

void initialHero(Game & game)
{
	if (!game.hero.texture.loadFromFile("images/Doodle45_45Left.png"))
	{
		printf("Error loaded file");
	}
	game.hero.texture.setSmooth(true);

	

	game.hero.body = new sf::Sprite;
	game.hero.body->setTexture(game.hero.texture);
  //  game.hero.body->setTextureRect(sf::IntRect(0, 0, DOODLE_WIDTH, 70));
	game.hero.body->setScale(sf::Vector2f(1.f, 1.f));
	game.hero.body->setPosition(260, 70);
	game.hero.direction.x = NONE;
	game.hero.deltaHeight = 0;
}
