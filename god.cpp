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
		}
		else if (mPopulation.status() == LifeStatus::RequiresEvolution)
		{
			evolve();
		}

		if (ccc % 64 == 0)
		{
			mDrawing.draw(mEnvironment.getField(), 
				mPopulation.getPopulatioAge(), mPopulation.getPopulationTurnCount());
		}

	}
}
//--------------------------------------------------------------------------------
void 
God::step()
{
	Action* action = mPopulation.getNextAction();
	Response* response = mEnvironment.process(action);
	mPopulation.giveResponse(response);

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