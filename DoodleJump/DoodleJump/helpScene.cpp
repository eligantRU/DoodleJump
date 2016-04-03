#include "stdafx.h"
#include "helpScene.h"

helpScene::helpScene()
{	
	goMenuButton = new sf::Sprite;
	goMenuButton->setTextureRect(sf::IntRect(0, 0, 104, 29));
	goMenuButton->setTexture(assets->BUTTON_INACTIVE_TEXTURE);
	goMenuButton->setPosition(200, 210);
	goMenuText.setFont(assets->font);
	goMenuText.setCharacterSize(20);
	goMenuText.setString("back");
	goMenuText.setStyle(sf::Text::Bold);
	goMenuText.setPosition(232.f, 212.f);
	goMenuText.setColor(sf::Color(0, 0, 0));

	buttonA = new sf::Sprite;
	buttonA->setTexture(assets->BUTTON_A_TEXTURE);
	buttonA->setScale(sf::Vector2f(0.5f, 0.5f));
	buttonA->setPosition(170, 295);

	buttonD = new sf::Sprite;
	buttonD->setTexture(assets->BUTTON_D_TEXTURE);
	buttonD->setScale(sf::Vector2f(0.5f, 0.5f));
	buttonD->setPosition(230, 295);
	
	helpText1.setFont(assets->font);
	helpText1.setCharacterSize(20);
	helpText1.setString("Press");
	helpText1.setStyle(sf::Text::Bold);
	helpText1.setPosition(100.f, 300.f);
	helpText1.setColor(sf::Color(0, 0, 0));

	helpText2.setFont(assets->font);
	helpText2.setCharacterSize(20);
	helpText2.setString("to move Doodle");
	helpText2.setStyle(sf::Text::Bold);
	helpText2.setPosition(290.f, 300.f);
	helpText2.setColor(sf::Color(0, 0, 0));

	background = new sf::Sprite;
	background->setTextureRect(sf::IntRect(0, 0, 550, 700));
	background->setTexture(assets->BACKGROUND_TEXTURE);
	background->setPosition(0, 0);
}

helpScene::~helpScene()
{
	delete background;
	delete goMenuButton;
	delete buttonA;
	delete buttonD;
	background = NULL;
	goMenuButton = NULL;
	buttonA = NULL;
	buttonD = NULL;
}

gameResult helpScene::onHelpMenu(sf::RenderWindow & window) // убожество
{
	window.clear(sf::Color(0, 255, 255));
	window.draw(*background);
	window.draw(*goMenuButton);
	window.draw(goMenuText);
	window.draw(helpText1);
	window.draw(*buttonA);
	window.draw(*buttonD);
	window.draw(helpText2);
	window.display();

	gameResult result;
	result.collision = Collision::NO_COLLISION;
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

		if (sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		{
			if (((mousePosition.y >= 210) && (mousePosition.y <= 239)
				&& (mousePosition.x >= 200) && (mousePosition.x <= 300)))
			{
				result.gameStatus = statusGame::START_SCENE;
				return result;
			}
		}
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
	}
	result.gameStatus = statusGame::HELP_SCENE;
	return result;
}
