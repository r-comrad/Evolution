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

const Direction& 
operator++(Direction& aDir)
{
	switch (aDir)
	{
	case Direction::UP:			return aDir = Direction::UP_RIGHT;
	case Direction::UP_RIGHT:	return aDir = Direction::RIGHT;
	case Direction::RIGHT:		return aDir = Direction::RIGHT_DOWN;
	case Direction::RIGHT_DOWN: return aDir = Direction::DOWN;
	case Direction::DOWN:		return aDir = Direction::DOWN_LEFT;
	case Direction::DOWN_LEFT:	return aDir = Direction::LEFT;
	case Direction::LEFT:		return aDir = Direction::LEFT_UP;
	case Direction::LEFT_UP:	return aDir = Direction::UP;
	}
}
const Direction
operator++(Direction& aDir, int)
{
	switch (aDir)
	{
	case Direction::UP:			return aDir = Direction::UP_RIGHT;
	case Direction::UP_RIGHT:	return aDir = Direction::RIGHT;
	case Direction::RIGHT:		return aDir = Direction::RIGHT_DOWN;
	case Direction::RIGHT_DOWN: return aDir = Direction::DOWN;
	case Direction::DOWN:		return aDir = Direction::DOWN_LEFT;
	case Direction::DOWN_LEFT:	return aDir = Direction::LEFT;
	case Direction::LEFT:		return aDir = Direction::LEFT_UP;
	case Direction::LEFT_UP:	return aDir = Direction::UP;
	}
}

const Direction&
operator--(Direction& aDir)
{
	switch (aDir)
	{
	case Direction::UP:			return aDir = Direction::LEFT_UP;
	case Direction::UP_RIGHT:	return aDir = Direction::UP;
	case Direction::RIGHT:		return aDir = Direction::UP_RIGHT;
	case Direction::RIGHT_DOWN: return aDir = Direction::RIGHT;
	case Direction::DOWN:		return aDir = Direction::RIGHT_DOWN;
	case Direction::DOWN_LEFT:	return aDir = Direction::DOWN;
	case Direction::LEFT:		return aDir = Direction::DOWN_LEFT;
	case Direction::LEFT_UP:	return aDir = Direction::LEFT;
	}
}
const Direction
operator--(Direction& aDir, int)
{
	switch (aDir)
	{
	case Direction::UP:			return aDir = Direction::LEFT_UP;
	case Direction::UP_RIGHT:	return aDir = Direction::UP;
	case Direction::RIGHT:		return aDir = Direction::UP_RIGHT;
	case Direction::RIGHT_DOWN: return aDir = Direction::RIGHT;
	case Direction::DOWN:		return aDir = Direction::RIGHT_DOWN;
	case Direction::DOWN_LEFT:	return aDir = Direction::DOWN;
	case Direction::LEFT:		return aDir = Direction::DOWN_LEFT;
	case Direction::LEFT_UP:	return aDir = Direction::LEFT;
	}
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