#ifndef OBJECT_H
#define OBJECT_H

#include "domain.h"
#include "action.h"

class Object
{
public:

	enum ObjectType { EMPTY, FOOD, POISON, WALL, CREATURE };
	ObjectType mObjectType;

	Object();

	virtual Action* action() = 0;

	bool isEmpty();
	bool isFood();
	bool isPoison();
	bool isWall();
	bool isCreature();
};

#endif // OBJECT_H