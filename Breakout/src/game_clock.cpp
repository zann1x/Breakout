#include "game_clock.h"

GameClock::GameClock()
	: m_clock{ new sf::Clock{} }, m_elapsed{ 0.f }, m_frames{ 0 }, m_frametime{ 0.f }
{
}

void GameClock::reset()
{
	m_elapsed = 0.f;
	m_frames = 0;
	m_frametime = 0.f;
	delete m_clock;
	m_clock = new sf::Clock{};
}

void GameClock::update()
{
	m_frametime = m_clock->restart().asSeconds();
	m_elapsed += m_frametime;
	++m_frames;
}

void GameClock::tick()
{
	m_frames = 0;
	m_elapsed = 0.0f;
}
