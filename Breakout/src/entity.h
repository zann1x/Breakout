#pragma once

#include <SFML/Graphics.hpp>

class Entity
{
public:
	virtual const sf::Drawable& getDrawable() const = 0;

	//bool operator==(const Entity& right) { return this == &right; }
};