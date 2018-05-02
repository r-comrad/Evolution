#include "population.h"

//--------------------------------------------------------------------------------
// Action implementation
//--------------------------------------------------------------------------------

Population::Population()
{
	mCurentOrganism = mOrganisms.begin();
}
//--------------------------------------------------------------------------------
Population::~Population()
{}
//--------------------------------------------------------------------------------
LifeStatus
Population::status()
{
	LifeStatus result;
	if (mOrganisms.size() > mOrganismsMinCount)
	{
		result = LifeStatus::NaturalSelection;
	}
	else
		//else if (mCreatures.size() <= CREATURE_MIN_COUNT) TODO? >0
	{
		result = LifeStatus::RequiresEvolution;
	}
	return result;
}
//--------------------------------------------------------------------------------
void
Population::evolve()
{
	//std::list<Creature> ::iterator it = mOrganisms.begin();
	//for (uint_16 i = 0; i < mOrganismsChildCount; ++i)
	//{
	//	for (uint_16 j = 0; j < mOrganismsChildCount; ++j)
	//	{
	//		mOrganisms.push_back(*it);
	//	}
	//}

	for (std::list<Creature> ::iterator it = mOrganisms.begin();
		it != mOrganisms.end(); ++it)
	{
		for (uint_16 j = 0; j < mOrganismsChildCount; ++j)
		{
			mOrganisms.push_back(*it);
		}
	}

	for (std::list<Creature> ::iterator it = mOrganisms.begin();
		it != mOrganisms.end(); ++it)
	{
		it->mutate(mMutateTemplate.front());
		mMutateTemplate.push(mMutateTemplate.front());
		mMutateTemplate.pop();
	}
}
//--------------------------------------------------------------------------------
void
Population::savePopulation(std::stringstream ss)
{
	//mFileForPrograms.open(FILE_NAME);
	//if (!mFileForPrograms.is_open())
	//{
	//	//cerr << "ERROR #10: Population.cpp (72). Can`t open file.";
	//	cout << "ERROR #10: Population.cpp (72). Can`t open file.";
	//}
	//
	//for (std::list<Creature> ::iterator it = mOrganisms.begin();
	//	it != mOrganisms.end(); ++it)
	//{

	//}

	//mFileForPrograms.close();
}
void 
Population::loadPopulation(std::stringstream ss)
{

}
//--------------------------------------------------------------------------------
Action* 
Population::getNextAction()
{
	return mCurentOrganism->getAction();
}
//--------------------------------------------------------------------------------
void 
Population::giveResponse(Response* aResponse)
{
	mCurentOrganism->processResponses(aResponse);
}
//--------------------------------------------------------------------------------