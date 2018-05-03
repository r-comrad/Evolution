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

		if (population.status == LifeStatus::NaturalSelection)
		{
			step();
		}
		else if (population.status == LifeStatus::RequiresEvolution)
		{
			evolve();
		}

		mDrawing.draw();
	}
}
//--------------------------------------------------------------------------------
void 
God::step()
{
	Action* action = population.getNextAction();
	Response* response = environment.process(action);
	population.giveResponse(response);
}
//--------------------------------------------------------------------------------
void 
God::evolve()
{
	population.evolve();
}