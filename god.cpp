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

		if (mPopulation.status() == LifeStatus::NaturalSelection)
		{
			step();
		}
		else if (mPopulation.status() == LifeStatus::RequiresEvolution)
		{
			evolve();
		}

		mDrawing.draw(mEnvironment.getField(), 
			mPopulation.getPopulatioAge(), mPopulation.getPopulationTurnCount());
	}
}
//--------------------------------------------------------------------------------
void 
God::step()
{
	Action* action = mPopulation.getNextAction();
	Response* response = mEnvironment.process(action);
	mPopulation.giveResponse(response);
}
//--------------------------------------------------------------------------------
void 
God::evolve()
{
	mPopulation.evolve();
}