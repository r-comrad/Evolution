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

private:
	std::vector<std::vector<CeilType>> mField;

	// TODO: to std::list mb
	std::queue<Point> mCoordinates;

	std::queue<Point> mFood;
	std::queue<Point> mPoison;

	Response* gotoAction(Action* aGotoAction);
	Response* moveAction(Action* aMoveAction, Point aPosition, Point& aNewPosition);
	Response* lookAction(Action* aLookAction, Point aPosition);
	Response* takeAction(Action* aTakeAction, Point aPosition);
	Response* turnAction(Action* aTurnAction);
	Response* dieAction(Action* aDieAction, Point aPosition);

	void fillField();
	void setCreatures();
};

#endif // ENVIRONMENT_H