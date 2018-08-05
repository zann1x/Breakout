#include "text.h"

Text::Text()
{
	m_text.setFillColor(sf::Color::White);
}

const sf::Text& Text::getDrawable() const
{
	return m_text;
}

void Text::setPosition(float x, float y)
{
	m_text.setPosition(x, y);
}

void Text::center(sf::Vector2f globalBoundaries)
{
	setPosition(globalBoundaries.x / 2 - getLocalBounds().width / 2, globalBoundaries.y / 2);
}

void Text::setString(const std::string& str)
{
	m_text.setString(str);
}

void Text::setFont(const std::string& font)
{
	m_font.loadFromFile(font);
	setFont(m_font);
}

void Text::setFont(const sf::Font& font)
{
	m_text.setFont(font);
}

const sf::FloatRect Text::getLocalBounds() const
{
	return m_text.getLocalBounds();
}
