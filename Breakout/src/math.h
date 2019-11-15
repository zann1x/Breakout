#pragma once

#include <SFML/Graphics.hpp>

enum class Direction
{
	TOP,
	BOTTOM,
	LEFT,
	RIGHT
};

const sf::Vector2f dirVecs[] = {
	sf::Vector2f(0,  1),
	sf::Vector2f(0, -1),
	sf::Vector2f(-1,  0),
	sf::Vector2f(1,  0)
};

sf::Vector2f clamp(sf::Vector2f val, sf::Vector2f low, sf::Vector2f high);
Direction getDirection(const sf::Vector2f& vec);
