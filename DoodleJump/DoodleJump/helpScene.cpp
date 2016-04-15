#include "stdafx.h"
#include "sheet.h"

HelpScene::HelpScene(Assets & assets, sf::View & view)
	:assets(&assets)
	,view(&view)
{	
	goMenuButton = new Button("Back", sf::Vector2f(200.f, 210.f), assets);

	buttonA = new sf::Sprite;
	buttonA->setTexture(assets.BUTTON_A_TEXTURE);
	buttonA->setScale(sf::Vector2f(0.5f, 0.5f));
	buttonA->setPosition(170, 295);

	buttonD = new sf::Sprite;
	buttonD->setTexture(assets.BUTTON_D_TEXTURE);
	buttonD->setScale(sf::Vector2f(0.5f, 0.5f));
	buttonD->setPosition(230, 295);
	
	helpText1.setFont(assets.font);
	helpText1.setCharacterSize(20);
	helpText1.setString("Press");
	helpText1.setStyle(sf::Text::Bold);
	helpText1.setPosition(100.f, 300.f);
	helpText1.setColor(sf::Color(0, 0, 0));

	helpText2.setFont(assets.font);
	helpText2.setCharacterSize(20);
	helpText2.setString("to move Doodle");
	helpText2.setStyle(sf::Text::Bold);
	helpText2.setPosition(290.f, 300.f);
	helpText2.setColor(sf::Color(0, 0, 0));

	background = new sf::Sprite;
	background->setTextureRect(sf::IntRect(0, 0, 550, 700));
	background->setTexture(assets.BACKGROUND_TEXTURE);
	background->setPosition(0, 0);
}

HelpScene::~HelpScene()
{
	delete background;
	delete goMenuButton;
	delete buttonA;
	delete buttonD;
	background = nullptr;
	goMenuButton = nullptr;
	buttonA = nullptr;
	buttonD = nullptr;
}

SGameResult HelpScene::onHelpMenu(sf::RenderWindow & window)
{
	clearResult();

	checkEvents(window);
	render(window);
	window.display();
	return result;
}

void HelpScene::clearResult(void)
{
	result.status = GameStatus::HELP_SCENE;
	result.collision = Collision::NO_COLLISION;
	result.points = 0;
}

void HelpScene::render(sf::RenderWindow & window)
{
	window.clear(sf::Color(255, 255, 255));
	window.draw(*background);
	goMenuButton->draw(window);
	window.draw(helpText1);
	window.draw(helpText2);
	window.draw(*buttonA);
	window.draw(*buttonD);
}

void HelpScene::checkEvents(sf::RenderWindow & window)
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

void HelpScene::checkMouseOnButtons(sf::Vector2i & mousePosition)
{
	goMenuButton->onMouse(mousePosition);
}

void HelpScene::checkMouseClick(sf::RenderWindow & window, sf::Event & event)
{
	if (goMenuButton->onClick(event))
	{
		result.status = GameStatus::START_SCENE;
	}
}
