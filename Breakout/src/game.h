#pragma once

#include <SFML/Graphics.hpp>

class Game
{
private:
	sf::String m_title;
	unsigned int m_windowWidth;
	unsigned int m_windowHeight;

	sf::RenderWindow m_window;

	sf::RectangleShape m_paddle;
	const float m_paddleSizeX = 100.0f;
	const float m_paddleSizeY = 30.0f;
	const float paddleVelocity = 400.0f;

	std::vector<sf::RectangleShape> m_recs;
	const float m_recSizeX = 100.0f;
	const float m_recSizeY = 30.0f;

private:
	void pollEvents();
	void processInput(float delta);
	void update(float delta);
	void draw();

public:
	Game(unsigned int width, unsigned int height, const sf::String& title);
	void run();
};