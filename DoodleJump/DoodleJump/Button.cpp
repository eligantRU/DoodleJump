#pragma once

#include "stdafx.h"
#include "sheet.h"

Button::Button(std::string text, sf::Vector2f position, Assets & assets)
	:assets(&assets)
{
	body = new sf::Sprite();
	setTexture(assets.BUTTON_INACTIVE_TEXTURE);
	setPosition(position);
	setText(text);
	this->text.setFont(assets.font);
	this->text.setCharacterSize(20);
	this->text.setStyle(sf::Text::Bold);
	this->text.setColor(sf::Color(0, 0, 0));

}

void Button::setTexture(sf::Texture & texture)
{
	body->setTexture(texture);
}

void Button::setPosition(sf::Vector2f position)	
{
	body->setPosition(position);
	setText(text.getString());
}

float Button::getStringLengthPx(std::string str)
{
	sf::Text text;
	text.setFont(assets->font);
	text.setCharacterSize(20);
	text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color(0, 0, 0));
	text.setString(str);
	return (text.findCharacterPos(str.length() - 1).x - text.findCharacterPos(0).x);
}

void Button::setText(std::string text)
{
	// http://stackoverflow.com/questions/13244928/getting-dimensions-of-text-in-sfml
	// NOTE: getLocalBounds/getGlobalBounds and sf::FloatRect::contains(sf::Vector2f const& point)

	this->text.setString(text);
	float width = body->getPosition().x + (BUTTON_WIDTH - getStringLengthPx(text))/2;
	float height = body->getPosition().y;
	this->text.setPosition(width, height);
}

void Button::onMouse(sf::Vector2i mousePosition)
{
	auto buttonPosition = body->getPosition();
	if (((mousePosition.y >= buttonPosition.y) && (mousePosition.y <= buttonPosition.y + BUTTON_HEIGHT)
		&& (mousePosition.x >= buttonPosition.x) && (mousePosition.x <= buttonPosition.x + BUTTON_WIDTH)))
	{
		setTexture(assets->BUTTON_ACTIVE_TEXTURE);
	}
	else
	{
		setTexture(assets->BUTTON_INACTIVE_TEXTURE);
	}
}

bool Button::onClick(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
	{
		auto buttonPosition = body->getPosition();
		const sf::Vector2i mousePosition(event.mouseButton.x, event.mouseButton.y);
		if (((mousePosition.y >= buttonPosition.y) && (mousePosition.y <= buttonPosition.y + BUTTON_HEIGHT)
			&& (mousePosition.x >= buttonPosition.x) && (mousePosition.x <= buttonPosition.x + BUTTON_WIDTH)))
		{
			setTexture(assets->BUTTON_INACTIVE_TEXTURE);
			return true;
		}
	}
	return false;
}

void Button::draw(sf::RenderWindow & window)
{
	window.draw(*body);
	window.draw(text);
}