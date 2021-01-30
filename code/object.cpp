#include "object.h"

//--------------------------------------------------------------------------------
// Object implementation
//--------------------------------------------------------------------------------

Object::Object()
{}
//--------------------------------------------------------------------------------
Object::Action*
Object::getAction() const
{
	Action* action = new Action();
	action->mObjectAction = new Object::ObjectAction(NON);
	return action;
}
//--------------------------------------------------------------------------------
const Object::ObjectType&
Object::getType() const
{
	return mObjectType;
}
//--------------------------------------------------------------------------------
std::vector<Object*> 
Object::multiply(int aChildCount) const
{
	return {};
}
//--------------------------------------------------------------------------------
void
Object::update(std::vector<int>)
{}
//--------------------------------------------------------------------------------
