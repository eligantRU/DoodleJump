#include "stdafx.h"
#include "GameOverScene.h"

gameOverScene::gameOverScene()
{
	goMenuButton = new sf::Sprite;
	goMenuButton->setTextureRect(sf::IntRect(0, 0, 104, 29));
	goMenuButton->setTexture(assets->BUTTON_INACTIVE_TEXTURE);
	goMenuButton->setPosition(200, 210);
	goMenuText.setFont(assets->font);
	goMenuText.setCharacterSize(20);
	goMenuText.setString("Menu");
	goMenuText.setStyle(sf::Text::Bold);
	goMenuText.setPosition(232.f, 212.f);
	goMenuText.setColor(sf::Color(0, 0, 0));

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

	lastRecord.setFont(assets->font);
	lastRecord.setCharacterSize(24);
	lastRecord.setStyle(sf::Text::Bold);
	lastRecord.setPosition(150.f, 100.f);
	lastRecord.setColor(sf::Color(0, 0, 0));

	background = new sf::Sprite;
	background->setTextureRect(sf::IntRect(0, 0, 550, 700));
	background->setTexture(assets->BACKGROUND_TEXTURE);
	background->setPosition(0, 0);
}

gameOverScene::~gameOverScene()
{
	delete background;
	delete goMenuButton;
	delete exitButton;
	background = NULL;
	goMenuButton = NULL;
	exitButton = NULL;
}

gameResult gameOverScene::onGameOverMenu(sf::RenderWindow & window, uint64_t & score) // убожество
{
	lastRecord.setString("Your last record: " + std::to_string(score));

	window.clear(sf::Color(255, 255, 255));
	window.draw(*background);
	window.draw(*goMenuButton);
	window.draw(goMenuText);
	window.draw(*exitButton);
	window.draw(exitText);
	window.draw(lastRecord);
	window.display();

	gameResult result;
	sf::Event event;
	while (window.pollEvent(event))
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

		if (((mousePosition.y >= 210) && (mousePosition.y <= 239)
			&& (mousePosition.x >= 200) && (mousePosition.x <= 300)))
		{
			goMenuButton->setTexture(assets->BUTTON_ACTIVE_TEXTURE);
		}
		else
		{
			goMenuButton->setTexture(assets->BUTTON_INACTIVE_TEXTURE);
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
				result.gameStatus = statusGame::START_SCENE;
				return result;
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
	result.gameStatus = statusGame::GAME_OVER_SCENE;
	return result;
}
