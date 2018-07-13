#include <SFML/Graphics.hpp>

#include <iostream>
#include <random>

sf::RectangleShape paddle(sf::Vector2f(100.0f, 30.0f));
float speed = 5.0f;

void update()
{
	sf::Vector2f pos = paddle.getPosition();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (pos.x > 10.0f)
			paddle.setPosition(paddle.getPosition().x - speed, paddle.getPosition().y);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (pos.x < 590.0f - paddle.getSize().x)
			paddle.setPosition(paddle.getPosition().x + speed, paddle.getPosition().y);
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 800), "Breakout");
	paddle.setFillColor(sf::Color::Green);
	paddle.setPosition(270.0f, 750.0f);

	std::default_random_engine gen;
	std::uniform_int_distribution<int> dis(0, 255);

	std::vector<sf::RectangleShape> recs;
	for (int i = 0; i < 8; i++)
	{
		sf::RectangleShape rectangle(sf::Vector2f(100.0f, 30.0f));
		rectangle.setPosition(i * 100.0f, 0.0f);
		rectangle.setFillColor(sf::Color(dis(gen), dis(gen), dis(gen), 255));
		recs.push_back(rectangle);
	}

	sf::Clock clock;
	sf::Time elapsed = sf::Time::Zero;
	int frames = 0;

	while (window.isOpen())
	{
		sf::Time delta = clock.restart();
		elapsed += delta;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			update();
		}
		frames++;

		if (elapsed.asSeconds() >= 1.0f)
		{
			std::cout << frames << "fps" << std::endl;
			elapsed = sf::Time::Zero;
			frames = 0;
		}

		window.clear();
		window.draw(paddle);
		for (sf::RectangleShape& rec : recs)
		{
			window.draw(rec);
		}
		window.display();
	}

	return 0;
}