#ifndef DRAWING_H
#define DRAWING_H

#include <SFML/Graphics.hpp>

#include "domain.h"
#include "environment.h"
#include "population.h"

#define DRAW_SQUARE_SIZE 14

class Drawing
{
	void drawField(sf::RenderWindow& aWindow, Environment& aEnvironment) const;
	void drawCreatures(sf::RenderWindow& aWindow, 
		Environment& aEnvironment, Population& aPopulation) const;
	void drawHistory(sf::RenderWindow& aWindow, std::vector<uint_32> aHistory) const;
};

#endif // DRAWING_H