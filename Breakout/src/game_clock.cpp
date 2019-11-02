#include "game_clock.h"

GameClock::GameClock(float fps) : m_elapsed{ 0.f }, m_fps { fps }, m_clock{ new sf::Clock{} }
{
	m_frametime = 1.f / m_fps;
}

void GameClock::subscribe( std::function<void(float)> callbackSub )
{
	m_subscribedFunctions.push_back(callbackSub);
}

void GameClock::update()
{
	m_elapsed += m_clock->restart().asSeconds();	
}

float GameClock::elapsed() const
{
	return m_elapsed;
}

void GameClock::tick()
{
	for (auto sub : m_subscribedFunctions) // calls all subbed functions
	{
		sub(m_elapsed);
	}
	m_elapsed -= m_frametime;
}

bool GameClock::readyToTick() const
{
	return m_elapsed >= m_frametime;
}
