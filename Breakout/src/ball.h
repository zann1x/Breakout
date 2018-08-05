#pragma once

#include <SFML/Graphics.hpp>

#include "entity.h"

class Ball : public Entity
{
private:
	sf::CircleShape m_shape;

	sf::Vector2f m_velocity;

	bool m_isAttached;

public:
	Ball();

	const sf::CircleShape& getDrawable() const override;

	bool isAttached() const;
	void setAttached(bool val);

	float getRadius() const;
	float getSize() const;

	const sf::Vector2f& getPosition() const;
	void setPosition(float x, float y);

	const sf::Vector2f& getVelocity() const;
	void setXVelocity(float val);
	void setYVelocity(float val);

	void setTexture(const sf::Texture& tex);
};
