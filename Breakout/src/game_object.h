#pragma once

#include <SFML/Graphics.hpp>

class GameObject
{
private:
	sf::RectangleShape m_shape;

public:
	GameObject();

	const sf::RectangleShape& getShape() const;

	void setPosition(float x, float y);

	const sf::Vector2f& getSize() const;
};