#include "population.h"

//--------------------------------------------------------------------------------
// Action implementation
//--------------------------------------------------------------------------------

Population::Population() :
	mMutateTemplate({ 0, 0, 0, 0, 1, 2, 3, 4 })
{
	mOrganismsMinCount = 8;
	mOrganismsMaxCount = 64;
	mOrganismsChildCount = 7;

	mOrganisms.resize(64);
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
	if (mPopStatistic.getPopulationAge() <= 1) // TODO
	{
		result = LifeStatus::NewTurn;
	}
	if (mPopStatistic.getCommandCount() == 0)
	{
		result = LifeStatus::NewCreature;
	}
	else if (mOrganisms.size() > mOrganismsMinCount)
	{
		result = LifeStatus::NaturalSelection;
	}
	else
	{
		result = LifeStatus::RequiresEvolution;
	}
	return result;
}
//--------------------------------------------------------------------------------
void
Population::evolve()
{
	mPopStatistic.nextCycle();

	std::list<Creature> ::iterator it = mOrganisms.begin();
	for (uint_8 i = 0; i < mOrganismsMinCount; ++i, ++it)
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
		it->reset();


		mMutateTemplate.push(mMutateTemplate.front());
		mMutateTemplate.pop();
	}

	mCurentOrganism = mOrganisms.begin();
}
//--------------------------------------------------------------------------------
void
Population::step()
{
	mCurentOrganism->step();
	++mCurentOrganism;
	mPopStatistic.nextCreature();

	if (mCurentOrganism == mOrganisms.end())
	{
		mCurentOrganism = mOrganisms.begin();
		mPopStatistic.nextTurn();
	}
}
//--------------------------------------------------------------------------------
void
Population::savePopulation(std::stringstream ss)
{

}
//--------------------------------------------------------------------------------
void 
Population::loadPopulation(std::stringstream ss)
{

}
//--------------------------------------------------------------------------------
const PopulationStatistic& 
Population::getPopulationStatistic()
{
	return mPopStatistic;
}
//--------------------------------------------------------------------------------
std::list<sint_16>
Population::getCreaturesLifes()
{
	std::list<sint_16> result;

	for (auto i : mOrganisms)
	{
		result.emplace_back(i.getLife());
	}

	return result;
}
//--------------------------------------------------------------------------------
Action* 
Population::getNextAction()
{
	Action* action = mCurentOrganism->getAction();
	action->setActionCount(mPopStatistic.getCommandCount());
	mPopStatistic.nextCommand();
	return action;
}
//--------------------------------------------------------------------------------
//uint_16 
//Population::getPopulatioAge()
//{
//	return mPopulatioAge;
//}
////--------------------------------------------------------------------------------
//uint_16 
//Population::getPopulationTurnCount()
//{
//	return mPopulationTurnCount;
//}
//--------------------------------------------------------------------------------
void 
Population::processResponse(Response* aResponse)
{
	mCurentOrganism->processResponses(aResponse);

	//TODO RRRRRRRRRRRRRRRRRR
	if (aResponse->mActionType == ActionType::DIE)
	{
		std::list<Creature> ::iterator it = mCurentOrganism;
		if (mCurentOrganism != mOrganisms.begin()) --mCurentOrganism;
		else mCurentOrganism = --mOrganisms.end();
		mOrganisms.erase(it);
	}

	//delete(aResponse);			// TODO
}
//--------------------------------------------------------------------------------