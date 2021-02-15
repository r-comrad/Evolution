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
#include "direction.h"

//#define MAX_PROGRAM_WORD_VALUE		uint_16(319)
#define MAX_LIFE						uint_16(90)
//#define CREATURE_REPRODUCTION_COUNT	uint_16(8)
#define PROGRAM_SIZE					uint_16(65)
#define MAX_NINIACTIONS_COUNT			uint_16(5)

class Creature : public Object
{
public:
	Creature();
	~Creature();

	virtual Object::Action* getAction();
	virtual std::vector<Object*> multiply(int aChildCount) const;
	virtual bool update(std::vector<int> aResponce);
	sint_16 getLife() const;

private:
	uint_16 mComandPointer;
	std::vector<uint_16> mProgram;
	int mActionCount;
	// LOOK:	1, 5 ints for actions
	// TURN:	2, int for dirrection
	// EAT:		3
	// ACTION:	4
	// MOVE:	5
	// GOTO		6,  1 int for offset [1,9]

	sint_16 mLife;
	Direction mDirection;

	void reset();
	void incComandPointer(uint_16 aValue = 1);
	void lifeChange(sint_16 aDLife);
	void mutate(uint_8 aMutCount);

private:
	enum CreatureComands {
		LOOK = 1, TURN = 2, EAT = 3,
		ACTION = 4, MOVE = 5, GOTO = 6
	};
	enum ComandsSize {
		LOOK = 5, TURN = 1, EAT = 0,
		ACTION = 0, MOVE = 0, GOTO = 1
	};
};

#define MAX_PROGRAM_WORD_VALUE

#endif // CREATURE_H
