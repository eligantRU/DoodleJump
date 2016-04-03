#include "stdafx.h"
#include "GameOverScene.h"

gameOverScene::gameOverScene()
{
	title = new sf::Sprite;
	title->setTextureRect(sf::IntRect(0, 0, 236, 96));
	title->setTexture(assets->GAME_OVER_TITLE_TEXTURE);
	title->setPosition(150, 30);

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

	playAgainButton = new sf::Sprite;
	playAgainButton->setTextureRect(sf::IntRect(0, 0, 104, 29));
	playAgainButton->setTexture(assets->BUTTON_INACTIVE_TEXTURE);
	playAgainButton->setPosition(250, 270);
	playAgainText.setFont(assets->font);
	playAgainText.setCharacterSize(20);
	playAgainText.setString("Play");
	playAgainText.setStyle(sf::Text::Bold);
	playAgainText.setPosition(282.f, 272.f);
	playAgainText.setColor(sf::Color(0, 0, 0));

	lastRecord.setFont(assets->font);
	lastRecord.setCharacterSize(24);
	lastRecord.setStyle(sf::Text::Bold);
	lastRecord.setPosition(190.f, 150.f);
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
	delete playAgainButton;
	background = NULL;
	goMenuButton = NULL;
	playAgainButton = NULL;
}

gameResult gameOverScene::onGameOverMenu(sf::RenderWindow & window, uint64_t & score) // убожество
{
	lastRecord.setString("Your record: " + std::to_string(score));

	window.clear(sf::Color(0, 255, 255));
	window.draw(*background);
	window.draw(*title);
	window.draw(*goMenuButton);
	window.draw(goMenuText);
	window.draw(*playAgainButton);
	window.draw(playAgainText);
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
			playAgainButton->setTexture(assets->BUTTON_ACTIVE_TEXTURE);
		}
		else
		{
			playAgainButton->setTexture(assets->BUTTON_INACTIVE_TEXTURE);
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
				result.gameStatus = statusGame::GAME_SCENE;
				return result;
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
