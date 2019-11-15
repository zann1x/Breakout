#include "math.h"

sf::Vector2f clamp(sf::Vector2f val, sf::Vector2f low, sf::Vector2f high)
{
	float cx = std::max(low.x, std::min(high.x, val.x));
	float cy = std::max(low.y, std::min(high.y, val.y));
	return sf::Vector2f(cx, cy);
}

Direction getDirection(const sf::Vector2f& vec)
{
	const sf::Vector2f normalizedVec = vec / sqrt(vec.x * vec.x + vec.y * vec.y);
	int closest = -1;
	float max = 0.0f;
	for (int i = 0; i < 4; i++)
	{
		const sf::Vector2f& dirVec = dirVecs[i];
		float dot = normalizedVec.x * dirVec.x + normalizedVec.y * dirVec.y;
		if (dot > max)
		{
			max = dot;
			closest = i;
		}
	}
	return static_cast<Direction>(closest);
}
