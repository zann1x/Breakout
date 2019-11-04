#pragma once

#include <SFML/System/Clock.hpp>

class GameClock
{
public:
	/* Note: Clock starts at construction*/
	GameClock();

	~GameClock() { delete m_clock; }

	/* Restart the clock */
	void reset();

	/* Update the current time of the clock */
	void update();

	/* returns true if time since last tick is > 1 sec */
	inline bool readyToTick() const { return m_elapsed - m_lastTick >= 1.0f; }

	/* resets all values that need to be updated per second */
	void tick();

	/* Get the current delta time of the clock*/
	inline float delta() const { return m_frametime; };

	/* Get elapsed time since starting the clock*/
	inline float elapsed() const { return m_elapsed; };

	/* Gets the fps count */
	inline int getFps() const { return m_frames; }

private:
	sf::Clock* m_clock;
	float m_elapsed;
	float m_lastTick;
	float m_frametime;
	int m_frames;
};
