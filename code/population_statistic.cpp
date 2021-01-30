#include "population_statistic.h"

//--------------------------------------------------------------------------------
// Statistic implementation
/// Characteristic implementation
//--------------------------------------------------------------------------------

PopulationStatistic::PopulationStatistic() :
	mCommandCount		(0),
	mCreatureCount		(0),
	mPopulationAges		{ 0 }
{}
//--------------------------------------------------------------------------------
void
PopulationStatistic::nextCommand()
{
	mCommandCount++;
}
//--------------------------------------------------------------------------------
void
PopulationStatistic::nextCreature()
{
	mCommandCount = 0;
	mCreatureCount++;
}
//--------------------------------------------------------------------------------
void
PopulationStatistic::nextTurn()
{
	mCommandCount = 0;
	mCreatureCount = 0;
	(*mPopulationAges.begin())++;
}
//--------------------------------------------------------------------------------
void
PopulationStatistic::nextCycle()
{
	mCommandCount = 0;
	mCreatureCount = 0;
	mPopulationAges.emplace_front(0);
	if (mPopulationAges.size() > POPULATION_AGE_MEMORY_SIZE)
		mPopulationAges.pop_back();
}
//--------------------------------------------------------------------------------
uint_16
PopulationStatistic::getCommandCount() const
{
	return mCommandCount;
}
//--------------------------------------------------------------------------------
uint_16
PopulationStatistic::getCreatureCount() const
{
	return mCreatureCount;
}
//--------------------------------------------------------------------------------
uint_16
PopulationStatistic::getPopulationAge() const
{
	return *mPopulationAges.begin();
}
//--------------------------------------------------------------------------------
const std::list<uint_16>& 
PopulationStatistic::getAllAges() const
{
	return mPopulationAges;
}