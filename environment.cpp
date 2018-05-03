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
}
//--------------------------------------------------------------------------------
Environment::~Environment()
{}
//--------------------------------------------------------------------------------
Response*
Environment::process(Action* aAction)
{
	Response* response = NULL;

	Point curPosition = mCoordinates.front();
	mCoordinates.pop();

	for (uint_8 i = 0; i < MAX_WATCHING_TIME; ++i)
	{
		if (aAction->mActionType == ActionType::GOTO)
		{
			response = gotoAction(aAction);
		}
		else if (aAction->mActionType == ActionType::MOVE)
		{
			response = moveAction(aAction, curPosition);
		}
		else if (aAction->mActionType == ActionType::LOOK)
		{
			response = lookAction(aAction, curPosition);
		}
		else if (aAction->mActionType == ActionType::TAKE)
		{
			response = takeAction(aAction, curPosition);
		}
		else if (aAction->mActionType == ActionType::TURN)
		{
			response = turnAction(aAction);
		}
		else if (aAction->mActionType == ActionType::DIE)
		{
			response = dieAction(aAction, curPosition);
		}
	}

	if (!aAction->mActionType == ActionType::DIE)
	{
		mCoordinates.push(curPosition);
	}
	
	delete(aAction);

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
Environment::moveAction(Action* aMoveAction, Point aPosition)
{
	Response* response = NULL;
	MoveAction* moveAction = static_cast<MoveAction*>(aMoveAction);
	moveAction->setCoordinate(aPosition);
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
Environment::lookAction(Action* aLookAction, Point aPosition)
{
	Response* response = NULL;
	LookAction* lookAction = static_cast<LookAction*>(aLookAction);
	lookAction->setCoordinate(aPosition);
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
Environment::takeAction(Action* aTakeAction, Point aPosition)
{
	Response* response = NULL;
	LookAction* takeAction = static_cast<LookAction*>(aTakeAction);
	takeAction->setCoordinate(aPosition);

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
Environment::dieAction(Action* aDieAction, Point aPosition)
{
	mField[aPosition.mX][aPosition.mY] = EMPTY;

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