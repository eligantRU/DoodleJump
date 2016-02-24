#include "stdafx.h"
#include "GameOverScene.h"


void onGameOverMenu(sf::RenderWindow & window)
{
	game.assets.BACKGROUND->setPosition(0, 0);

	sf::Text menuText;
	menuText.setFont(game.assets.font);
	menuText.setCharacterSize(20);
	menuText.setString("Menu");
	menuText.setStyle(sf::Text::Bold);
	menuText.setPosition(255.f, 225.f);
	menuText.setColor(sf::Color(0, 0, 0));

	sf::Text recordsText;
	recordsText.setFont(game.assets.font);
	recordsText.setCharacterSize(20);
	recordsText.setString("Records");
	recordsText.setStyle(sf::Text::Bold);
	recordsText.setPosition(240.f, 315.f);
	recordsText.setColor(sf::Color(0, 0, 0));

	sf::RectangleShape menu(sf::Vector2f(120, 50));
	menu.setPosition(215.f, 210.f);

	sf::RectangleShape records(sf::Vector2f(120, 50));
	records.setPosition(215.f, 300.f);


	window.clear(sf::Color(255, 255, 255));
	window.draw(*game.assets.BACKGROUND);
	window.draw(menu);
	window.draw(records);
	window.draw(recordsText);
	window.draw(menuText);
	window.display();

	sf::Event event;
	if (window.pollEvent(event) && sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

		if (((mousePosition.y >= 210) && (mousePosition.y <= 260)
			&& (mousePosition.x >= 215) && (mousePosition.x <= 335)))
		{
			game.frameFunc = onStartMenu;
		}

		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
	}
}
