#ifndef CREATURE_H
#define CREATURE_H

#include <vector>
#include <map>
#include <set>
#include <list>

#include "domain.h"
#include "response.h"
#include "action.h"
#include "object.h"

//#define MAX_PROGRAM_WORD_VALUE		uint_16(319)
//#define MAX_LIFE					uint_16(90)
//#define CREATURE_REPRODUCTION_COUNT uint_16(8)
#define PROGRAM_SIZE				uint_16(65)

class Creature
{
public:

	Creature();
	~Creature();

	virtual Action* getAction() const;
	virtual std::vector<Object*> multiply(int aChildCount) const;
	virtual void update(std::vector<int>);
	sint_16 getLife() const;

private:

	uint_16 mPrCount;
	std::vector<uint_16> mProgram;
	// LOOK:	1, 5 ints for actions
	// TURN:	2, int for dirrection
	// EAT:		3
	// ACTION:	4
	// MOVE:	5
	// GOTO		6,  1 int for offset [1,9]

	sint_16 mLife;
	Direction mDirection;

	void  reset();
	void incPrCount(uint_16 aDPrCount = 1);
	void lifeChange(sint_16 aDLife);

};

#endif // CREATURE_H
