#pragma once

#include <vector>
#include <functional>
#include <SFML/System/Clock.hpp>

class GameClock
{
public:
	/* Note: Clock starts at construction*/
	explicit GameClock(float fps = 60.f);

	~GameClock() { delete m_clock; }

	void reset();

	/* Subscribe update methods to clock to receive a callback when clock ticks */
	void subscribe(std::function<void(float)> callbackSub);

	/* Update the current time of the clock */
	void update();

	/* returns true if clock has reached desired elapsed time */
	bool readyToTick() const;

	/* consumes elapsed time for one frame and calls all subscribed methods */
	void tick();

	/* Get the current delta time of the clock*/
	float elapsed() const;

private:
	sf::Clock* m_clock;
	float m_elapsed;
	float m_fps;
	float m_frametime;

	std::vector<std::function<void(float)>> m_subscribedFunctions;
};
