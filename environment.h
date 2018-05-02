#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <queue>
#include <list>
#include <vector>

#include "creature.h"
#include "object.h"

#define N (105 + 2)
#define M (75 + 2)

//#define CREATURE_MAX_COUNT 64
//#define CREATURE_MIN_COUNT 8

//#define DRAW_DX 20
//#define DRAW_DY 20
//#define MAX_TURN_SIZE 20
#define MAX_WATCHING_TIME 20

//enum LifeStatus { NaturalSelection, RequiresEvolution };

enum CeilType { EMPTY, FOOD, POISON, WALL, CREATURE };

class Environment
{
public:
	

	Environment();
	~Environment();

	Response* process(Action* action);
	const std::vector<std::vector<CeilType>>& getField() const;

private:
	std::vector<std::vector<CeilType>> mField;

	std::queue<Point> mCoordinates;

	Response* gotoAction(Action* aGotoAction);
	Response* moveAction(Action* aMoveAction);
	Response* lookAction(Action* aLookAction);
	Response* takeAction(Action* aTakeAction);
	Response* turnAction(Action* aTurnAction);
	Response* dieAction(Action* aDieAction);

	void fillField();
	void setCreatures();
};

#endif // ENVIRONMENT_H