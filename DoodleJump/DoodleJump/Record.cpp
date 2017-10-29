#include "stdafx.h"
#include "sheet.h"

Record::Record(std::string nickname, uint64_t score, Assets & assets)
	:m_score(score)
{
	m_lineBody.setTexture(assets.RECORD_LINE_TEXTURE);
	m_lineBody.setPosition(WINDOW_WIDTH - RECORD_LINE_WIDTH, -10 * float(m_score));

	m_nickname.setString(nickname);
	m_nickname.setFont(assets.ARIAL_FONT);
	m_nickname.setCharacterSize(20);
	m_nickname.setStyle(sf::Text::Bold);
	m_nickname.setFillColor(sf::Color(0, 0, 0));
	Button bla("", sf::Vector2f(0, 0), assets); // TODO: Why a button calculate a length of string?!
	m_nickname.setPosition(WINDOW_WIDTH - bla.getStringLengthPx(nickname), -10 * float(m_score) + 5);
}

Record::~Record()
{

}

void Record::draw(sf::RenderWindow & window) const
{
	window.draw(m_lineBody);
	window.draw(m_nickname);
}

bool Record::validateNickname(std::string nickname) // TODO: refactoring
{
	if (nickname.length() > 16 || nickname.length() < 4)
	{
		return false;
	}

	unsigned digitCounter = 0;
	auto isDigit = [](const char ch) {
		return (ch >= '0' && ch <= '9') ? true : false;
	};
	for (unsigned i = 0; i < nickname.length(); ++i)
	{
		if (isDigit(nickname[i]))
		{
			++digitCounter;
		}
		if (digitCounter > 2)
		{
			return false;
		}
	}
	return true;
}
