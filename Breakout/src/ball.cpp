#include "ball.h"

#include "resource_manager.h"

Ball::Ball()
	: m_shape{ 15.0f }, m_velocity{ sf::Vector2f(200.0f, -300.0f) }, m_isAttached{ true }
{
}

const sf::CircleShape& Ball::getDrawable() const
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
	return m_shape.getRadius();
}

float Ball::getSize() const 
{ 
	return m_shape.getRadius() * 2;
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

void Ball::setTexture(const sf::Texture& tex)
{
	m_shape.setTexture(&tex);
}
