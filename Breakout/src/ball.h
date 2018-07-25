#pragma once

#include <SFML/Graphics.hpp>

class Ball
{
private:
	sf::CircleShape m_shape;

	sf::Vector2f m_velocity;
	float m_size;

	float m_radius;
	sf::Color m_color = sf::Color(sf::Color::Magenta);

	bool m_isAttached;

public:
	Ball(sf::Vector2f velocity, float radius);

	const sf::CircleShape& getShape() const;

	bool isAttached() const;
	void setAttached(bool val);

	float getRadius() const;
	float getSize() const;

	const sf::Vector2f& getPosition() const;
	void setPosition(float x, float y);

	const sf::Vector2f& getVelocity() const;
	void setXVelocity(float val);
	void setYVelocity(float val);
};
