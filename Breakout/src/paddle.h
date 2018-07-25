#pragma once

#include <SFML/Graphics.hpp>

class Paddle
{
private:
	sf::RectangleShape m_shape;

	float m_velocity;

public:
	Paddle();

	const sf::RectangleShape& getShape() const;

	const sf::Vector2f& getSize() const;

	const sf::Vector2f& getPosition() const;
	void setPosition(float x, float y);

	float getVelocity() const;
};
