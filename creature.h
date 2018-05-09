#ifndef CREATURE_H
#define CREATURE_H

#include <vector>
#include <map>
#include <set>
#include <list>

#include "domain.h"
#include "response.h"
#include "action.h"

#define MAX_PROGRAM_WORD_VALUE		uint_16(319)
#define MAX_LIFE					uint_16(90)
#define CREATURE_REPRODUCTION_COUNT uint_16(8)
#define PROGRAM_SIZE				uint_16(64)

class Creature
{
public:

	//Creature(); // TODO: убрать пустой конструктор
	Creature();
	~Creature();

	Action* getAction();
	void processResponses(Response* aResponse);
	void step();
	void reset();

	sint_16 getLife() const;

	void mutate(uint_8 aMutCount);

private:

	uint_16 mPrCount;
	//uint_16 mPrCount, mDPrCount = 1;
	std::vector<uint_16> mProgram;
	// 0 - 63				:goto step x in program
	// 64					:move forward
	// 65					:look in front of itself
	// 66					:eat/make food (take)
	// 67 - 74				:turn round at derection x - 70
	// * E C F P W -

	sint_16 mLife;
	Direction mDirection;	//TODO: direction enum

	struct PairCmp 
	{
		bool operator()(const std::pair<uint_16, uint_16>& p1, const std::pair<uint_16, uint_16>& p2) const;
	};
	std::map<std::pair<uint_16, uint_16>, ActionType, PairCmp> programDecoder;

	void incPrCount(uint_16 aDPrCount = 1);
	void lifeChange(sint_16 aDLife);
};

#endif // CREATURE_H

/*
70 71 72
77    73
76 75 74

0 1 2
7   3
6 5 4
*/