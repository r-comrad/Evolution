#ifndef OBJECT_H
#define OBJECT_H

#include <vector>

#include "domain.h"
#include "action.h"

class Object
{
public:

	enum ObjectType { EMPTY = 0, FOOD, POISON, WALL, CREATURE };
	enum ObjectAction { DIE = -1, NON = 0, LOOK, EAT, ACTION, MOVE};

	struct Action
	{
		ObjectAction mObjectAction;
		int mX, mY;
	};

	ObjectType mObjectType;

	Object();

	virtual Action* getAction() const;
	const ObjectType& getType() const;
	virtual std::vector<Object*> multiply(int aChildCount) const;
	virtual bool update(std::vector<int> aResponce);
	void mutate(uint_8 aMutCount);
};

#endif // OBJECT_H