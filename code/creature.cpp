#include "creature.h"

//--------------------------------------------------------------------------------
// Creature implementation
//--------------------------------------------------------------------------------

//const Direction Creature::operator++(Direction& aDir, int)
//{
//	return Direction();
//}

//Creature::Creature()
//{}
//--------------------------------------------------------------------------------
Creature::Creature() :
	mProgram	(PROGRAM_SIZE), 
	mDirection	(0)
{
	reset();
}
//--------------------------------------------------------------------------------
Creature::~Creature()
{}
//--------------------------------------------------------------------------------
Object::Action*
Creature::getAction()
{
	//TODO: block comands (LOOK doesn't work correctly, need to goto by 5 comands)

	Object::Action* result = Object::getAction();
	sint_16 curCommand = mProgram[mComandPointer];

	result->mX = mDirection.getX();
	result->mY = mDirection.getY();

	++mActionCount;

	Object::ObjectAction result;
	if (mLife < 1)
	{
		result->mObjectAction = Object::ObjectAction::DIE;
	}
	else if (curCommand == CreatureComands::LOOK)
	{
		result->mObjectAction = Object::ObjectAction::LOOK;
	}
	else  if (curCommand == CreatureComands::TURN)
	{
		result->mObjectAction = Object::ObjectAction::NON;
		incComandPointer(1);
		curCommand = mProgram[mComandPointer];
		curCommand -= 5;
		for (sint_16 i = 0; i < curCommand; ++i) ++mDirection;
		for (sint_16 i = 0; i < -curCommand; ++i) --mDirection;
	}
	else if (curCommand == CreatureComands::EAT)
	{
		result->mObjectAction = Object::ObjectAction::EAT;
		incComandPointer(1);
		mActionCount += 100;
	}
	else if (curCommand == CreatureComands::ACTION)
	{
		result->mObjectAction = Object::ObjectAction::ACTION;
		incComandPointer(1);
		mActionCount += 100;
	}
	else if (curCommand == CreatureComands::MOVE)
	{
		result->mObjectAction = Object::ObjectAction::MOVE;
		incComandPointer(1);
		mActionCount += 100;
	}
	else if (curCommand == CreatureComands::GOTO)
	{
		result->mObjectAction = Object::ObjectAction::NON;
		incComandPointer(1);
		curCommand = mProgram[mComandPointer];
		incComandPointer(curCommand);
	}

	return result;
}

std::vector<Object*>
Creature::multiply(int aChildCount) const
{

}
//--------------------------------------------------------------------------------
bool
Creature::update(std::vector<int> aResponce)
{
	bool result = false;
	uint_16 curCommand = mProgram[mComandPointer];

	if (curCommand == CreatureComands::LOOK)
	{
		if (aResponce[0] == Object::ObjectType::EMPTY) incComandPointer(1);
		else if (aResponce[0] == Object::ObjectType::FOOD) incComandPointer(2);
		else if (aResponce[0] == Object::ObjectType::POISON) incComandPointer(3);
		else if (aResponce[0] == Object::ObjectType::WALL) incComandPointer(4);
		else if (aResponce[0] == Object::ObjectType::CREATURE) incComandPointer(5);
	}

	if (curCommand == CreatureComands::EAT)
	{
		mLife += aResponce[0];
	}
	if (curCommand == CreatureComands::ACTION)
	{
		mLife += aResponce[0];
	}
	if (curCommand == CreatureComands::MOVE)
	{
		mLife += aResponce[0];
	}

	if (mActionCount >= MAX_NINIACTIONS_COUNT)
	{
		result = true;
		mActionCount = 0;
		--mLife;
	}

	return result;
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
sint_16
Creature::getLife() const
{
	return mLife;
}
//--------------------------------------------------------------------------------
void 
Creature::reset()
{
	mLife = 60;
	mDirection = Direction(rnd(0, 8));
	mComandPointer = 0;
	mActionCount = 0;
	//TODO: programm reset?
	//for (int i = 0; i < mProgram.size(); ++i)
	//{
	//	int num = rnd(1, 6);
	//	mProgram[i] = num;
	//	for (int j = 0; j < additionalNumbers[num]; ++j)
	//	{
	//		mProgram[i + j + 1] = rnd(1, 8);
	//	}
	//}
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void 
Creature::mutate(uint_8 aMutCount)
{
	std::set<uint_16> changeNumbers;
	while (changeNumbers.size() < aMutCount &&
		changeNumbers.size() < mProgram.size())
	{
		int num = rnd(0, mProgram.size() - 1);
		changeNumbers.insert(num);
	}

	for (const auto& i : changeNumbers)
	{
		mProgram[i] = rnd1(MAX_PROGRAM_WORD_VALUE + 1);
	}
}
//--------------------------------------------------------------------------------
void
Creature::incComandPointer(uint_16 aValue)
{
	mComandPointer += aValue;

	while (aValue >= mProgram.size())
		aValue -= mProgram.size();
}
//--------------------------------------------------------------------------------
void 
Creature::lifeChange(sint_16 aDLife)
{
	mLife += aDLife;
	if (mLife > MAX_LIFE) mLife = MAX_LIFE;
	if (mLife <= 0) mLife = -5;
}
//--------------------------------------------------------------------------------