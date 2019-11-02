#include "game_clock.h"

GameClock::GameClock(float fps) : m_fps{ fps }
{
	m_frametime = 1.f / m_fps;
	initiateClock();
}

void GameClock::initiateClock()
{
	if (m_clock)
	{
		delete m_clock;
	}

	m_clock = new sf::Clock{};
}

void GameClock::subscribe(std::function<void(float)> callbackSub)
{
	m_subscribedFunctions.push_back(callbackSub);
}

void GameClock::update()
{
	m_elapsed += m_clock->restart().asSeconds();
	if (readyToTick())
	{
		tick();
	}
}

float GameClock::elapsed() const
{
	return m_elapsed;
}

void GameClock::tick()
{
	for (auto sub : m_subscribedFunctions)
	{
		sub(m_elapsed);
	}
	m_elapsed -= m_frametime;
}

bool GameClock::readyToTick() const
{
	return m_elapsed >= m_frametime;
}
