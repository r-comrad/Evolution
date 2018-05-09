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

	for (auto& i : mProgram) i = rnd1(MAX_PROGRAM_WORD_VALUE + 1);
		//mProgram = 
		//{
		//	129, 7, 7, 65, 193, 7, 0, 258,
		//	129, 15, 15, 65, 193, 15, 0, 258,
		//	129, 23, 23, 65, 193, 23, 0, 258,
		//	129, 31, 31, 65, 193, 31, 0, 258,
		//	129, 39, 39, 65, 193, 39, 0, 258,
		//	129, 47, 47, 65, 193, 47, 0, 258,
		//	129, 55, 55, 65, 193, 55, 0, 258,
		//	258, 64
		//};


	if (programDecoder.size() == 0)
	{
		programDecoder.insert(std::pair<std::pair<uint_16, uint_16>, ActionType>
			(std::make_pair(0, 63), ActionType::GOTO));
		programDecoder.insert(std::pair<std::pair<uint_16, uint_16>, ActionType>
			(std::make_pair(64, 127), ActionType::MOVE));
		programDecoder.insert(std::pair<std::pair<uint_16, uint_16>, ActionType>
			(std::make_pair(128, 191), ActionType::LOOK));
		programDecoder.insert(std::pair<std::pair<uint_16, uint_16>, ActionType>
			(std::make_pair(192, 256), ActionType::TAKE));
		programDecoder.insert(std::pair<std::pair<uint_16, uint_16>, ActionType>
			(std::make_pair(257, 319), ActionType::TURN));
	}
}
//--------------------------------------------------------------------------------
Creature::~Creature()
{}
//--------------------------------------------------------------------------------
Action*
Creature::getAction()
{
	uint_16 curCommand = mProgram[mPrCount];
	std::map<std::pair<uint_16, uint_16>, ActionType, PairCmp> ::iterator
		it = programDecoder.find(std::make_pair(curCommand, curCommand));
	ActionType actionType = it->second;

	Action* result = NULL; 
	if (mLife < 1)
	{
		result = new DieAction();
	}
	else if (actionType == ActionType::GOTO)
	{
		mPrCount = curCommand;
		result = new GotoAction();
	}
	else  if (actionType == ActionType::MOVE)
	{
		incPrCount();
		result = new MoveAction(mDirection);
	}
	else if (actionType == ActionType::LOOK)
	{
		incPrCount(0);
		result = new LookAction(mDirection);
	}
	else if (actionType == ActionType::TAKE)
	{
		incPrCount();
		result = new TakeAction(mDirection);
	}
	else if (actionType == ActionType::TURN)
	{
		++mDirection;
		incPrCount();
		result = new TurnAction();	
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

	delete(aResponse);			// TODO
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