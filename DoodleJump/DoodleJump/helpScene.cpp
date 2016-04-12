#include "stdafx.h"
#include "sheet.h"

helpScene::helpScene(Assets * assets, sf::View * view)
{	
	this->assets = assets;
	this->view = view;
	goMenuButton = new sf::Sprite;
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

SGameResult helpScene::onHelpMenu(sf::RenderWindow & window)
{
	clearResult();

	checkEvents(window);
	render(window);
	window.display();
	return result;
}

void helpScene::clearResult(void)
{
	result.status = gameStatus::HELP_SCENE;
	result.collision = Collision::NO_COLLISION;
	result.points = 0;
}

void helpScene::render(sf::RenderWindow & window)
{
	window.clear(sf::Color(255, 255, 255));
	window.draw(*background);
	window.draw(*goMenuButton);
	window.draw(goMenuText);
	window.draw(helpText1);
	window.draw(*buttonA);
	window.draw(*buttonD);
	window.draw(helpText2);
}

void helpScene::checkEvents(sf::RenderWindow & window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		checkMouseOnButtons(sf::Mouse::getPosition(window));
		checkMouseClick(window, event);
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
	}
}

void helpScene::checkMouseOnButtons(sf::Vector2i & mousePosition)
{
	if (((mousePosition.y >= 210) && (mousePosition.y <= 239)
		&& (mousePosition.x >= 200) && (mousePosition.x <= 300)))
	{
		goMenuButton->setTexture(assets->BUTTON_ACTIVE_TEXTURE);
	}
	else
	{
		goMenuButton->setTexture(assets->BUTTON_INACTIVE_TEXTURE);
	}
}


void helpScene::checkMouseClick(sf::RenderWindow & window, sf::Event & event)
{
	if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
	{
		const sf::Vector2i mousePosition(event.mouseButton.x, event.mouseButton.y);
		if (((mousePosition.y >= 210) && (mousePosition.y <= 239)
			&& (mousePosition.x >= 200) && (mousePosition.x <= 300)))
		{
			goMenuButton->setTexture(assets->BUTTON_INACTIVE_TEXTURE);
			result.status = gameStatus::START_SCENE;
		}
	}
}
