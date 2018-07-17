#include <SFML/Graphics.hpp>

#include <iostream>
#include <random>

sf::RenderWindow window;
sf::RectangleShape paddle;
std::vector<sf::RectangleShape> recs;

float speed = 400.0f;

void init()
{
	// window
	window.create(sf::VideoMode(600, 800), "Breakout");

	// player paddle
	paddle.setSize(sf::Vector2f(100.0f, 30.0f));
	paddle.setFillColor(sf::Color::Green);
	paddle.setPosition(270.0f, 760.0f);

	// colored boxes
	std::default_random_engine gen;
	std::uniform_int_distribution<int> dis(0, 255);

	for (int i = 0; i < 8; i++)
	{
		sf::RectangleShape rectangle(sf::Vector2f(100.0f, 30.0f));
		rectangle.setPosition(i * 100.0f, 0.0f);
		rectangle.setFillColor(sf::Color(dis(gen), dis(gen), dis(gen), 255));
		recs.push_back(rectangle);
	}
}

void pollEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void processInput(float delta)
{
	pollEvents();

	sf::Vector2f pos = paddle.getPosition();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (pos.x > 10.0f)
			paddle.setPosition(paddle.getPosition().x - speed * delta, paddle.getPosition().y);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (pos.x < 590.0f - paddle.getSize().x)
			paddle.setPosition(paddle.getPosition().x + speed * delta, paddle.getPosition().y);
	}
}

void update(float delta)
{

}

void draw()
{
	window.clear();

	window.draw(paddle);
	for (sf::RectangleShape& rec : recs)
	{
		window.draw(rec);
	}

	window.display();
}

int main()
{
	init();

	sf::Clock clock;
	sf::Time timer = clock.getElapsedTime();
	sf::Time current = sf::Time::Zero;
	sf::Time last = sf::Time::Zero;
	float delta = 0.0f;
	float tps = 1.0 / 60.0;
	int frames = 0;

	while (window.isOpen())
	{
		current = clock.getElapsedTime();
		delta = (current - last).asSeconds();
		last = current;

		processInput(delta);
		update(delta);
		frames++;

		if ((clock.getElapsedTime() - timer).asSeconds() > 1.0f)
		{
			timer += sf::seconds(1.0f);
			std::cout << frames << "fps" << std::endl;
			frames = 0;
		}

		draw();
	}

	return 0;
}