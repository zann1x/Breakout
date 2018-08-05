#pragma once

#include <SFML/Graphics.hpp>

#include "entity.h"

class Paddle : public Entity
{
private:
	sf::RectangleShape m_shape;

	float m_velocity;

public:
	Paddle();

	const sf::RectangleShape& getDrawable() const override;

	const sf::Vector2f& getSize() const;

	const sf::Vector2f& getPosition() const;
	void setPosition(float x, float y);

	float getVelocity() const;

	void setTexture(const sf::Texture& tex);
};
