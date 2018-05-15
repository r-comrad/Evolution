#ifndef GOD_H
#define GOD_H

#include "environment.h"
#include "population.h"
#include "creatures_life_list.h"
#include "population_statistic.h"
#include "drawing.h"

class God
{
public:
	God();
	~God();

	void process();

private:
	Environment mEnvironment;
	Population mPopulation;
	Drawing mDrawing;

	bool drawFlag = true;

	void step();
	void evolve();

	void next();
	void draw();
};

#endif // GOD_H