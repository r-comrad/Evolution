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

enum LifeStatus { NewCreature, NewTurn, NewPopulation, NaturalSelection, RequiresEvolution };

class Population
{
public:
	Population();
	~Population();

	LifeStatus status();
	void evolve();
	void step();
	uint_16 size();
	bool canGrov();

	void savePopulation(std::stringstream ss);
	void loadPopulation(std::stringstream ss);
	const PopulationStatistic& getPopulationStatistic();
	std::list<sint_16> getCreaturesLifes();

	Action* getNextAction();
	void processResponse(Response* aResponse);

private:
	std::ofstream file;

	uint_16 mOrganismsMinCount;
	uint_16 mOrganismsMaxCount;
	uint_16 mOrganismsChildCount;

	PopulationStatistic mPopStatistic;

	// ������� ��� ��������(����������� ���������)
	// �����������
	std::queue <uint_8> mMutateTemplate; 

	std::list<Creature> ::iterator mCurentOrganism;
	std::list<Creature> mOrganisms;
};

#endif // POPULATION_H