#include "response.h"

//--------------------------------------------------------------------------------
// Response implementation
//--------------------------------------------------------------------------------

Response::Response(ActionType aActionType, bool aCompletActionFlag) :
	mActionType(aActionType)
{
	mCompletActionFlag = aCompletActionFlag;
}
//--------------------------------------------------------------------------------
bool
Response::isCompletAction()
{
	return mCompletActionFlag;
}
//--------------------------------------------------------------------------------
GotoResponse::GotoResponse(bool aCompletActionFlag) :
	Response(ActionType::GOTO, aCompletActionFlag)
{}
//--------------------------------------------------------------------------------
MoveResponse::MoveResponse(sint_16 aDLife, bool aCompletActionFlag) :
	Response(ActionType::MOVE, aCompletActionFlag),
	mDLife(aDLife)
{}
//--------------------------------------------------------------------------------
LookResponse::LookResponse(CeilType aCeilType, bool aCompletActionFlag) :
	Response(ActionType::LOOK, aCompletActionFlag),
	mCeilType(aCeilType)
{}
//--------------------------------------------------------------------------------
TakeResponse::TakeResponse(sint_16 aDLife, bool aCompletActionFlag) :
	Response(ActionType::TAKE, aCompletActionFlag),
	mDLife(aDLife)
{}
//--------------------------------------------------------------------------------
TurnResponse::TurnResponse(bool aCompletActionFlag) :
	Response(ActionType::TURN, aCompletActionFlag)
{}
//--------------------------------------------------------------------------------
DieResponse::DieResponse(bool aCompletActionFlag) :
	Response(ActionType::DIE, aCompletActionFlag)
{}
//--------------------------------------------------------------------------------