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
	m_nickname.setColor(sf::Color(0, 0, 0));
	m_nickname.setPosition(WINDOW_WIDTH - 75, -10 * float(m_score) + 5);
}

Record::~Record()
{

}

void Record::draw(sf::RenderWindow & window) const
{
	window.draw(m_lineBody);
	window.draw(m_nickname);
}
