//#include <SFML/Graphics.hpp>

/*int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}*/

#include "environment.h"
#include "population.h"

Environment environment;
Population population;
bool drawFlag = true;

void foo()
{
	Action* action = population.getNextAction();
	Response* response = environment.process(action);
	population.giveResponse(response);
}

int main()
{
	//std::ofstream file1;
	//file1.open("a");
	//file1 << 1;
	//return 0;
	sf::RenderWindow window(sf::VideoMode(1920, 1200), "Evolution 3.0");

	sf::Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if(event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Tab)
				{
					drawFlag = !drawFlag;
				}
				if (event.key.code == sf::Keyboard::X)
				{
					window.close();
				}
			}
		}

		foo();

		window.clear();
		if (drawFlag)
		{
			//foo1(window);
		}		
		window.display();
	}
	
	return 0;
}