#pragma once

#include "stdafx.h"
#include "sheet.h"

class Record
{
public:
	Record(std::string nickname, uint64_t score, Assets & assets);
	~Record();

	void draw(sf::RenderWindow & window) const;
private:
	uint64_t m_score = 0;
	sf::Sprite m_lineBody;
	sf::Text m_nickname;
};

