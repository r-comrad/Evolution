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
uint_16 glN = 0;
void 
God::process()
{
	while(mDrawing.isActive())
	{
			
		mDrawing.checkEvents();

		if (mPopulation.status() == LifeStatus::NewCreature)
		{
			if (!mDrawing.allowedNextStep()) continue;
			step();
			//draw();
		}
		else if (mPopulation.status() == LifeStatus::NewTurn)
		{
			if (!mDrawing.allowedNextStep()) continue;
			step();
			draw();
			
			uint_16 k = 64 / mPopulation.size();
			//if (mPopulation.canGrov()) mEnvironment.newTurn();
			++cnt;
			if (cnt % k == 0) mEnvironment.newTurn();
		}
		else if (mPopulation.status() == LifeStatus::NewPopulation)
		{
			if (!mDrawing.allowedNextStep()) continue;
			step();
			draw();
		}
		else if (mPopulation.status() == LifeStatus::NaturalSelection)
		{
			if (!mDrawing.allowedNextStep()) continue;
			step();
			//draw();
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
	++glN;
	mPopulation.evolve();
	mEnvironment.reset();
	cnt = 0;
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
	mDrawing.drawStatistic(popStatistic, glN);
	mDrawing.display();
}