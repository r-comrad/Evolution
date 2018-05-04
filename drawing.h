#ifndef DRAWING_H
#define DRAWING_H

#include <SFML/Graphics.hpp>

#include "domain.h"
#include "environment.h"
#include "population.h"

#define DRAW_SQUARE_SIZE 14

class Drawing
{
	enum DrawingState { NONE, GENERATION, TURN, STEP };

public:
	Drawing();

	void checkEvents();
	void draw(const std::vector<std::vector<CeilType>>& aField, 
		uint_16 aPopulatioAge, uint_16 aPopulationTurnCount);

	bool isActive();

private:
	sf::RenderWindow mWindow;
	sf::Event mEvent;
	sf::Font mFont;
	sf::Text mText;

	bool mDrawFlag;
	DrawingState mDrawState;
public:
	void drawField(const std::vector<std::vector<CeilType>>& aField);
	void drawCreatures(sf::RenderWindow& aWindow, 
		Environment& aEnvironment, Population& aPopulation) const;
	void drawHistory(sf::RenderWindow& aWindow, std::vector<uint_32> aHistory) const;
};

#endif // DRAWING_H