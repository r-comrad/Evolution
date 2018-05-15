#include "environment.h"

//--------------------------------------------------------------------------------
// Enviroment implementation
//--------------------------------------------------------------------------------

#define N (105 + 2)
#define M (75 + 2)

#define MAX_WATCHING_TIME 20

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

	Point curPosition = *mCurentCoordinate;

	if (aAction->mActionType == ActionType::GOTO)
	{
		response = gotoAction(aAction);
	}
	else if (aAction->mActionType == ActionType::MOVE)
	{
		// TODO curPosition?
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

	//delete(aAction); //TODO?

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
	return mCoordinates;
}
//--------------------------------------------------------------------------------
void 
Environment::reset()
{
	mCoordinates.clear();
	fillField();
	setCreatures();
	mCurentCoordinate = mCoordinates.begin();
}
//--------------------------------------------------------------------------------
void
Environment::step()
{
	++mCurentCoordinate;
	if (mCurentCoordinate == mCoordinates.end())
	{
		mCurentCoordinate = mCoordinates.begin();
	}
	// TODO mCurentCoordinate = mCoordinates.begin() после эволюции?

	for (int i = 0; i < 2; ++i)
		if (mFood.size() > 0)
		{
			Point p = mFood.front();
			mFood.pop();
			if (mField[p.mX][p.mY] == CeilType::EMPTY)
				mField[p.mX][p.mY] = CeilType::FOOD;
			else mFood.push(p);
		}
	for (int i = 0; i < 2; ++i)
		if (mPoison.size() > 0)
		{
			Point p = mPoison.front();
			mPoison.pop();
			if (mField[p.mX][p.mY] == CeilType::EMPTY)
				mField[p.mX][p.mY] = CeilType::POISON;
			else mPoison.push(p);
		}
	//for (int i = 0; i < 2; ++i)
		//if (food > 0)
	//while (food > 0)
		//{
		//	uint_8 x = 0;
		//	uint_8 y = 0;

		//	while (mField[x][y] != CeilType::EMPTY)
		//	{
		//		x = rnd1(N - 1) + 1;
		//		y = rnd1(M - 1) + 1;
		//	}
		//	mField[x][y] = CeilType::FOOD;
		//	--food;
		//}

	//for (int i = 0; i < 2; ++i)
	//	if (poison > 0)
	////while (poison > 0)
	//	{
	//		uint_8 x = 0;
	//		uint_8 y = 0;

	//		while (mField[x][y] != CeilType::EMPTY)
	//		{
	//			x = rnd1(N - 1) + 1;
	//			y = rnd1(M - 1) + 1;
	//		}
	//		mField[x][y] = CeilType::POISON;
	//		--poison;
	//	}

}
//--------------------------------------------------------------------------------
Response* 
Environment::gotoAction(Action* aGotoAction)
{
	Response* response = NULL;
	GotoAction* gotoAction = static_cast<GotoAction*>(aGotoAction);
	response = new GotoResponse(gotoAction->isCompletAction());
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

	//if (moveAction->getNewX() >= (N - 1) || moveAction->getNewY() >= (M - 1))
	//{
	//	int y = 0;
	//	++y;
	//	cout << y;
	//}
 
	uint_8 x = moveAction->getNewX();
	uint_8 y = moveAction->getNewY();
	if (mField[x][y] == CeilType::WALL || mField[x][y] == CeilType::CREATURE)
	{
		dLife = 0;
	}
	else
	{
		if (mField[x][y] == FOOD)
		{
			dLife = 10;
			//food++;
			mFood.push(aPosition);
		}
		else if (mField[x][y] == POISON)
		{
			dLife = -100;
			//poison--;
			mPoison.push(aPosition);
		}

		mField[x][y] = CREATURE;
		mField[moveAction->getOldX()][moveAction->getOldY()] = EMPTY;

		// TODO: переделать action, возращать Point, использовать функции Point для получения координат
		*mCurentCoordinate = Point(x, y);
	}

	response = new MoveResponse(dLife, moveAction->isCompletAction());

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

	response = new LookResponse(ceilType, lookAction->isCompletAction());

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
	uint_8 x = takeAction->getX();
	uint_8 y = takeAction->getY();
	if (mField[x][y] == FOOD)
	{
		dLife = 10;
		mField[x][y] = EMPTY;
		//food++;
		mFood.push(aPosition);
	}
	else if (mField[x][y] == POISON)
	{
		mField[x][y] = FOOD;
		mPoison.push(aPosition);
		//poison++;
		//food--;
	}

	response = new TakeResponse(dLife, takeAction->isCompletAction());
	return response;
}
//--------------------------------------------------------------------------------
Response* 
Environment::turnAction(Action* aTurnAction)
{
	Response* response = NULL;
	TurnAction* turnAction = static_cast<TurnAction*>(aTurnAction);
	response = new TurnResponse(turnAction->isCompletAction());
	return response;
}
//--------------------------------------------------------------------------------
Response* 
Environment::dieAction(Action* aDieAction, Point aPosition)
{
	mField[aPosition.mX][aPosition.mY] = EMPTY;

	Response* response = NULL;
	DieAction* dieAction = static_cast<DieAction*>(aDieAction);
	response = new DieResponse(dieAction->isCompletAction());

	std::list<Point> ::iterator it = mCurentCoordinate;
	if (mCurentCoordinate != mCoordinates.begin()) --mCurentCoordinate;
	else mCurentCoordinate = --mCoordinates.end();
	mCoordinates.erase(it);
	

	return response;
}
//--------------------------------------------------------------------------------
void
Environment::fillField()
{
	//int base = 600;
	//for (int i = 0; i < base;)
	//{
	//	int x = rnd1(N - 1) + 1;
	//	int y = rnd1(M - 1) + 1;

	//	if (mField[x][y] != CeilType::EMPTY)
	//	{
	//		continue;
	//	}
	//	mField[x][y] = CeilType::FOOD;
	//	mFood.emplace(x, y);
	//	++i;
	//}

	//for (int i = 0; i < base / 2;)
	//{
	//	int x = rnd1(N - 1) + 1;
	//	int y = rnd1(M - 1) + 1;

	//	if (mField[x][y] != CeilType::EMPTY) continue;
	//	mField[x][y] = CeilType::POISON;
	//	mPoison.emplace(x, y);
	//	++i;
	//}

	//for (int i = 0; i < base / 3;)
	//{
	//	int x = rnd1(N - 1) + 1;
	//	int y = rnd1(M - 1) + 1;

	//	if (mField[x][y] != CeilType::EMPTY) continue;
	//	mField[x][y] = CeilType::WALL;
	//	mPoison.emplace(x, y);
	//	++i;
	//}

	//for (int i = 1; i < mField.size() - 1; ++i)
	//{
	//	for (int j = 1; j < mField[0].size() - 1; ++j)
	//	{
	//		int num = rnd1(101);

	//		if (setCeil(num, 0 + 20, mField[i][j], FOOD));
	//		else if (setCeil(num, 20 + 10, mField[i][j], POISON));
	//		else if (setCeil(num, 30 + 10, mField[i][j], WALL));
	//		else mField[i][j] = EMPTY;
	//	}
	//}

	for (int j = 1; j < mField.size() - 1; ++j)
	{
		for (int k = 1; k <  mField[0].size() - 1; ++k)
		{
			mField[j][k] = EMPTY;
		}
	}

	for (int i = 0; i < 20; ++i)
	{

		int x = rnd1(N - 6) + 4;
		int y = rnd1(M - 6) + 4;

		for (int j = 0; j < 3; ++j)
		{
			for (int k = 0; k < 3; ++k)
			{
				mField[x + j][y + k] = FOOD;
				mField[x - j][y - k] = FOOD;
				mField[x + j][y - k] = FOOD;
				mField[x - j][y + k] = FOOD;
			}
		}

		mField[x][y] = WALL;
	}

	for (int i = 0; i < 10; ++i)
	{

		int x = rnd1(N - 6) + 4;
		int y = rnd1(M - 6) + 4;

		for (int j = 0; j < 3; ++j)
		{
			for (int k = 0; k < 3; ++k)
			{
				mField[x + j][y + k] = POISON;
				mField[x - j][y - k] = POISON;
				mField[x + j][y - k] = POISON;
				mField[x - j][y + k] = POISON;
			}
		}

		mField[x][y] = WALL;
	}
}
//--------------------------------------------------------------------------------
bool
Environment::setCeil(uint_16 aNum, uint_16 aPr, CeilType& aCeil, CeilType aCeilTypes)
{
	bool result = false;

	if (aNum <= aPr)
	{
		aCeil = aCeilTypes;
		result = true;
	}

	return result;
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
		mCoordinates.emplace_back(x, y);
		++i;
	}
}
//--------------------------------------------------------------------------------