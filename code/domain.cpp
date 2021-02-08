#include "domain.h"

uint_16 rnd1(uint_16 mod)
{
	return rand() % mod;
}

uint_64 rnd2(uint_64 mod)
{
	uint_64 num;
	num = uint_64(rand())*uint_64(rand())*uint_64(rand());
	return num % mod;
}

uint_64 rnd(uint_64 aFrom, uint_64 aTo)
{
	uint_64 num =rand();
	uint_64 mod = aTo + 1 - aFrom;
	return num % mod + aFrom;
}

sint_8 dX[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
sint_8 dY[] = { 0, 1, 1, 1, 0, -1, -1, -1 };

Point::Point()
{}

Point::Point(sint_8 aX, sint_8 aY) :
	mX(aX),
	mY(aY)
{}

Point 
Point::operator+ (Direction &aDirection)
{
	return Point(mX + dX[uint_8(aDirection)], mY + dY[uint_8(aDirection)]);
}