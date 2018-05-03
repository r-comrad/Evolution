#ifndef DRAWING_H
#define DRAWING_H

#include <SFML/Graphics.hpp>

#include "domain.h"
#include "environment.h"
#include "population.h"

#define DRAW_SQUARE_SIZE 14

class Drawing
{
public:
	Drawing();

	void checkEvents();
	void draw(const std::vector<std::vector<CeilType>>& aField);

	bool isActive();

private:
	sf::RenderWindow mWindow;
	sf::Event mEvent;

	bool mDrawFlag;
public:
	void drawField(const std::vector<std::vector<CeilType>>& aField);
	void drawCreatures(sf::RenderWindow& aWindow, 
		Environment& aEnvironment, Population& aPopulation) const;
	void drawHistory(sf::RenderWindow& aWindow, std::vector<uint_32> aHistory) const;
};

#endif // DRAWING_H