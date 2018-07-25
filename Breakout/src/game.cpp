#include "game.h"

#include <iostream>
#include <random>
#include <algorithm>
#include <tuple>

Game::Game(unsigned int width, unsigned int height, const sf::String& title)
	: m_title{ title }, m_windowWidth{ width }, m_windowHeight{ height }, 
		m_window { sf::VideoMode(width, height), title },
		m_ball{ sf::Vector2f(300.0f, -500.0f), 15.0f }
{
	// player paddle
	m_paddle.setSize(sf::Vector2f(m_paddleSizeX, m_paddleSizeY));
	m_paddle.setFillColor(sf::Color::Green);
	m_paddle.setPosition(m_windowWidth / 2 - m_paddleSizeX / 2, m_windowHeight - 10.0f - m_paddleSizeY);

	/*
	// ball
	m_ball.setRadius(m_ballRad);
	m_ball.setFillColor(sf::Color::Magenta);
	m_ball.setPosition(400.0f, 400.0f);
	*/

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

	if (m_ball.isAttached())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			m_ball.setAttached(false);
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

bool Game::checkCollission(const sf::RectangleShape& rec1, const sf::RectangleShape& rec2)
{
	bool collisionX = rec1.getPosition().x + m_ball.getSize() >= rec2.getPosition().x && rec1.getPosition().x <= rec2.getPosition().x + rec2.getSize().x;
	bool collisionY = rec1.getPosition().y <= rec2.getPosition().y + rec2.getSize().y && rec1.getPosition().y + m_ball.getSize() >= rec2.getPosition().y;

	return collisionX && collisionY;
}

std::tuple<bool, Direction, sf::Vector2f> Game::checkCollision(const sf::CircleShape& circle, const sf::RectangleShape& rec)
{
	const sf::Vector2f circleCenter = sf::Vector2f(circle.getPosition().x + circle.getRadius(), circle.getPosition().y + circle.getRadius());
	const sf::Vector2f recHalfSize = sf::Vector2f(rec.getSize().x / 2, rec.getSize().y / 2);
	const sf::Vector2f recCenter = sf::Vector2f(rec.getPosition().x + recHalfSize.x, rec.getPosition().y + recHalfSize.y);

	const sf::Vector2f centerDiff = circleCenter - recCenter;
	const sf::Vector2f clamped = clamp(centerDiff, -recHalfSize, recHalfSize);

	const sf::Vector2f closest = recCenter + clamped;
	const sf::Vector2f closestDiff = closest - circleCenter;

	if (sqrt(closestDiff.x * closestDiff.x + closestDiff.y * closestDiff.y) < circle.getRadius())
		return std::make_tuple(true, getDirection(closestDiff), closestDiff);
	else
		return std::make_tuple(false, Direction::TOP, sf::Vector2f(0.0f, 0.0f));
}

void Game::update(float delta)
{
	if (m_ball.isAttached())
	{
		m_ball.setPosition(m_paddle.getPosition().x + m_paddleSizeX / 2 - m_ball.getRadius(), m_paddle.getPosition().y - m_ball.getSize());
	}
	else
	{
		m_ball.setPosition(m_ball.getPosition().x + m_ball.getVelocity().x * delta, m_ball.getPosition().y + m_ball.getVelocity().y * delta);

		const sf::Vector2f ballPos = m_ball.getPosition();
		const sf::Vector2f ballPosTopRight = sf::Vector2f(ballPos.x + m_ball.getSize(), ballPos.y);
		const sf::Vector2f ballPosBottomLeft = sf::Vector2f(ballPos.x, ballPos.y + m_ball.getSize());
		const sf::Vector2f ballPosBottomRight = sf::Vector2f(ballPos.x + m_ball.getSize(), ballPos.y + m_ball.getSize());

		// check window boundaries for ball
		if (ballPosTopRight.x >= m_windowWidth)
			m_ball.setXVelocity(-1 * abs(m_ball.getVelocity().x));
		else if (ballPos.x <= 0.0f)
			m_ball.setXVelocity(abs(m_ball.getVelocity().x));
		if (ballPos.y <= 0.0f)
			m_ball.setYVelocity(abs(m_ball.getVelocity().y));
		else if (ballPos.y > m_windowHeight + 25.0f)
		{
			m_ball.setAttached(true);
			m_ball.setYVelocity(-1 * abs(m_ball.getVelocity().y));
		}

		// check if ball has contact with player paddle
		std::tuple<bool, Direction, sf::Vector2f> coll = checkCollision(m_ball.getShape(), m_paddle);
		if (std::get<0>(coll))
		{
			Direction dir = std::get<1>(coll);
			const sf::Vector2f& diffVec = std::get<2>(coll);
			if (dir == Direction::TOP)
			{
				m_ball.setPosition(ballPos.x, ballPos.y - abs(diffVec.y));
				m_ball.setYVelocity(-1 * abs(m_ball.getVelocity().y));
			}
			else if (dir == Direction::LEFT || dir == Direction::RIGHT)
			{
				m_ball.setXVelocity(-m_ball.getVelocity().x);

				if (dir == Direction::LEFT)
					m_ball.setPosition(ballPos.x - abs(diffVec.x), ballPos.y);
				else
					m_ball.setPosition(ballPos.x + abs(diffVec.x), ballPos.y);
			}
		}

		// check if ball hit a box
		for (int i = 0; i < m_recs.size(); )
		{	
			std::tuple<bool, Direction, sf::Vector2f> coll = checkCollision(m_ball.getShape(), m_recs.at(i));
			if (std::get<0>(coll))
			{
				Direction dir = std::get<1>(coll);
				const sf::Vector2f& diffVec = std::get<2>(coll);
				if (dir == Direction::TOP || dir == Direction::BOTTOM)
				{
					m_ball.setYVelocity(-m_ball.getVelocity().y);
					float correction = m_ball.getRadius() - abs(diffVec.y);
					if (dir == Direction::TOP)
						m_ball.setPosition(ballPos.x, ballPos.y - correction);
					else
						m_ball.setPosition(ballPos.x, ballPos.y + correction);
				}
				else
				{
					m_ball.setXVelocity(-m_ball.getVelocity().x);
					float correction = m_ball.getRadius() - abs(diffVec.x);
					if (dir == Direction::LEFT)
						m_ball.setPosition(ballPos.x - correction, ballPos.y);
					else
						m_ball.setPosition(ballPos.x + correction, ballPos.y);
				}

				m_recs.erase(m_recs.begin() + i);
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
	m_window.draw(m_ball.getShape());

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

			frames++;

			if ((clock.getElapsedTime() - timer).asSeconds() > 1.0f)
			{
				timer += sf::seconds(1.0f);
				std::cout << frames << "fps" << std::endl;
				frames = 0;
			}
		}
	}
}