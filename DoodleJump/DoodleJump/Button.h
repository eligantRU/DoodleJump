#pragma once

#include "stdafx.h"
#include "sheet.h"

struct Button
{
public:
	Button(std::string text, sf::Vector2f position, Assets & assets);
	void onMouse(sf::Vector2i mousePosition);
	bool onClick(sf::Event event);
	void setText(std::string text);
	void setPosition(sf::Vector2f position);
	void setTexture(sf::Texture & texture);
	void draw(sf::RenderWindow & window);
	float getStringLengthPx(std::string str);
	sf::Vector2f getRelativePosition(void);
	sf::Sprite * body;
	sf::Text text;
private:
	Assets * assets;
};