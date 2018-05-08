#ifndef POPULATION_STATISTIC_H
#define POPULATION_STATISTIC_H

#define POPULATION_AGE_MEMORY_SIZE 10

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
	const std::list<uint_16>& getAllAges() const;

private:
	uint_16 mCommandCount;
	uint_16 mCreatureCount;
	std::list<uint_16> mPopulationAges;

	//std::list<uint_8> mLifeValues;
};

#endif // POPULATION_STATISTIC_H