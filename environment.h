#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <queue>
#include <list>
#include <vector>

#include "creature.h"

enum CeilType { EMPTY, FOOD, POISON, WALL, CREATURE };

class Environment
{
public:

	Environment();
	~Environment();

	Response* process(Action* aAction);
	const std::vector<std::vector<CeilType>>& getField() const;
	std::list<Point> getCreaturesCoordinates();
	void reset();

	void step();

private:
	std::vector<std::vector<CeilType>> mField;

	// TODO: to std::list mb
	std::list<Point> ::iterator mCurentCoordinate;
	std::list<Point> mCoordinates;

	std::queue<Point> mFood;
	std::queue<Point> mPoison;

	sint_16 poison = 0;
	sint_16 food = 0;

	Response* gotoAction(Action* aGotoAction);
	Response* moveAction(Action* aMoveAction, Point aPosition);
	Response* lookAction(Action* aLookAction, Point aPosition);
	Response* takeAction(Action* aTakeAction, Point aPosition);
	Response* turnAction(Action* aTurnAction);
	Response* dieAction(Action* aDieAction, Point aPosition);

	void fillField();
	bool setCeil(uint_16 aNum, uint_16 aPr, CeilType& aCeil, CeilType aCeilTypes);
	void setCreatures();
};

#endif // ENVIRONMENT_H