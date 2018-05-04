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

	mPopulatioAge = 0;
	mPopulationTurnCount = 0;
	mActionCount = 0;
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
	{
		result = LifeStatus::RequiresEvolution;
	}
	return result;
}
//--------------------------------------------------------------------------------
void
Population::evolve()
{
	mPopulatioAge = 0;

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
Action* 
Population::getNextAction()
{
	mActionCount++;
	Action* action = mCurentOrganism->getAction();
	action->setActionCount(mActionCount);

	if (action->isCompletAction())
	{
		mCurentOrganism->step();
		++mCurentOrganism;
		++mPopulationTurnCount;
		mActionCount = 0;

		if (mCurentOrganism == mOrganisms.end())
		{
			mCurentOrganism = mOrganisms.begin();
			++mPopulatioAge;
			mPopulationTurnCount = 0;
		}
	}

	//TODO
	if (action->mActionType == ActionType::DIE)
	{
		std::list<Creature> ::iterator it = mCurentOrganism;
		if (it != mOrganisms.begin())
			mOrganisms.erase(--it);
		else mOrganisms.erase(--mOrganisms.end());
	}

	return action;
}
//--------------------------------------------------------------------------------
uint_16 
Population::getPopulatioAge()
{
	return mPopulatioAge;
}
//--------------------------------------------------------------------------------
uint_16 
Population::getPopulationTurnCount()
{
	return mPopulationTurnCount;
}
//--------------------------------------------------------------------------------
void 
Population::giveResponse(Response* aResponse)
{
	mCurentOrganism->processResponses(aResponse);
}
//--------------------------------------------------------------------------------