#include "stdafx.h"
#include "PauseScene.h"

void onPauseMenu(sf::RenderWindow & window) // убожество
{
	kostil = game.assets.BACKGROUND->getPosition();

	sf::Text backText;
	backText.setFont(game.assets.font);
	backText.setCharacterSize(20);
	backText.setString("Back");
	backText.setStyle(sf::Text::Bold);
	backText.setPosition(255.f, kostil.y + 225.f);
	backText.setColor(sf::Color(0, 0, 0));

	sf::RectangleShape back(sf::Vector2f(120, 50));
	back.setPosition(215.f, kostil.y + 210.f);


	window.clear(sf::Color(255, 255, 255));

	view.setCenter(275, kostil.y + 350);
	window.setView(view);

	window.draw(*game.assets.BACKGROUND);
	window.draw(back);
	window.draw(backText);
	window.display();

	sf::Event event;
	while (window.pollEvent(event))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			game.frameFunc = onGameFrame;
		}
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
