#pragma once

#include <SFML/Graphics.hpp>

enum class BlockType
{
	SOLID,
	RED,
	GREEN
};

class GameObject
{
private:
	sf::RectangleShape m_shape;

	bool m_isDestroyable;

public:
	GameObject();

	const sf::RectangleShape& getShape() const;

	void setPosition(float x, float y);

	const sf::Vector2f& getSize() const;

	void setType(BlockType type);

	bool isDestroyable() const;
};
