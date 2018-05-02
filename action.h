#ifndef ACTION_H
#define ACTION_H

#include "domain.h"

enum ActionType { GOTO, MOVE, LOOK, TAKE, TURN, DIE };

class Action
{
public:

	ActionType mActionType;

	Action(ActionType aActionType);

	bool isCompletAction();
};

class GotoAction : public Action
{
public:

	GotoAction();
};

class MoveAction : public Action
{
public:

	MoveAction(Direction aDirection);

	uint_8 getOldX();
	uint_8 getOldY();

	uint_8 getNewX();
	uint_8 getNewY();

	void setCoordinate(Point aCoordinate); // существо не знает своих координат

private:

	Direction mDirection;
	Point mOldCoordinate, mNewCoordinate;
};

class LookAction : public Action
{
public:

	LookAction(Direction aDirection);

	uint_8 getX();
	uint_8 getY();

	void setCoordinate(Point aCoordinate);

private:

	Direction mDirection;
	Point mCoordinate;
};

class TakeAction : public Action
{
public:

	TakeAction(Direction aDirection);

	uint_8 getX();
	uint_8 getY();

	void setCoordinate(Point aCoordinate);

private:

	Direction mDirection;
	Point mCoordinate;
};

class TurnAction : public Action
{
public:

	TurnAction();
};

class DieAction : public Action
{
public:

	DieAction();
};

#endif // ACTION_H