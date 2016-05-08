#include "stdafx.h"
#include "sheet.h"

SoundHandler::SoundHandler()
{

}

SoundHandler::~SoundHandler()
{

}

void SoundHandler::playSound(sf::SoundBuffer & buffer)
{
	m_actualSound.setBuffer(buffer);
	m_actualSound.play();
}

void SoundHandler::pauseSound()
{
	m_actualSound.pause();
}

void SoundHandler::removeSoundFromPause()
{
	if (m_actualSound.getStatus() == sf::SoundSource::Status::Paused)
	{
		m_actualSound.play();
	}
}
