#ifndef PROGRAM_H
#define PROGRAM_H

#include "domain.h"

// TURN / TURN_LEFT - TURN-RIGHT
enum CommandType { 
	ZERRO = 0,	GOTO = 50,	MOVE = 1, 
	LOOK = 2,	TAKE = 3,	TURN = 4, 
	DIE = 5 
};

class Program
{
public:
	Program(std::vector<uint_8>& aProbability);

private:
	//static std::map<
	std::vector<uint_16> mProgram;
};

#endif // PROGRAM_H