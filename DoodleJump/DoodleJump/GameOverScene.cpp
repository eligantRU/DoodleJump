#include "stdafx.h"
#include "sheet.h"

GameOverScene::GameOverScene(Assets & assets, sf::View & view, SoundHandler & soundHandler, std::function<uint64_t()> getter)
	:m_assets(assets)
	,m_view(view)
	,m_soundHandler(soundHandler)
	,m_getter(getter)
{
	m_title = std::make_unique<sf::Sprite>(sf::Sprite());
	m_title->setTextureRect(sf::IntRect(0, 0, 236, 96));
	m_title->setTexture(m_assets.GAME_OVER_TITLE_TEXTURE);
	m_title->setPosition(150.f, 30.f);

	m_goMenuButton = std::make_unique<Button>("Menu", sf::Vector2f(232.f, 182.f), m_assets);
	m_playAgainButton = std::make_unique<Button>("Play", sf::Vector2f(250.f, 240.f), m_assets);

	m_lastRecord.setFont(m_assets.ARIAL_FONT);
	m_lastRecord.setCharacterSize(24);
	m_lastRecord.setStyle(sf::Text::Bold);
	m_lastRecord.setPosition(190.f, 140.f);
	m_lastRecord.setColor(sf::Color(0, 0, 0));

	m_background = std::make_unique<sf::Sprite>(sf::Sprite());
	m_background->setTextureRect(sf::IntRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	m_background->setTexture(m_assets.BACKGROUND_TEXTURE);
	m_background->setPosition(0, 0);
}

GameOverScene::~GameOverScene()
{

}

SGameResult GameOverScene::onGameOverMenu(sf::RenderWindow & window)
{
	m_score = m_getter();
	m_result.status = GameStatus::GAME_OVER_SCENE;
	m_lastRecord.setString("Your record: " + std::to_string(m_score));
	
	render(window);
	window.display();

	checkEvents(window);
	return m_result;
}

void GameOverScene::render(sf::RenderWindow & window) const
{
	window.clear();
	window.draw(*m_background);
	window.draw(*m_title);
	m_goMenuButton->draw(window);
	m_playAgainButton->draw(window);
	window.draw(m_lastRecord);
}

void GameOverScene::checkEvents(sf::RenderWindow & window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		checkMouseOnButtons(sf::Mouse::getPosition(window));
		checkMouseClick(event);
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
	}

	if (m_result.status != GameStatus::GAME_OVER_SCENE)
	{
		saveRecord();
	}
}

void GameOverScene::checkMouseOnButtons(sf::Vector2i mousePosition)
{
	m_goMenuButton->onMouse(mousePosition);
	m_playAgainButton->onMouse(mousePosition);
}

void GameOverScene::checkMouseClick(sf::Event & event)
{
	if (m_goMenuButton->onClick(event))
	{
		m_result.status = GameStatus::START_SCENE;
	}

	if (m_playAgainButton->onClick(event))
	{
		m_result.status = GameStatus::GAME_SCENE;
	}
}

void GameOverScene::saveRecord()
{
	system("cls");
	std::cout << "Write your nickname: ";
	std::string nickname;
	std::cin >> nickname;
	system("cls");

	MasterAPI api(API_HOST);
	sf::Http::Response::Status status = api.sendRequest("index.php/record/" + nickname + "/" + std::to_string(m_score), "POST");

	if (status != sf::Http::Response::Ok)
	{
		std::cout << "Error: " << status << std::endl;
		MessageBoxA(nullptr, "Error server connection\n Code: " + status, "Error", MB_ICONERROR | MB_OK);
		assert(0);
	}
}
