#include "game_object.h"

#include <random>

std::default_random_engine gen;
std::uniform_int_distribution<int> dis(0, 255);

GameObject::GameObject()
	: m_shape{ sf::Vector2f(100.0f, 30.0f) }
{
	m_shape.setFillColor(sf::Color(dis(gen), dis(gen), dis(gen), 255));
}

const sf::RectangleShape& GameObject::getShape() const
{
	return m_shape;
}

void GameObject::setPosition(float x, float y)
{
	m_shape.setPosition(sf::Vector2f(x, y));
}

const sf::Vector2f& GameObject::getSize() const
{
	return m_shape.getSize();
}