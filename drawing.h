#ifndef DRAWING_H
#define DRAWING_H

#include <SFML/Graphics.hpp>

#include "domain.h"
#include "environment.h"
#include "population.h"
#include "creatures_life_list.h"
#include "population_statistic.h"

#define DRAW_SQUARE_SIZE 14

class Drawing
{
	enum DrawingState { NONE, GENERATION, TURN, STEP };

public:
	Drawing();

	void checkEvents();
	//void draw(const std::vector<std::vector<CeilType>>& aField, 
	//	uint_16 aPopulatioAge, uint_16 aPopulationTurnCount);
	//void draw(const std::vector<std::vector<CeilType>>& aField,
	//	CreaturesLifeList& aList, const PopulationStatistic& aPopStatistic);

	bool isActive();
	bool isDraw();

	void clear();
	void display();

	void drawField(const std::vector<std::vector<CeilType>>& aField);
	void drawCreaturesLifes(CreaturesLifeList& aList);
	void drawStatistic(const PopulationStatistic& aPopStatistic);

	bool allowedNextStep();
	bool stepByStep();

private:
	sf::RenderWindow mWindow;
	sf::Event mEvent;
	sf::Font mFont;
	sf::Text mText;

	bool mDrawFlag;
	bool nextStep;
	bool stepByStepFlag;
	DrawingState mDrawState;
public:
	void drawCreatures(sf::RenderWindow& aWindow, 
		Environment& aEnvironment, Population& aPopulation) const;
	void drawHistory(sf::RenderWindow& aWindow, std::vector<uint_32> aHistory) const;
};

#endif // DRAWING_H