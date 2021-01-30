//#include <SFML/Graphics.hpp>
#include "god.h"

#include <iostream>
using namespace std;

struct A
{
	sf::RenderWindow window; 
	sf::Event event;
	double n;
	bool drawFlag;
	sf::RectangleShape rectangle;
	A() :
		window(sf::VideoMode(1920, 1200), "Evolution 3.0"),
		rectangle(sf::Vector2f(20, 20)),
		n(0)
	{
		
		rectangle.setSize(sf::Vector2f(20, 20));
	}

	void rrr()
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();

			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Tab)
				{
					cout << "Tab";
					drawFlag = !drawFlag;
				}
				if (event.key.code == sf::Keyboard::X)
				{
					window.close();
				}
			}
		}
	}

	void tt()
	{
		window.clear();
		if (drawFlag)
		{
			rectangle.setPosition(sf::Vector2f(int(n), 400));
			rectangle.setFillColor(sf::Color::Blue);
			window.draw(rectangle);
		}

		n += 0.1;
		if (n > 1000) n -= 1000;

		window.display();
	}
};

int main()
{
	//A a;

	//while (true)
	//{
	//	a.rrr();

	//	int x, y;
	//	//cin >> x >> y;
	//	//cout << x + y;

	//	a.tt();
	//}

	//return 0;

	God god;
	god.process();
	return 0;
}