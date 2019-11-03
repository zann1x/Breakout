#include "paddle.h"

#include "resource_manager.h"

Paddle::Paddle()
	: m_shape{ sf::Vector2f(100.0f, 20.0f) }, m_velocity{ 250.0f }
{
}

const sf::RectangleShape& Paddle::getDrawable() const
{
	return m_shape;
}

const sf::Vector2f& Paddle::getSize() const
{
	return m_shape.getSize();
}

const sf::Vector2f& Paddle::getPosition() const
{
	return m_shape.getPosition();
}

void Paddle::setPosition(float x, float y)
{
	m_shape.setPosition(x, y);
}

float Paddle::getVelocity() const
{
	return m_velocity;
}

void Paddle::setTexture(const sf::Texture& tex)
{
	m_shape.setTexture(&tex);
}
