#pragma once

#include <SFML/Graphics.hpp>

#include "math.h"
#include "entity.h"
#include "ball.h"
#include "paddle.h"
#include "game_object.h"
#include "text.h"

enum class GameState
{
	START,
	PLAY,
	PAUSE,
	OVER
};

class Game
{
private:
	sf::String m_title;
	unsigned int m_windowWidth;
	unsigned int m_windowHeight;

	GameState m_state;

	sf::RenderWindow m_window;

	Paddle m_paddle;
	Ball m_ball;

	std::vector<Entity*> m_entities;
	std::vector<GameObject> m_objects;

	bool m_gameIsPaused = false;

private:
	void pollEvents();
	void processInput(float delta);
	bool checkCollision(const sf::RectangleShape& rec1, const sf::RectangleShape& rec2);
	std::tuple<bool, Direction, sf::Vector2f> checkCollision(const sf::CircleShape& circle, const sf::RectangleShape& rec);
	enum collisionInfoKey{ HasCollKey, DirKey, PosKey };
	void update(float delta);
	void draw();

public:
	Game(unsigned int width, unsigned int height, const sf::String& title);
	~Game();

	void run();
};