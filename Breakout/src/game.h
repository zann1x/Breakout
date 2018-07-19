#pragma once

#include <SFML/Graphics.hpp>

enum class Direction
{
	TOP,
	BOTTOM,
	LEFT,
	RIGHT
};

class Game
{
private:
	sf::String m_title;
	unsigned int m_windowWidth;
	unsigned int m_windowHeight;

	sf::RenderWindow m_window;

	sf::RectangleShape m_paddle;
	const float m_paddleSizeX = 100.0f;
	const float m_paddleSizeY = 20.0f;
	const float paddleVelocity = 400.0f;

	sf::CircleShape m_ball;
	const float m_ballRad = 15.0f;
	const float m_ballSize = 2 * m_ballRad;
	float m_ballVelocityX = 300.0f;
	float m_ballVelocityY = -500.0f;
	bool m_ballIsAttached = true;

	std::vector<sf::RectangleShape> m_recs;
	const float m_recSizeX = 100.0f;
	const float m_recSizeY = 30.0f;

	bool m_gameIsPaused = false;

private:
	void pollEvents();
	void processInput(float delta);
	bool checkCollission(sf::RectangleShape& rec1, sf::RectangleShape& rec2);
	std::tuple<bool, Direction, sf::Vector2f> checkCollision(sf::CircleShape& circle, sf::RectangleShape& rec);
	void update(float delta);
	void draw();

public:
	Game(unsigned int width, unsigned int height, const sf::String& title);
	void run();
};