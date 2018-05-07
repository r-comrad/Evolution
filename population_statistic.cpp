#include "population_statistic.h"

//--------------------------------------------------------------------------------
// Statistic implementation
/// Characteristic implementation
//--------------------------------------------------------------------------------

PopulationStatistic::PopulationStatistic() :
	mCommandCount		(0),
	mCreatureCount		(0),
	mPopulatioAge		(0)
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
	mPopulatioAge++;
}
//--------------------------------------------------------------------------------
void
PopulationStatistic::nextCycle()
{
	mCommandCount = 0;
	mCreatureCount = 0;
	mPopulatioAge = 0;
}
//--------------------------------------------------------------------------------
uint_16
PopulationStatistic::getCommandCount()
{
	return mCommandCount;
}
//--------------------------------------------------------------------------------
uint_16
PopulationStatistic::getCreatureCount()
{
	return mCreatureCount;
}
//--------------------------------------------------------------------------------
uint_16
PopulationStatistic::getPopulationAge()
{
	return mPopulatioAge;
}
//--------------------------------------------------------------------------------