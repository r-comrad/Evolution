#include "god.h"

//--------------------------------------------------------------------------------
// God implementation
//--------------------------------------------------------------------------------

God::God()
{

}
//--------------------------------------------------------------------------------
God::~God()
{

}
//--------------------------------------------------------------------------------
int ccc = 0;
void 
God::start()
{
	while(mDrawing.isActive())
	{
		mDrawing.checkEvents();

		if (mPopulation.status() == LifeStatus::NaturalSelection)
		{
			step();

			CreaturesLifeList list(mEnvironment.getCreaturesCoordinates(), 
				mPopulation.getCreaturesLifes());
			const PopulationStatistic& 
				popStatistic = mPopulation.getPopulationStatistic();

			mDrawing.draw(mEnvironment.getField(), list, popStatistic);
		}
		else if (mPopulation.status() == LifeStatus::RequiresEvolution)
		{
			evolve();
		}

		if (ccc % 64 == 0)
		{
			//if (mPopulation.getPopulatioAge() == 15)
			//{
			//	int y = 0;
			//	cout << y;
			//}
			//PopulationStatistic popStatistic = mPopulation.getPopulationStatistic();
			//mDrawing.draw(mEnvironment.getField(), 
			//	popStatistic.getPopulationAge(), popStatistic.getCreatureCount());
		}

	}
}
//--------------------------------------------------------------------------------
void 
God::step()
{
	Action* action = mPopulation.getNextAction();
	Response* response = mEnvironment.process(action);
	mPopulation.processResponse(response);

	if (action->isCompletAction())
	{
		++ccc;
		//mDrawing.draw(mEnvironment.getField(),
		//	mPopulation.getPopulatioAge(), mPopulation.getPopulationTurnCount());
	}
}
//--------------------------------------------------------------------------------
void 
God::evolve()
{
	mPopulation.evolve();
	mEnvironment.reset();
}