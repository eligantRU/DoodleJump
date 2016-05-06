#pragma once

#include "stdafx.h"
#include "sheet.h"

Button::Button(std::string text, sf::Vector2f position, Assets & assets)
	:m_assets(assets)
{
	m_body = std::make_unique<sf::Sprite>();
	setTexture(m_assets.BUTTON_INACTIVE_TEXTURE);
	setPosition(position);
	setText(text);
	m_text.setFont(m_assets.ARIAL_FONT);
	m_text.setCharacterSize(20);
	m_text.setStyle(sf::Text::Bold);
	m_text.setColor(sf::Color(0, 0, 0));

}

Button::~Button()
{

}

void Button::setTexture(sf::Texture & texture)
{
	m_body->setTexture(texture);
}

void Button::setPosition(sf::Vector2f position)	
{
	m_body->setPosition(position);
	setText(m_text.getString());
}

float Button::getStringLengthPx(const std::string & str)
{
	sf::Text text;
	text.setFont(m_assets.ARIAL_FONT);
	text.setCharacterSize(20);
	text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color(0, 0, 0));
	text.setString(str);
	return (text.findCharacterPos(str.length() - 1).x - text.findCharacterPos(0).x);
}

void Button::setText(const std::string & text)
{
	// http://stackoverflow.com/questions/13244928/getting-dimensions-of-text-in-sfml
	// NOTE: getLocalBounds/getGlobalBounds and sf::FloatRect::contains(sf::Vector2f const& point)

	m_text.setString(text);
	float width = m_body->getPosition().x + (BUTTON_WIDTH - getStringLengthPx(text))/2;
	float height = m_body->getPosition().y;
	m_text.setPosition(width, height);
}

void Button::onMouse(sf::Vector2i mousePosition)
{
	auto buttonPosition = m_body->getPosition();
	if (((mousePosition.y >= buttonPosition.y) && (mousePosition.y <= buttonPosition.y + BUTTON_HEIGHT)
		&& (mousePosition.x >= buttonPosition.x) && (mousePosition.x <= buttonPosition.x + BUTTON_WIDTH)))
	{
		setTexture(m_assets.BUTTON_ACTIVE_TEXTURE);
	}
	else
	{
		setTexture(m_assets.BUTTON_INACTIVE_TEXTURE);
	}
}

bool Button::onClick(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
	{
		auto buttonPosition = m_body->getPosition();
		const sf::Vector2i mousePosition(event.mouseButton.x, event.mouseButton.y);
		if (((mousePosition.y >= buttonPosition.y) && (mousePosition.y <= buttonPosition.y + BUTTON_HEIGHT)
			&& (mousePosition.x >= buttonPosition.x) && (mousePosition.x <= buttonPosition.x + BUTTON_WIDTH)))
		{
			setTexture(m_assets.BUTTON_INACTIVE_TEXTURE);
			return true;
		}
	}
	return false;
}

void Button::draw(sf::RenderWindow & window)
{
	window.draw(*m_body);
	window.draw(m_text);
}
