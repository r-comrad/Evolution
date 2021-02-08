#include "creature.h"

//--------------------------------------------------------------------------------
// Creature implementation
//--------------------------------------------------------------------------------

//Creature::Creature()
//{}
//--------------------------------------------------------------------------------
Creature::Creature() :
	mProgram	(PROGRAM_SIZE)
{
	reset();
}
//--------------------------------------------------------------------------------
Creature::~Creature()
{}
//--------------------------------------------------------------------------------

const Creature::Direction&
operator++(Creature::Direction& aDir)
{
	Creature::Direction::Down;
	switch (aDir)
	{
		case Creature::Direction::Up		:	return aDir = Creature::Direction::UpRight;
		case Creature::Direction::UpRight	:	return aDir = Creature::Direction::Right;
		case Creature::Direction::Right		:	return aDir = Creature::Direction::DownRight;
		case Creature::Direction::DownRight	:	return aDir = Creature::Direction::Down;
		case Creature::Direction::Down		:	return aDir = Creature::Direction::DownLeft;
		case Creature::Direction::DownLeft	:	return aDir = Creature::Direction::Left;
		case Creature::Direction::Left		:	return aDir = Creature::Direction::UpLeft;
		case Creature::Direction::UpLeft	:	return aDir = Creature::Direction::Up;
	}
}

const Creature::Direction
operator++(Creature::Direction& aDir, int)
{
	switch (aDir)
	{
		case Creature::Direction::Up		:	return aDir = Creature::Direction::UpRight;
		case Creature::Direction::UpRight	:	return aDir = Creature::Direction::Right;
		case Creature::Direction::Right		:	return aDir = Creature::Direction::DownRight;
		case Creature::Direction::DownRight	:	return aDir = Creature::Direction::Down;
		case Creature::Direction::Down		:	return aDir = Creature::Direction::DownLeft;
		case Creature::Direction::DownLeft	:	return aDir = Creature::Direction::Left;
		case Creature::Direction::Left		:	return aDir = Creature::Direction::UpLeft;
		case Creature::Direction::UpLeft	:	return aDir = Creature::Direction::Up;
	}
}

const Creature::Direction&
operator--(Creature::Direction& aDir)
{
	switch (aDir)
	{
		case Creature::Direction::Up		:	return aDir = Creature::Direction::UpLeft;
		case Creature::Direction::UpRight	:	return aDir = Creature::Direction::Up;
		case Creature::Direction::Right		:	return aDir = Creature::Direction::UpRight;
		case Creature::Direction::DownRight	:	return aDir = Creature::Direction::Right;
		case Creature::Direction::Down		:	return aDir = Creature::Direction::DownRight;
		case Creature::Direction::DownLeft	:	return aDir = Creature::Direction::Down;
		case Creature::Direction::Left		:	return aDir = Creature::Direction::DownLeft;
		case Creature::Direction::UpLeft	:	return aDir = Creature::Direction::Left;
	}
}

const Creature::Direction
operator--(Creature::Direction& aDir, int)
{
	switch (aDir)
	{
		case Creature::Direction::Up		:	return aDir = Creature::Direction::UpLeft;
		case Creature::Direction::UpRight	:	return aDir = Creature::Direction::Up;
		case Creature::Direction::Right		:	return aDir = Creature::Direction::UpRight;
		case Creature::Direction::DownRight	:	return aDir = Creature::Direction::Right;
		case Creature::Direction::Down		:	return aDir = Creature::Direction::DownRight;
		case Creature::Direction::DownLeft	:	return aDir = Creature::Direction::Down;
		case Creature::Direction::Left		:	return aDir = Creature::Direction::DownLeft;
		case Creature::Direction::UpLeft	:	return aDir = Creature::Direction::Left;
	}
}

