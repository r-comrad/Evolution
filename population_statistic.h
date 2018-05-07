#ifndef POPULATION_STATISTIC_H
#define POPULATION_STATISTIC_H

#include <list>

#include "domain.h"

//CHARACTERISTIC_H
//class Characteristic
class PopulationStatistic
{
public:
	PopulationStatistic();

	void nextCommand();
	void nextCreature();
	void nextTurn();
	void nextCycle();

	uint_16 getCommandCount() const;
	uint_16 getCreatureCount() const;
	uint_16 getPopulationAge() const;

private:
	uint_16 mCommandCount;
	uint_16 mCreatureCount;
	uint_16 mPopulatioAge;

	//std::list<uint_8> mLifeValues;
};

#endif // POPULATION_STATISTIC_H