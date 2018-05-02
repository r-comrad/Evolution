#include "environment.h"

//--------------------------------------------------------------------------------
// Enviroment implementation
//--------------------------------------------------------------------------------

Environment::Environment() :
	mField				(N, std::vector <CeilType> (M, CeilType::EMPTY))
{
	for (uint_16 i = 0; i < N; ++i)
	{
		mField[i][0] = CeilType::WALL;
		mField[i][M - 1] = CeilType::WALL;
	}
	for (uint_16 i = 0; i < M; ++i)
	{
		mField[0][i] = CeilType::WALL;
		mField[N - 1][i] = CeilType::WALL;
	}

	fillField();
	setCreatures();
	//fillField();
	//setCreatures();

	//file1.open("statistic");

	//if (!font.loadFromFile("font.ttf"))
	//{
	//	cout << "Font load error!\n";
	//}

	//text.setFont(font);
}
//--------------------------------------------------------------------------------
Environment::~Environment()
{}
//--------------------------------------------------------------------------------
Response*
Environment::process(Action* action)
{
	Response* response = NULL;

	bool dead = false;
	for (uint_8 i = 0; i < MAX_WATCHING_TIME; ++i)
	{
		if (action->mActionType == ActionType::GOTO)
		{
			response = gotoAction(action);
		}
		else if (action->mActionType == ActionType::MOVE)
		{
			response = moveAction(action);
		}
		else if (action->mActionType == ActionType::LOOK)
		{
			response = lookAction(action);
		}
		else if (action->mActionType == ActionType::TAKE)
		{
			response = takeAction(action);
		}
		else if (action->mActionType == ActionType::TURN)
		{
			response = turnAction(action);
		}
		else if (action->mActionType == ActionType::DIE)
		{
			response = dieAction(action);
			dead = true;
		}
	}

	if (!dead)
	{
		mCoordinates.push(mCoordinates.front());
	}
	mCoordinates.pop();

	return response;
}
//--------------------------------------------------------------------------------
const std::vector<std::vector<CeilType>>& 
Environment::getField() const
{
	return mField;
}
//--------------------------------------------------------------------------------
Response* 
Environment::gotoAction(Action* aGotoAction)
{
	Response* response = NULL;
	MoveAction* gotoAction = static_cast<MoveAction*>(aGotoAction);
	return response;
}
//--------------------------------------------------------------------------------
Response* 
Environment::moveAction(Action* aMoveAction)
{
	Response* response = NULL;
	MoveAction* moveAction = static_cast<MoveAction*>(aMoveAction);
	sint_16 dLife = 0;
 
	if (mField[moveAction->getNewX()][moveAction->getNewY()] == CeilType::WALL ||
		mField[moveAction->getNewX()][moveAction->getNewY()] == CeilType::CREATURE)
	{
		dLife = 0;
	}
	else
	{
		if (mField[moveAction->getNewX()][moveAction->getNewY()] == FOOD)
		{
			dLife = 10;
		}
		else if (mField[moveAction->getNewX()][moveAction->getNewY()] == POISON)
		{
			dLife = -100;
		}

		mField[moveAction->getNewX()][moveAction->getNewY()] = CREATURE;
		mField[moveAction->getOldX()][moveAction->getOldY()] = EMPTY;
	}

	response = new MoveResponse(dLife);

	return response;
}
//--------------------------------------------------------------------------------
Response* 
Environment::lookAction(Action* aLookAction)
{
	Response* response = NULL;
	LookAction* lookAction = static_cast<LookAction*>(aLookAction);
	LookResponse::CeilType ceilType;

	if (mField[lookAction->getX()][lookAction->getY()] == CeilType::EMPTY)
	{
		ceilType = LookResponse::CeilType::EMPTY;
	}
	else if (mField[lookAction->getX()][lookAction->getY()] == CeilType::FOOD)
	{
		ceilType = LookResponse::CeilType::FOOD;
	}
	else if (mField[lookAction->getX()][lookAction->getY()] == CeilType::POISON)
	{
		ceilType = LookResponse::CeilType::POISON;
	}
	else if (mField[lookAction->getX()][lookAction->getY()] == CeilType::WALL)
	{
		ceilType = LookResponse::CeilType::WALL;
	}
	else if (mField[lookAction->getX()][lookAction->getY()] == CeilType::CREATURE)
	{
		ceilType = LookResponse::CeilType::CREATURE;
	}

	response = new LookResponse(ceilType);

	return response;
}
//--------------------------------------------------------------------------------
Response* 
Environment::takeAction(Action* aTakeAction)
{
	Response* response = NULL;
	LookAction* takeAction = static_cast<LookAction*>(aTakeAction);

	sint_16 dLife = 0;
	if (mField[takeAction->getX()][takeAction->getY()] == FOOD)
	{
		dLife = 10;
		mField[takeAction->getX()][takeAction->getY()] = EMPTY;
	}
	else if (mField[takeAction->getX()][takeAction->getY()] == POISON)
	{
		mField[takeAction->getX()][takeAction->getY()] = FOOD;
	}

	response = new TakeResponse(dLife);
	return response;
}
//--------------------------------------------------------------------------------
Response* 
Environment::turnAction(Action* aTurnAction)
{
	Response* response = NULL;
	MoveAction* turnAction = static_cast<MoveAction*>(aTurnAction);
	return response;
}
//--------------------------------------------------------------------------------
Response* 
Environment::dieAction(Action* aDieAction)
{
	Response* response = NULL;
	MoveAction* dieAction = static_cast<MoveAction*>(aDieAction);
	return response;
}
//--------------------------------------------------------------------------------
void
Environment::fillField()
{

}
//--------------------------------------------------------------------------------
void
Environment::setCreatures()
{

}
//--------------------------------------------------------------------------------