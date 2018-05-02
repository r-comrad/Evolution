#include "response.h"

//--------------------------------------------------------------------------------
// Response implementation
//--------------------------------------------------------------------------------

Response::Response(ActionType aActionType) :
	mActionType(aActionType)
{}
//--------------------------------------------------------------------------------
GotoResponse::GotoResponse() :
	Response(ActionType::GOTO)
{}
//--------------------------------------------------------------------------------
MoveResponse::MoveResponse(sint_16 aDLife) :
	Response(ActionType::MOVE),
	mDLife(aDLife)
{}
//--------------------------------------------------------------------------------
LookResponse::LookResponse(CeilType aCeilType) :
	Response(ActionType::LOOK),
	mCeilType(aCeilType)
{}
//--------------------------------------------------------------------------------
TakeResponse::TakeResponse(sint_16 aDLife) :
	Response(ActionType::TAKE),
	mDLife(aDLife)
{}
//--------------------------------------------------------------------------------
TurnResponse::TurnResponse() :
	Response(ActionType::TURN)
{}
//--------------------------------------------------------------------------------