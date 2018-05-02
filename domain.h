#ifndef DOMAIN_H
#define DOMAIN_H

#include <queue>
#include <list>
#include <vector>
#include <ostream>
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <cstdlib>
#include <fstream>

#include <SFML/Graphics.hpp>
//#include <Time.hpp>

typedef signed		__int8		sint_8;
typedef unsigned	__int8		uint_8;

typedef signed		__int16		sint_16;
typedef unsigned	__int16		uint_16;

typedef unsigned	__int32		uint_32;

typedef unsigned	__int64		uint_64;

uint_16 rnd1(uint_16 mod = 32767);
uint_64 rnd2(uint_64 mod);

enum struct Direction { UP, UP_RIGHT, RIGHT, RIGHT_DOWN, DOWN, DOWN_LEFT, LEFT, LEFT_UP};

const Direction& operator++(Direction& aDir);
const Direction operator++(Direction& aDir, int);

const Direction& operator--(Direction& aDir);
const Direction operator--(Direction& aDir, int);

struct Point
{
	sint_8 mX, mY;

	Point();
	Point(sint_8 aX, sint_8 aY);

	Point operator+ (Direction &aDirection);
};

#endif // DOMAIN_H