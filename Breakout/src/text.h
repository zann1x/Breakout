#pragma once

#include <SFML/Graphics.hpp>

#include "entity.h"

class Text : public Entity
{
private:
	sf::Text m_text;
	sf::Font m_font;

public:
	Text();

	const sf::Text& getDrawable() const override;

	void setPosition(float x, float y);
	void center(sf::Vector2f globalBoundaries);

	void setString(const std::string& str);

	void setFont(const std::string& str);
	void setFont(const sf::Font& font);

	const sf::FloatRect getLocalBounds() const;
};
