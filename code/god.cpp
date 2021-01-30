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
God::process()
{
	while(mDrawing.isActive())
	{
			
		mDrawing.checkEvents();

		if (mPopulation.status() == LifeStatus::NewTurn)
		{
			if (!mDrawing.allowedNextStep()) continue;
			step();
			draw();
		}
		else if (mPopulation.status() == LifeStatus::NewCreature)
		{
			if (!mDrawing.allowedNextStep()) continue;
			step();
			draw();
		}
		else if (mPopulation.status() == LifeStatus::NaturalSelection)
		{
			if (!mDrawing.allowedNextStep()) continue;
			step();
			draw();
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

	if (action->isCompletAction())
	{
		mPopulation.step();
		mEnvironment.step();
	}

	delete(action);
	delete(response);
}
//--------------------------------------------------------------------------------
void 
God::evolve()
{
	mPopulation.evolve();
	mEnvironment.reset();
}
//--------------------------------------------------------------------------------
void
God::next()
{
	mPopulation.step();
	mEnvironment.step();
}
//--------------------------------------------------------------------------------
void
God::draw()
{
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