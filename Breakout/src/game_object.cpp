#include "game_object.h"

#include <random>

std::default_random_engine gen;
std::uniform_int_distribution<int> dis(0, 255);

GameObject::GameObject()
	: m_shape{ sf::Vector2f(100.0f, 30.0f) }
{
	m_shape.setOutlineColor(sf::Color::Black);
	m_shape.setOutlineThickness(-1.0f);
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

void GameObject::setType(BlockType type)
{
	switch (type)
	{
	case BlockType::SOLID:
		m_isDestroyable = false;
		m_shape.setFillColor(sf::Color(160.0f, 160.0f, 160.0f, 255.0f));
		break;
	case BlockType::RED:
		m_isDestroyable = true;
		m_shape.setFillColor(sf::Color(255.0f, 0.0f, 0.0f, 255.0f));
		break;
	case BlockType::GREEN:
		m_isDestroyable = true;
		m_shape.setFillColor(sf::Color(0.0f, 255.0f, 0.0f, 255.0f));
		break;
	}
}

bool GameObject::isDestroyable() const
{
	return m_isDestroyable;
}
