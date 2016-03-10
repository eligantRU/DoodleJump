#include "stdafx.h"
#include "PauseScene.h"

pauseScene::pauseScene()
{
	backButton = new sf::Sprite;
	backButton->setTextureRect(sf::IntRect(0, 0, 104, 29));
	backButton->setTexture(assets->BUTTON_INACTIVE_TEXTURE);
	backButton->setPosition(200, 210);
	backText.setFont(assets->font);
	backText.setCharacterSize(20);
	backText.setString("Back");
	backText.setStyle(sf::Text::Bold);
	backText.setPosition(232.f, 212.f);
	backText.setColor(sf::Color(0, 0, 0));

	exitButton = new sf::Sprite;
	exitButton->setTextureRect(sf::IntRect(0, 0, 104, 29));
	exitButton->setTexture(assets->BUTTON_INACTIVE_TEXTURE);
	exitButton->setPosition(250, 270);
	exitText.setFont(assets->font);
	exitText.setCharacterSize(20);
	exitText.setString("Exit");
	exitText.setStyle(sf::Text::Bold);
	exitText.setPosition(280.f, 272.f);
	exitText.setColor(sf::Color(0, 0, 0));

	background = new sf::Sprite;
	background->setTextureRect(sf::IntRect(0, 0, 550, 700));
	background->setTexture(assets->BACKGROUND_TEXTURE);
	background->setPosition(0, 0);
}

pauseScene::~pauseScene()
{
	delete background;
	delete backButton;
	delete exitButton;
	background = NULL;
	backButton = NULL;
	exitButton = NULL;
}

void pauseScene::onPauseMenu(sf::RenderWindow & window, sf::View & view) 
{
	window.clear(sf::Color(255, 255, 255));

	view.reset(sf::FloatRect(0, 0, 550, 700));
	window.setView(view);

	window.draw(*background);
	window.draw(*backButton);
	window.draw(backText);
	window.draw(*exitButton);
	window.draw(exitText);
	window.display();

	sf::Event event;
	while (window.pollEvent(event))
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

		if (((mousePosition.y >= 210) && (mousePosition.y <= 239)
			&& (mousePosition.x >= 200) && (mousePosition.x <= 300)))
		{
			backButton->setTexture(assets->BUTTON_ACTIVE_TEXTURE);
		}
		else
		{
			backButton->setTexture(assets->BUTTON_INACTIVE_TEXTURE);
		}

		if (((mousePosition.y >= 270) && (mousePosition.y <= 299)
			&& (mousePosition.x >= 250) && (mousePosition.x <= 350)))
		{
			exitButton->setTexture(assets->BUTTON_ACTIVE_TEXTURE);
		}
		else
		{
			exitButton->setTexture(assets->BUTTON_INACTIVE_TEXTURE);
		}

		if (sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		{
			if (((mousePosition.y >= 210) && (mousePosition.y <= 239)
				&& (mousePosition.x >= 200) && (mousePosition.x <= 300)))
			{
				gameScene scene;
				Game * game = &scene;
				
				while (window.isOpen())
				{
					game->onGameFrame(window);
				}
				delete game;
				game = NULL;
			}
			if (((mousePosition.y >= 270) && (mousePosition.y <= 299)
				&& (mousePosition.x >= 250) && (mousePosition.x <= 350)))
			{
				window.close();
			}

		}
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
	}
}