Object::Action*
Creature::getAction() const
{
	Object::Action* result = Object::getAction();
	uint_16 curCommand = mProgram[mPrCount];

	Object::ObjectAction result;
	if (mLife < 1)
	{
		result->mObjectAction = Object::ObjectAction::DIE;
	}
	else if (curCommand == CreatureComands::LOOK)
	{
		result->mObjectAction = Object::ObjectAction::LOOK;
		Acr
	}
	else  if (curCommand == CreatureComands::TURN)
	{
		result->mObjectAction = Object::ObjectAction::NON;
	}
	else if (curCommand == CreatureComands::EAT)
	{
		result->mObjectAction = Object::ObjectAction::EAT;
	}
	else if (curCommand == CreatureComands::ACTION)
	{
		result->mObjectAction = Object::ObjectAction::ACTION;
	}
	else if (curCommand == CreatureComands::MOVE)
	{
		result->mObjectAction = Object::ObjectAction::MOVE;
	}
	else if (curCommand == CreatureComands::GOTO)
	{
		result->mObjectAction = Object::ObjectAction::NON;

	}

	return result;
}
//--------------------------------------------------------------------------------
void
Creature::processResponses(Response* aResponse)
{
	if (aResponse->mActionType == ActionType::GOTO)
	{}
	else if (aResponse->mActionType == ActionType::MOVE)
	{
		MoveResponse* moveResponse = static_cast<MoveResponse*>(aResponse);
		lifeChange(moveResponse->mDLife);
	}
	else if (aResponse->mActionType == ActionType::LOOK)
	{
		LookResponse* lookResponse = static_cast<LookResponse*>(aResponse);

		if (lookResponse->mCeilType == LookResponse::CeilType::EMPTY)
		{
			incPrCount(4);
			//incPrCount(5);
		}
		else  if (lookResponse->mCeilType == LookResponse::CeilType::CREATURE)
		{
			incPrCount(3);
			//mDPrCount = 4;
		}
		else  if (lookResponse->mCeilType == LookResponse::CeilType::FOOD)
		{
			incPrCount(2);
			//mDPrCount = 3;
		}
		else  if (lookResponse->mCeilType == LookResponse::CeilType::POISON)
		{
			incPrCount(1);
			//mDPrCount = 2;
		}
		else  if (lookResponse->mCeilType == LookResponse::CeilType::WALL)
		{
			incPrCount(3);
			//mDPrCount = 1;
		}
	}
	else if(aResponse->mActionType == ActionType::TAKE)
	{
		TakeResponse* takeResponse = static_cast<TakeResponse*>(aResponse);
		lifeChange(takeResponse->mDLife);
	}
	else if (aResponse->mActionType == ActionType::TURN)
	{}
}
//--------------------------------------------------------------------------------
void 
Creature::step()
{
	--mLife;
}
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
	mDirection = Direction(rnd1(8));
	mPrCount = 0;
	std::vector<int> additionalNumbers = {0, 5, 1, 0, 0, 0, 1};
	for (int i = 0; i < mProgram.size(); ++i)
	{
		int num = rnd(1, 6);
		mProgram[i] = num;
		for (int j = 0; j < additionalNumbers[num]; ++j)
		{
			mProgram[i + j + 1] = rnd(1, 8);
		}
	}
}
//--------------------------------------------------------------------------------
bool 
Creature::PairCmp::operator()(const std::pair<uint_16, uint_16>& p1,
	const std::pair<uint_16, uint_16>& p2) const
{
	if (p1.second < p2.first) return true;
	return false;
}
//--------------------------------------------------------------------------------
void 
Creature::mutate(uint_8 aMutCount)
{
	std::set<uint_16> changeNumbers;
	while (changeNumbers.size() < aMutCount &&
		changeNumbers.size() < mProgram.size())
	{
		int num = rnd1(mProgram.size());
		if (changeNumbers.find(num) == changeNumbers.end())
			changeNumbers.insert(num);
	}

	for (const auto& i : changeNumbers)
	{
		mProgram[i] = rnd1(MAX_PROGRAM_WORD_VALUE + 1);
	}
}
//--------------------------------------------------------------------------------
void
Creature::incPrCount(uint_16 aDPrCount)
{
	mPrCount += aDPrCount;

	while (mPrCount >= mProgram.size()) 
		mPrCount -= mProgram.size();
}
//--------------------------------------------------------------------------------
void 
Creature::lifeChange(sint_16 aDLife)
{
	mLife += aDLife;
	if (mLife > MAX_LIFE) mLife = MAX_LIFE;
	if (mLife <= 0) mLife = -100;
}
//--------------------------------------------------------------------------------