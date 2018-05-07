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

	reset();
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

	if (aAction->mActionType == ActionType::GOTO)
	{
		response = gotoAction(aAction);
	}
	else if (aAction->mActionType == ActionType::MOVE)
	{
		// TODO curPosition?
		response = moveAction(aAction, curPosition, curPosition);
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

	if (aAction->isCompletAction())
	{
		mCoordinates.pop();
		if (!(aAction->mActionType == ActionType::DIE))
		{
			mCoordinates.push(curPosition);
		}
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
std::list<Point>
Environment::getCreaturesCoordinates()
{
	std::list<Point> result;

	for (uint_8 i = 0; i < mCoordinates.size(); ++i)
	{
		Point point = mCoordinates.front();
		mCoordinates.pop();

		result.emplace_back(point);
		mCoordinates.push(point);
	}

	return result;
}
//--------------------------------------------------------------------------------
void 
Environment::reset()
{
	while (!mCoordinates.empty())
	{
		mCoordinates.pop();
	}
	while (!mFood.empty())
	{
		mFood.pop();
	}
	while (!mPoison.empty())
	{
		mPoison.pop();
	}

	for (uint_16 i = 1; i < N - 1; ++i)
	{
		for (uint_16 j = 1; j < M - 1; ++j)
		{
			mField[i][j] = CeilType::EMPTY;
		}
	}

	fillField();
	setCreatures();
}
//--------------------------------------------------------------------------------
Response* 
Environment::gotoAction(Action* aGotoAction)
{
	Response* response = NULL;
	GotoAction* gotoAction = static_cast<GotoAction*>(aGotoAction);
	response = new GotoResponse();
	return response;
}
//--------------------------------------------------------------------------------
Response* 
Environment::moveAction(Action* aMoveAction, Point aPosition, Point& aNewPosition)
{
	Response* response = NULL;
	MoveAction* moveAction = static_cast<MoveAction*>(aMoveAction);
	moveAction->setCoordinate(aPosition);
	sint_16 dLife = 0;

	//if (moveAction->getNewX() >= (N - 1) || moveAction->getNewY() >= (M - 1))
	//{
	//	int y = 0;
	//	++y;
	//	cout << y;
	//}
 
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

		// TODO: переделать action, возращать Point, использовать функции Point для получения координат
		aNewPosition = Point(moveAction->getNewX(), moveAction->getNewY());
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

	//if (lookAction->getX() >= N || lookAction->getY() >= M)
	//{
	//	int y = 0;
	//	++y;
	//	cout << y;
	//}

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
	TakeAction* takeAction = static_cast<TakeAction*>(aTakeAction);
	takeAction->setCoordinate(aPosition);

	//if (takeAction->getX() >= N || takeAction->getY() >= M)
	//{
	//	int y = 0;
	//	++y;
	//	cout << y;
	//}

	sint_16 dLife = 0;
	//int rr = takeAction->getX();
	//int rrr = takeAction->getY();
	//mField[rr];
	//mField[rr][rrr];
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
	TurnAction* turnAction = static_cast<TurnAction*>(aTurnAction);
	response = new TurnResponse();
	return response;
}
//--------------------------------------------------------------------------------
Response* 
Environment::dieAction(Action* aDieAction, Point aPosition)
{
	mField[aPosition.mX][aPosition.mY] = EMPTY;

	Response* response = NULL;
	DieAction* dieAction = static_cast<DieAction*>(aDieAction);
	response = new DieResponse();
	return response;
}
//--------------------------------------------------------------------------------
void
Environment::fillField()
{
	int base = 600;
	for (int i = 0; i < base;)
	{
		int x = rnd1(N - 1) + 1;
		int y = rnd1(M - 1) + 1;

		if (mField[x][y] != CeilType::EMPTY)
		{
			continue;
		}
		mField[x][y] = CeilType::FOOD;
		mFood.emplace(x, y);
		++i;
	}

	for (int i = 0; i < base / 2;)
	{
		int x = rnd1(N - 1) + 1;
		int y = rnd1(M - 1) + 1;

		if (mField[x][y] != CeilType::EMPTY) continue;
		mField[x][y] = CeilType::POISON;
		mPoison.emplace(x, y);
		++i;
	}

	for (int i = 0; i < base / 3;)
	{
		int x = rnd1(N - 1) + 1;
		int y = rnd1(M - 1) + 1;

		if (mField[x][y] != CeilType::EMPTY) continue;
		mField[x][y] = CeilType::WALL;
		mPoison.emplace(x, y);
		++i;
	}
}
//--------------------------------------------------------------------------------
void
Environment::setCreatures()
{
	for (int i = 0; i < 64;)
	{
		int x = rnd1(N - 1) + 1;
		int y = rnd1(M - 1) + 1;

		if (mField[x][y] != CeilType::EMPTY) continue;
		mField[x][y] = CeilType::CREATURE;
		mCoordinates.emplace(x, y);
		++i;
	}
}
//--------------------------------------------------------------------------------