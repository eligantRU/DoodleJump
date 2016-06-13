#pragma once

#include "stdafx.h"
#include "sheet.h"

struct SAnimationStep // Ask Shambir: why this here? Do I need encapsulate methods?
{
	unsigned m_firstFrameNo = 0;
	unsigned m_lastFrameNo = 0;
	sf::Texture & m_leftTexture;
	sf::Texture & m_rightTexture;
	sf::Vector2f m_leftOffset;
	sf::Vector2f m_rightOffset;

	SAnimationStep operator=(const SAnimationStep animStep)
	{
		m_firstFrameNo = animStep.m_firstFrameNo;
		m_lastFrameNo = animStep.m_lastFrameNo;
		m_leftTexture = animStep.m_leftTexture;
		m_rightTexture = animStep.m_rightTexture;
		m_leftOffset = animStep.m_leftOffset;
		m_rightOffset = animStep.m_rightOffset;
		return *this;
	}

	SAnimationStep(unsigned firstFrameNo, unsigned lastFrameNo, sf::Texture & leftTexture, sf::Texture & rightTexture, sf::Vector2f leftOffset, sf::Vector2f rightOffset)
		:m_firstFrameNo(firstFrameNo)
		, m_lastFrameNo(lastFrameNo)
		, m_leftTexture(leftTexture)
		, m_rightTexture(rightTexture)
		, m_leftOffset(leftOffset)
		, m_rightOffset(rightOffset)
	{

	}

	bool IsActive(unsigned frameNo) const
	{
		return (frameNo >= m_firstFrameNo) && (frameNo <= m_lastFrameNo);
	}
};

class GameScene
{
public:
	GameScene(Assets & assets, sf::View & view, SoundHandler & soundHandler);
	~GameScene();
	SGameResult onGameFrame(sf::RenderWindow & window);
	uint64_t getScore() const;
private:
	void resetGame();
	void tuneSceneAfterPause(sf::RenderWindow & window);
	void render(sf::RenderWindow & window);
	void update(sf::RenderWindow & window);

	void moveDoodle();
	float getDoodleHorizontalOffset();
	float getDoodleVerticalOffset();
	void handleDoodleJumping(float & offsetY);
	void handleDoodleFalling(float & offsetY);
	float checkCollisions();
	void updatePositionBeforeDown();

	void generPlates();
	sf::Vector2f getCenterPlatePosition(int plateID) const;
	void buildPlate(int startingPointPlateID, int plateIndex);
	void dropUnstablePlates();
	void moveDynamicPlates(); 
	int getUppermostPlateID() const;

	void applyAnimationStep(SAnimationStep animationStep);
	void fallBonus(int bonusID);
	void animateBonus();
	void animateSpring();
	void animateTrampoline();
	void animateRocket();
	void animateHatHelicopter();
	void initBonuses();
	void moveBonuses();
	void generBonuses(); 
	void getBonusJumping();
	void buildBonus(BonusType bonusType, int bonusIndex, int plateIndex);

	void generHole();

	void checkEvents(sf::RenderWindow & window);
	void checkKeyboard(sf::Event event);
	void checkKeyPressed(sf::Event event, bool & isNeedUpdate);
	void checkKeyReleased(sf::Event event, bool & isNeedUpdate);
	bool checkGameEnd();
	void checkCylinderEffect();
	Collision checkCollisionPlates();
	Collision checkCollisionBonuses();
	Collision checkCollisionHole();
	int getBonusCollisionID() const;

	void getRecords(unsigned numRecords);

	Assets & m_assets;
	sf::View & m_view;
	SoundHandler & m_soundHandler;

	std::unique_ptr<Doodle> m_hero;
	std::array<std::unique_ptr<Plate>, NUMBER_PLATES> m_plates;
	std::array<std::unique_ptr<Bonus>, NUMBER_BONUSES> m_bonuses;

	std::unique_ptr<sf::Sprite> m_hole;
	std::unique_ptr<sf::Sprite> m_background;

	uint64_t m_points = 0;
	sf::Text m_scoreNum;

	BonusType m_actualBonus;
	sf::Vector2f m_holePosition;
	sf::Vector2f m_offsetFallBonus;
	int m_animationCounter = 0;
	int m_actualBonusId;
	bool m_endOfGame = false;
	bool m_isPause = false;
	bool m_isLeft = false;
	bool m_isRight = false;

	std::vector<Record> m_records;

	SGameResult m_result;
};