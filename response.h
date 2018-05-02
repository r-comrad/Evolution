#ifndef RESPONSE_H
#define RESPONSE_H

#include "domain.h"
#include "action.h"

class Response
{
public:

	ActionType mActionType;

	Response(ActionType aActionType);
};

class GotoResponse : public Response
{
public:

	GotoResponse();
};

class MoveResponse : public Response
{
public:

	sint_16 mDLife;

	MoveResponse(sint_16 aDLife);
};

class LookResponse : public Response
{
public:

	enum CeilType { EMPTY, FOOD, POISON, WALL, CREATURE };
	CeilType mCeilType;

	LookResponse(CeilType aCeilType);
};

class TakeResponse : public Response
{
public:

	sint_16 mDLife;

	TakeResponse(sint_16 aDLife);
};

class TurnResponse : public Response
{
public:

	TurnResponse();
};

#endif // RESPONSE_H