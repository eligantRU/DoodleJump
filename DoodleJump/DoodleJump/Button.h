#pragma once

#include "stdafx.h"
#include "sheet.h"

struct Button
{
public:
	Button(std::string text, sf::Vector2f position, Assets & assets);
	~Button();
	void onMouse(sf::Vector2i mousePosition);
	bool onClick(sf::Event event);
	void setText(const std::string & text);
	void setPosition(sf::Vector2f position);
	void setTexture(sf::Texture & texture);
	void draw(sf::RenderWindow & window) const;
private:
	float getStringLengthPx(const std::string & str) const;
	std::unique_ptr<sf::Sprite> m_body;
	sf::Text m_text;
	Assets & m_assets;
};