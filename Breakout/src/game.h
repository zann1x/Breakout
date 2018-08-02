#pragma once

#include <SFML/Graphics.hpp>

#include "math.h"
#include "ball.h"
#include "paddle.h"
#include "game_object.h"

class Game
{
private:
	sf::String m_title;
	unsigned int m_windowWidth;
	unsigned int m_windowHeight;

	sf::RenderWindow m_window;

	Paddle m_paddle;
	Ball m_ball;

	std::vector<GameObject> m_objects;

	bool m_gameIsPaused = false;

private:
	void pollEvents();
	void processInput(float delta);
	bool checkCollission(const sf::RectangleShape& rec1, const sf::RectangleShape& rec2);
	std::tuple<bool, Direction, sf::Vector2f> checkCollision(const sf::CircleShape& circle, const sf::RectangleShape& rec);
	void update(float delta);
	void draw();

public:
	Game(unsigned int width, unsigned int height, const sf::String& title);
	void run();
};