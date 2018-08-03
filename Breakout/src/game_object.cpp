#include "game_object.h"

#include <random>

#include "resource_manager.h"

std::default_random_engine gen;
std::uniform_int_distribution<int> dis(0, 255);

GameObject::GameObject()
	: m_shape{ sf::Vector2f(100.0f, 30.0f) }
{
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
	case BlockType::TYPE0:
		m_isDestroyable = false;
		m_shape.setTexture(&ResourceManager::getTexture("solid_block"));
		break;
	case BlockType::TYPE1:
		m_isDestroyable = true;
		m_shape.setTexture(&ResourceManager::getTexture("block_1"));
		break;
	case BlockType::TYPE2:
		m_isDestroyable = true;
		m_shape.setTexture(&ResourceManager::getTexture("block_2"));
		break;
	}
}

bool GameObject::isDestroyable() const
{
	return m_isDestroyable;
}
