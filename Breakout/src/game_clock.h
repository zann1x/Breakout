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
	inline bool readyToTick() const { return m_elapsed >= 1.0f; }

	/* resets all values that need to be updated per second */
	void tick();

	/* Get the current delta time of the clock*/
	inline float delta() const { return m_frametime; };

	/* Gets the fps count */
	inline int getFps() const { return m_frames; }

private:
	sf::Clock* m_clock;
	float m_elapsed;
	float m_frametime;
	int m_frames;
};
