#pragma once

#include "stdafx.h"
#include "sheet.h"

struct GameScene
{
public:
	GameScene(Assets & assets, sf::View & view);
	~GameScene();
	SGameResult onGameFrame(sf::RenderWindow & window);
	uint64_t getScore(void);
private:
	void render(sf::RenderWindow & window);
	void moveDoodle(void);
	void moveDoodleHorizontal(float & positionX);
	void moveDoodleVertical(float & positionY);
	void animateBonus(void);
	void animateSpring(void);
	void animateTrampoline(void);
	void animateRocket(void);
	void animateHatHelicopter(void);
	void initBonuses(void);
	void moveBonuses(void);
	void generPlates(void);
	void generBonuses(void);
	void update(sf::RenderWindow & window);
	void checkEvents(sf::RenderWindow & window);
	void checkKeyboard(sf::Event event); 
	void checkKeyPressed(sf::Event event, bool & isNeedUpdate);
	void checkKeyRealesed(sf::Event event, bool & isNeedUpdate);
	float checkDoodleFall(void);
	void dropUnstablePlates(void);
	void generHole(void);
	bool checkGameEnd(void);
	void checkCylinderEffect(sf::Vector2f & doodlePosition);
	Collision checkCollisionPlate(sf::Vector2f & doodlePosition, sf::Vector2f platePosition[NUMBER_PLATES]);
	Collision checkCollisionBonus(sf::Vector2f & doodlePosition, sf::Vector2f bonusPosition[NUMBER_PLATES]);
	Collision checkCollisionHole(sf::Vector2f & doodlePosition);
	void buildBonus(BonusType bonusType, int bonusIndex, sf::Vector2f platePosition, int plateIndex);
	void moveDynamicPlates(void);
	void resetGame(void);

	Assets * m_assets;
	sf::View * m_view;

	Doodle * m_hero;
	Bonus * m_bonuses[NUMBER_BONUSES];
	Plate * m_plates[NUMBER_PLATES];
	// Enemy * m_enemy[NUMBER_ENEMY];
	sf::Sprite * m_hole;

	uint64_t m_points = 0;
	sf::Text m_scoreNum;

	BonusType m_actualBonus;
	int m_animationCounter = 0;
	int m_actualBonusId;
	sf::Vector2f m_holePosition;
	int m_unstablePlatesCounter = 0;
	sf::Sprite * m_background;
	SGameResult m_result;
	sf::Vector2f m_offsetFallBonus;
	bool m_endOfGame = false;
	bool m_isPause = false;
	bool m_isLeft = false;
	bool m_isRight = false;
};