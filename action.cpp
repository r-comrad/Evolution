#include "action.h"

//--------------------------------------------------------------------------------
// Actions implementation
//--------------------------------------------------------------------------------

Action::Action(ActionType aActionType) :
	mActionType	(aActionType)
{}
//--------------------------------------------------------------------------------
bool
Action::isCompletAction()
{
	return mActionType == MOVE || mActionType == TAKE || mActionType == DIE;
}
//--------------------------------------------------------------------------------
GotoAction::GotoAction() :
	Action		(ActionType::GOTO)
{}
//--------------------------------------------------------------------------------
MoveAction::MoveAction(Direction aDirection) :
	Action		(ActionType::MOVE),
	mDirection	(aDirection)
{}
//--------------------------------------------------------------------------------
uint_8 
MoveAction::getOldX()
{
	return mOldCoordinate.mX;
}
//--------------------------------------------------------------------------------
uint_8 
MoveAction::getOldY()
{
	return mOldCoordinate.mX;
}
//--------------------------------------------------------------------------------
uint_8 
MoveAction::getNewX()
{
	return mNewCoordinate.mX;
}
//--------------------------------------------------------------------------------
uint_8 
MoveAction::getNewY()
{
	return mNewCoordinate.mX;
}
//--------------------------------------------------------------------------------
void MoveAction::setCoordinate(Point aCoordinate)
{
	mOldCoordinate = aCoordinate;
	mNewCoordinate = aCoordinate + mDirection;
}
//--------------------------------------------------------------------------------
LookAction::LookAction(Direction aDirection) :
	Action		(ActionType::LOOK),
	mDirection	(aDirection)
{}
//--------------------------------------------------------------------------------
uint_8 
LookAction::getX()
{
	return mCoordinate.mX;
}
//--------------------------------------------------------------------------------
uint_8 
LookAction::getY()
{
	return mCoordinate.mX;
}
//--------------------------------------------------------------------------------
void LookAction::setCoordinate(Point aCoordinate)
{
	mCoordinate = aCoordinate + mDirection;
}
//--------------------------------------------------------------------------------
TakeAction::TakeAction(Direction aDirection) :
	Action		(ActionType::TAKE),
	mDirection	(aDirection)
{}
//--------------------------------------------------------------------------------
uint_8 
TakeAction::getX()
{
	return mCoordinate.mX;
}
//--------------------------------------------------------------------------------
uint_8 
TakeAction::getY()
{
	return mCoordinate.mX;
}
//--------------------------------------------------------------------------------
void TakeAction::setCoordinate(Point aCoordinate)
{
	mCoordinate = aCoordinate + mDirection;
}
//--------------------------------------------------------------------------------
TurnAction::TurnAction() :
	Action		(ActionType::TURN)
{}
//--------------------------------------------------------------------------------
DieAction::DieAction() :
	Action		(ActionType::DIE)
{}
//--------------------------------------------------------------------------------