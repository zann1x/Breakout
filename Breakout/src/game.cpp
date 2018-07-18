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

	// ball
	m_ball.setRadius(m_ballRad);
	m_ball.setFillColor(sf::Color::Magenta);
	m_ball.setPosition(400.0f, 400.0f);

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

	if (m_ballIsAttached)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			m_ballIsAttached = false;
	}
	if (!m_gameIsPaused)
	{
		const sf::Vector2f paddlePos = m_paddle.getPosition();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (paddlePos.x > 10.0f)
				m_paddle.setPosition(paddlePos.x - paddleVelocity * delta, paddlePos.y);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (paddlePos.x < 590.0f - m_paddle.getSize().x)
				m_paddle.setPosition(paddlePos.x + paddleVelocity * delta, paddlePos.y);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			m_gameIsPaused = true;
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			m_gameIsPaused = false;
	}
}

bool Game::checkCollission(sf::CircleShape& ball, sf::RectangleShape& obj)
{
	sf::Vector2f ballPosTopRight = sf::Vector2f();

	bool collisionX = ball.getPosition().x + m_ballSize >= obj.getPosition().x && ball.getPosition().x <= obj.getPosition().x + obj.getSize().x;
	bool collisionY = ball.getPosition().y <= obj.getPosition().y + obj.getSize().y && ball.getPosition().y + m_ballSize >= obj.getPosition().y;

	return collisionX && collisionY;
}

void Game::update(float delta)
{
	if (m_ballIsAttached)
	{
		m_ball.setPosition(m_paddle.getPosition().x + m_paddleSizeX / 2 - m_ballRad, m_paddle.getPosition().y - m_ballSize);
	}
	else
	{
		const sf::Vector2f ballPos = m_ball.getPosition();
		m_ball.setPosition(ballPos.x + m_ballVelocityX * delta, ballPos.y + m_ballVelocityY * delta);

		// check window boundaries for ball
		if (ballPos.x + m_ballVelocityX * delta + m_ballSize > m_windowWidth || ballPos.x + m_ballVelocityX * delta < 0.0f)
			m_ballVelocityX = -m_ballVelocityX;
		if (ballPos.y + m_ballVelocityY * delta < 0.0f)
			m_ballVelocityY = -m_ballVelocityY;
		if (ballPos.y + m_ballVelocityY * delta - m_ballSize > m_windowHeight)
		{
			m_ballIsAttached = true;
			m_ballVelocityY = -m_ballVelocityY;
		}

		// check if ball has contact with player paddle
		// bug noticed, but i think it is too cool to not leave it in the game as a feature
		if (checkCollission(m_ball, m_paddle))
		{
			m_ballVelocityY = -1 * abs(m_ballVelocityY);
		}

		// check if ball hit a box
		const sf::Vector2f ballPosTopRight = sf::Vector2f(ballPos.x + m_ballSize, ballPos.y);
		const sf::Vector2f ballPosBottomLeft = sf::Vector2f(ballPos.x, ballPos.y + m_ballSize);
		const sf::Vector2f ballPosBottomRight = sf::Vector2f(ballPos.x + m_ballSize, ballPos.y + m_ballSize);

		bool hit = false;
		for (int i = 0; i < m_recs.size(); )
		{	
			const sf::Vector2f recPos = m_recs.at(i).getPosition();
			const sf::Vector2f recPosTopRight = sf::Vector2f(recPos.x + m_recSizeX, recPos.y);
			const sf::Vector2f recPosBottomLeft = sf::Vector2f(recPos.x, recPos.y + m_recSizeY);
			const sf::Vector2f recPosBottomRight = sf::Vector2f(recPos.x + m_recSizeX, recPos.y + m_recSizeY);

			// ball hit box from bottom
			if (ballPosTopRight.x > recPosBottomLeft.x && ballPos.x < recPosBottomRight.x && ballPos.y < recPosBottomLeft.y && ballPosBottomLeft.y > recPos.y)
			{
				m_ballVelocityY = abs(m_ballVelocityY);
				hit = true;
			}
			// ball hit box from top
			else if (ballPosBottomLeft.x < recPosTopRight.x && ballPosBottomRight.x > recPos.x && ballPosBottomLeft.y > recPos.y && ballPos.y < recPosBottomLeft.y)
			{
				m_ballVelocityY = -1 * abs(m_ballVelocityY);
				hit = true;
			}
			// ball hit box from left side
			else if (ballPosTopRight.x > recPos.x && ballPos.x < recPosTopRight.x && ballPosTopRight.y < recPosBottomLeft.y && ballPosBottomRight.y > recPos.y)
			{
				m_ballVelocityX = -1 * abs(m_ballVelocityX);
				hit = true;
			}
			// ball hit box from right side
			else if (ballPos.x < recPosTopRight.x && ballPosTopRight.x > recPos.x && ballPos.y < recPosBottomRight.y && ballPosBottomLeft.y > recPosTopRight.y)
			{
				m_ballVelocityX = abs(m_ballVelocityX);
				hit = true;
			}

			if (hit)
			{
				m_recs.erase(m_recs.begin() + i);
				hit = false;
			}
			else 
			{
				i++;
			}
		}
	}
}

void Game::draw()
{
	m_window.clear();

	for (sf::RectangleShape& rec : m_recs)
		m_window.draw(rec);
	m_window.draw(m_paddle);
	m_window.draw(m_ball);

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
		if (!m_gameIsPaused)
		{
			update(delta);
			draw();
		}
		frames++;

		if ((clock.getElapsedTime() - timer).asSeconds() > 1.0f)
		{
			timer += sf::seconds(1.0f);
			std::cout << frames << "fps" << std::endl;
			frames = 0;
		}
	}
}