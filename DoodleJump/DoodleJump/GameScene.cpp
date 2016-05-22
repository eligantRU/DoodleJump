#include "stdafx.h"
#include "sheet.h"

GameScene::GameScene(Assets & assets, sf::View & view, SoundHandler & soundHandler)
	:m_assets(assets)
	,m_view(view)
	,m_soundHandler(soundHandler)
{
	m_hero = std::make_unique<Doodle>(m_assets);
	for (auto &bonus : m_bonuses)
	{
		bonus = std::make_unique<Bonus>();
	}	
	for (auto &plate : m_plates)
	{
		plate = std::make_unique<Plate>();
		plate->setType(PlateType::STATIC);
		plate->setTexture(m_assets.PLATE_STATIC_TEXTURE);
	}

	m_actualBonus = BonusType::NO;
	m_view.reset(sf::FloatRect(0.f, 0.f, float(WINDOW_WIDTH), float(WINDOW_HEIGHT)));
	m_hero->setSpeedY(-50.f);
	m_offsetFallBonus.x = 0.f;
	m_offsetFallBonus.y = 0.f;

	m_hole = std::make_unique<sf::Sprite>();
	m_hole->setTextureRect(sf::IntRect(0, 0, 60, 54));
	m_hole->setTexture(m_assets.HOLE_TEXTURE);
	m_holePosition.x = float(rand() % (WINDOW_WIDTH - HOLE_WIDTH));
	m_holePosition.y = -float(rand() % 15000) - 10 * WINDOW_HEIGHT;
	m_hole->setPosition(m_holePosition.x, m_holePosition.y);

	m_scoreNum.setFont(m_assets.ARIAL_FONT);
	m_scoreNum.setCharacterSize(20);
	m_scoreNum.setStyle(sf::Text::Bold);
	m_scoreNum.setColor(sf::Color(0, 0, 0));

	m_background = std::make_unique<sf::Sprite>();
	m_background->setTextureRect(sf::IntRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	m_background->setTexture(m_assets.BACKGROUND_TEXTURE);

	initBonuses();
	resetGame();
}

GameScene::~GameScene()
{

}


SGameResult GameScene::onGameFrame(sf::RenderWindow & window) // TODO: refactoring
{
	if (m_result.status == GameStatus::GAME_OVER_SCENE)
	{
		resetGame();
	}

	if (!m_endOfGame)
	{
		tuneSceneAfterPause(window);

		checkEvents(window);
		update(window);
		window.setView(m_view);
		render(window);
		window.display();

		if (m_isPause)
		{
			m_view.setCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
			m_soundHandler.pauseSound();
			window.setView(m_view);
			m_result.status = GameStatus::PAUSE_SCENE;
		}
		else
		{
			m_result.status = GameStatus::GAME_SCENE;
		}
	}
	else
	{
		m_view.setCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
		window.setView(m_view);
		m_result.status = GameStatus::GAME_OVER_SCENE; 
	}
	return m_result;
}

void GameScene::tuneSceneAfterPause(sf::RenderWindow & window)
{
	if (m_isPause)
	{
		m_isPause = false;
		m_soundHandler.removeSoundFromPause();
		m_view.setCenter(WINDOW_WIDTH / 2, m_background->getPosition().y + WINDOW_HEIGHT / 2);
		window.setView(m_view);
	}
}

void GameScene::update(sf::RenderWindow & window)
{
	(void)window;
	moveDoodle();
	m_hero->correctSkin();
	checkCylinderEffect();
	animateBonus();

	updatePositionBeforeDown();
	sf::Vector2f doodlePosition = m_hero->getPosition();
	if ((m_hero->getSpeedY() <= 0) && (doodlePosition.y <= m_hero->getPositionBeforeDown().y)) // TODO: this code need handler
	{
		m_view.setCenter(WINDOW_WIDTH/2, doodlePosition.y);
		m_background->setPosition(0, doodlePosition.y - WINDOW_HEIGHT / 2);
		m_scoreNum.setPosition(0, doodlePosition.y - WINDOW_HEIGHT / 2);
		++m_points;
	}

	moveBonuses();
	dropUnstablePlates();
	moveDynamicPlates();

	generPlates();

	generBonuses();
	generHole();

	m_endOfGame = checkGameEnd();
}

void GameScene::resetGame()
{
	m_view.reset(sf::FloatRect(0.f, 0.f, float(WINDOW_WIDTH), float(WINDOW_HEIGHT)));
	m_scoreNum.setPosition(0, 0);
	m_endOfGame = false;
	m_points = 0;
	m_actualBonus = BonusType::NO;
	m_animationCounter = 0;
	m_offsetFallBonus.x = 0.f;
	m_offsetFallBonus.y = 0.f;
	m_isLeft = false;
	m_isRight = false;
	m_hero->setDirection(DirectionX::NONE);
	m_hero->setTexture(m_assets.DOODLE_LEFT_TEXTURE);
	m_hero->setPosition(DOODLE_START_POSITION);
	m_hero->setSpeedY(-50.f);
	m_hero->setPositionBeforeDown(m_hero->getPosition());
	m_view.setCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

	for (auto &plate : m_plates)
	{
		plate->setPosition(sf::Vector2f(0, DOODLE_START_POSITION.y));
	}
	m_plates[0]->setPosition(sf::Vector2f((WINDOW_WIDTH - PLATE_WIDTH) / 2, DOODLE_START_POSITION.y - WINDOW_HEIGHT));
	initBonuses();
}

void GameScene::render(sf::RenderWindow & window)
{
	window.clear();
	
	window.draw(*m_background);
	for (auto &plate : m_plates)
	{
		plate->draw(window);
	}
	m_hero->draw(window);
	for (auto &bonus : m_bonuses)
	{
		bonus->draw(window);
	}
	window.draw(*m_hole);
	m_scoreNum.setString("Score: " + std::to_string(m_points));
	window.draw(m_scoreNum);
}

uint64_t GameScene::getScore() const
{
	return m_points;
}
