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
void 
God::start()
{
	while(mDrawing.isActive())
	{
		mDrawing.checkEvents();

		if (mPopulation.status() == LifeStatus::NewTurn)
		{
			step();

			mDrawing.clear();
			if (mDrawing.isDraw())
			{
				CreaturesLifeList list(mEnvironment.getCreaturesCoordinates(),
					mPopulation.getCreaturesLifes());
				mDrawing.drawField(mEnvironment.getField());
				mDrawing.drawCreaturesLifes(list);
			}
			const PopulationStatistic&
				popStatistic = mPopulation.getPopulationStatistic();
			mDrawing.drawStatistic(popStatistic);
			mDrawing.display();
		}
		else if (mPopulation.status() == LifeStatus::NewCreature)
		{
			if (mDrawing.stepByStep() && !mDrawing.pressedN()) continue;

			step();

			mDrawing.clear();
			if (mDrawing.isDraw())
			{
				CreaturesLifeList list(mEnvironment.getCreaturesCoordinates(),
					mPopulation.getCreaturesLifes());
				mDrawing.drawField(mEnvironment.getField());
				mDrawing.drawCreaturesLifes(list);
			}
			const PopulationStatistic&
				popStatistic = mPopulation.getPopulationStatistic();
			mDrawing.drawStatistic(popStatistic);
			mDrawing.display();
		}
		else if (mPopulation.status() == LifeStatus::NaturalSelection)
		{
			step();

			//mDrawing.clear();
			//const PopulationStatistic&
			//	popStatistic = mPopulation.getPopulationStatistic();
			//mDrawing.drawStatistic(popStatistic);
			//mDrawing.display();
		}
		else if (mPopulation.status() == LifeStatus::RequiresEvolution)
		{
			evolve();
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
}
//--------------------------------------------------------------------------------
void 
God::evolve()
{
	mPopulation.evolve();
	mEnvironment.reset();
}