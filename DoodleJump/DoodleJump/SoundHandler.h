#pragma once

#include "stdafx.h"
#include "sheet.h"

class SoundHandler
{
public:
	SoundHandler();
	~SoundHandler();
	void playSound(sf::SoundBuffer & buffer);
	void pauseSound();
	void removeSoundFromPause();
private:
	sf::Sound m_actualSound;
};