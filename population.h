#ifndef POPULATION_H
#define POPULATION_H

#include <list>
#include <vector>
#include <ostream>
#include <sstream>

#include "domain.h"
#include "creature.h"
#include "population_statistic.h"

#define FILE_NAME ""

enum LifeStatus { NewTurn, NewCreature, NaturalSelection, RequiresEvolution };

class Population
{
public:
	Population();
	~Population();

	LifeStatus status();
	void evolve();

	void savePopulation(std::stringstream ss);
	void loadPopulation(std::stringstream ss);
	const PopulationStatistic& getPopulationStatistic();
	std::list<uint_16> getCreaturesLifes();

	Action* getNextAction();
	void processResponse(Response* aResponse);

private:
	uint_16 mOrganismsMinCount;
	uint_16 mOrganismsMaxCount;
	uint_16 mOrganismsChildCount;

	PopulationStatistic mPopStatistic;

	// шаблоны для эволюции(колличество изменений)
	// зацикленные
	std::queue <uint_8> mMutateTemplate; 

	std::list<Creature> ::iterator mCurentOrganism;
	std::list<Creature> mOrganisms;
};

#endif // POPULATION_H