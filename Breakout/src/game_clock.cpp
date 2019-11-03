#include "game_clock.h"

GameClock::GameClock(float fps)
	: m_elapsed{ 0.f }, m_fps{ fps }, m_clock{ new sf::Clock{} }
{
	m_frametime = 1.f / m_fps;
}

void GameClock::reset()
{
	m_elapsed = 0.f;
	delete m_clock;
	m_clock = new sf::Clock{};
}

void GameClock::update()
{
	m_elapsed += m_clock->restart().asSeconds();
}

void GameClock::tick()
{
	m_elapsed -= m_frametime;
}

bool GameClock::readyToTick() const
{
	return m_elapsed >= m_frametime;
}
