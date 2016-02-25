#include "stdafx.h"
#include "StartScene.h"

void onStartMenu(sf::RenderWindow & window)
{
	game.assets.BACKGROUND->setPosition(0, 0);

	sf::Text playText;
	playText.setFont(game.assets.font);
	playText.setCharacterSize(20);
	playText.setString("Play");
	playText.setStyle(sf::Text::Bold);
	playText.setPosition(255.f, 225.f);
	playText.setColor(sf::Color(0, 0, 0));

	sf::Text exitText;
	exitText.setFont(game.assets.font);
	exitText.setCharacterSize(20);
	exitText.setString("Exit");
	exitText.setStyle(sf::Text::Bold);
	exitText.setPosition(255.f, 405.f);
	exitText.setColor(sf::Color(0, 0, 0));

	sf::RectangleShape play(sf::Vector2f(120, 50));
	play.setPosition(215.f, 210.f);

	sf::RectangleShape records(sf::Vector2f(120, 50));
	records.setPosition(215.f, 300.f);

	sf::RectangleShape exit(sf::Vector2f(120, 50));
	exit.setPosition(215.f, 390.f);


	window.clear(sf::Color(255, 255, 255));
	window.draw(*game.assets.BACKGROUND);
	window.draw(play);
	window.draw(exit);
	window.draw(playText);
	window.draw(exitText);
	window.display();

	
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

			if (((mousePosition.y >= 210) && (mousePosition.y <= 260)
				&& (mousePosition.x >= 215) && (mousePosition.x <= 335)))
			{
				game.frameFunc = onGameFrame;
			}
		}
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
	}
}