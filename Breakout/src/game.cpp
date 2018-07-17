#include "game.h"

#include <iostream>
#include <random>

Game::Game(unsigned int width, unsigned int height, const sf::String& title)
	: m_title{ title }, m_windowWidth{ width }, m_windowHeight{ height }, 
		m_window { sf::VideoMode(width, height), title }
{
	// player paddle
	m_paddle.setSize(sf::Vector2f(m_paddleSizeX, m_paddleSizeY));
	m_paddle.setFillColor(sf::Color::Green);
	m_paddle.setPosition(m_windowWidth / 2 - m_paddleSizeX / 2, m_windowHeight - 10.0f - m_paddleSizeY);

	// colored boxes
	std::default_random_engine gen;
	std::uniform_int_distribution<int> dis(0, 255);

	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			sf::RectangleShape rectangle(sf::Vector2f(m_recSizeX, m_recSizeY));
			rectangle.setPosition(x * m_recSizeX, y * m_recSizeY);
			rectangle.setFillColor(sf::Color(dis(gen), dis(gen), dis(gen), 255));
			m_recs.push_back(rectangle);
		}
	}
}

void Game::pollEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_window.close();
	}
}

void Game::processInput(float delta)
{
	pollEvents();

	sf::Vector2f pos = m_paddle.getPosition();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (pos.x > 10.0f)
			m_paddle.setPosition(m_paddle.getPosition().x - paddleVelocity * delta, m_paddle.getPosition().y);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (pos.x < 590.0f - m_paddle.getSize().x)
			m_paddle.setPosition(m_paddle.getPosition().x + paddleVelocity * delta, m_paddle.getPosition().y);
	}
}

void Game::update(float delta)
{

}

void Game::draw()
{
	m_window.clear();

	m_window.draw(m_paddle);
	for (sf::RectangleShape& rec : m_recs)
	{
		m_window.draw(rec);
	}

	m_window.display();
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timer = clock.getElapsedTime();
	sf::Time current = sf::Time::Zero;
	sf::Time last = sf::Time::Zero;
	float delta = 0.0f;
	int frames = 0;

	while (m_window.isOpen())
	{
		current = clock.getElapsedTime();
		delta = (current - last).asSeconds();
		last = current;

		processInput(delta);
		update(delta);
		frames++;

		if ((clock.getElapsedTime() - timer).asSeconds() > 1.0f)
		{
			timer += sf::seconds(1.0f);
			std::cout << frames << "fps" << std::endl;
			frames = 0;
		}

		draw();
	}
}