#include "ball.h"

Ball::Ball(sf::Vector2f velocity, float radius)
	: m_velocity { velocity }, m_size{ radius * 2 }, m_radius{ radius }, m_isAttached{ true }
{
	m_shape.setRadius(m_radius);
	m_shape.setFillColor(m_color);
}

const sf::CircleShape& Ball::getShape() const
{
	return m_shape;
}

bool Ball::isAttached() const 
{ 
	return m_isAttached; 
}

void Ball::setAttached(bool val) 
{ 
	m_isAttached = val; 
}

float Ball::getRadius() const
{
	return m_radius;
}

float Ball::getSize() const 
{ 
	return m_size; 
}

const sf::Vector2f& Ball::getPosition() const
{
	return m_shape.getPosition();
}

void Ball::setPosition(float x, float y)
{
	m_shape.setPosition(sf::Vector2f(x, y));
}

const sf::Vector2f& Ball::getVelocity() const
{
	return m_velocity;
}

void Ball::setXVelocity(float val)
{
	m_velocity.x = val;
}

void Ball::setYVelocity(float val)
{
	m_velocity.y = val;
}