#ifndef POPULATION_H
#define POPULATION_H

#include <list>
#include <vector>
#include <ostream>
#include <sstream>

#include "domain.h"
#include "creature.h"

#define FILE_NAME ""

enum LifeStatus { NaturalSelection, RequiresEvolution };

class Population
{
public:
	Population();
	~Population();

	LifeStatus status();
	void evolve();
	void savePopulation(std::stringstream ss);
	void loadPopulation(std::stringstream ss);

	Action* getNextAction();
	uint_16 getPopulatioAge();
	uint_16 getPopulationTurnCount();
	void giveResponse(Response* aResponse);

private:
	uint_16 mOrganismsMinCount;
	uint_16 mOrganismsMaxCount;
	uint_16 mOrganismsChildCount;

	uint_16 mActionCount;
	uint_16 mPopulatioAge;
	uint_16 mPopulationTurnCount;

	// шаблоны для эволюции(колличество изменений)
	// зацикленные
	std::queue <uint_8> mMutateTemplate; 

	std::list<Creature> ::iterator mCurentOrganism;
	std::list<Creature> mOrganisms;
	//std::vector<Creature> mOrganisms;

	//std::ofstream mFileForPrograms;
};

#endif // POPULATION_H