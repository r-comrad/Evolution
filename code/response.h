#ifndef RESPONSE_H
#define RESPONSE_H

#include "domain.h"
#include "action.h"

class Response
{
public:

	ActionType mActionType;

	Response(ActionType aActionType, bool aCompletActionFlag);

	bool isCompletAction();

private:
	bool mCompletActionFlag;
};

class GotoResponse : public Response
{
public:

	GotoResponse(bool aCompletActionFlag);
};

class MoveResponse : public Response
{
public:

	sint_16 mDLife;

	MoveResponse(sint_16 aDLife, bool aCompletActionFlag);
};

class LookResponse : public Response
{
public:

	enum CeilType { EMPTY, FOOD, POISON, WALL, CREATURE };
	CeilType mCeilType;

	LookResponse(CeilType aCeilType, bool aCompletActionFlag);
};

class TakeResponse : public Response
{
public:

	sint_16 mDLife;

	TakeResponse(sint_16 aDLife, bool aCompletActionFlag);
};

class TurnResponse : public Response
{
public:

	TurnResponse(bool aCompletActionFlag);
};

class DieResponse : public Response
{
public:

	DieResponse(bool aCompletActionFlag);
};

#endif // RESPONSE_H