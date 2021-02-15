#include "Direction.h"

Direction::Direction(uint_16 aValue)
{
	mDir = Direction::DirectionValues(aValue);
}


const Direction&
Direction::operator++()
{
	switch (mDir)
	{
	case Direction::DirectionValues::Up:	
		mDir = Direction::DirectionValues::UpRight;
		break;
	case Direction::DirectionValues::UpRight :
		mDir = Direction::DirectionValues::Right;
		break;
	case Direction::DirectionValues::Right :	
		mDir = Direction::DirectionValues::DownRight;
		break;
	case Direction::DirectionValues::DownRight :	
		mDir = Direction::DirectionValues::Down;
		break;
	case Direction::DirectionValues::Down :	
		mDir = Direction::DirectionValues::DownLeft;
		break;
	case Direction::DirectionValues::DownLeft :	
		mDir = Direction::DirectionValues::Left;
		break;
	case Direction::DirectionValues::Left :	
		mDir = Direction::DirectionValues::UpLeft;
		break;
	case Direction::DirectionValues::UpLeft :	
		mDir = Direction::DirectionValues::Up;
		break;
	}
	return *this;
}

const Direction
Direction::operator++(int)
{
	Direction result = *this;

	switch (mDir)
	{
	case Direction::DirectionValues::Up :
		mDir = Direction::DirectionValues::UpRight;
		break;
	case Direction::DirectionValues::UpRight :
		mDir = Direction::DirectionValues::Right;
		break;
	case Direction::DirectionValues::Right :
		mDir = Direction::DirectionValues::DownRight;
		break;
	case Direction::DirectionValues::DownRight :
		mDir = Direction::DirectionValues::Down;
		break;
	case Direction::DirectionValues::Down :
		mDir = Direction::DirectionValues::DownLeft;
		break;
	case Direction::DirectionValues::DownLeft :
		mDir = Direction::DirectionValues::Left;
		break;
	case Direction::DirectionValues::Left :
		mDir = Direction::DirectionValues::UpLeft;
		break;
	case Direction::DirectionValues::UpLeft :
		mDir = Direction::DirectionValues::Up;
		break;
	}

	return result;
}

const Direction&
Direction::operator--()
{
	switch (mDir)
	{
	case Direction::DirectionValues::Up :
		mDir = Direction::DirectionValues::UpLeft;
		break;
	case Direction::DirectionValues::UpRight :
		mDir = Direction::DirectionValues::Up;
		break;
	case Direction::DirectionValues::Right :
		mDir = Direction::DirectionValues::UpRight;
		break;
	case Direction::DirectionValues::DownRight :
		mDir = Direction::DirectionValues::Right;
		break;
	case Direction::DirectionValues::Down :
		mDir = Direction::DirectionValues::DownRight;
		break;
	case Direction::DirectionValues::DownLeft :
		mDir = Direction::DirectionValues::Down;
		break;
	case Direction::DirectionValues::Left :
		mDir = Direction::DirectionValues::DownLeft;
			break;
	case Direction::DirectionValues::UpLeft :
		mDir = Direction::DirectionValues::Left;
		break;
	}

	return *this;
}

const Direction
Direction::operator--(int)
{
	Direction result = *this;

	switch (mDir)
	{
	case Direction::DirectionValues::Up :
		mDir = Direction::DirectionValues::UpLeft;
		break;
	case Direction::DirectionValues::UpRight :
		mDir = Direction::DirectionValues::Up;
		break;
	case Direction::DirectionValues::Right :
		mDir = Direction::DirectionValues::UpRight;
		break;
	case Direction::DirectionValues::DownRight :
		mDir = Direction::DirectionValues::Right;
		break;
	case Direction::DirectionValues::Down :
		mDir = Direction::DirectionValues::DownRight;
		break;
	case Direction::DirectionValues::DownLeft :
		mDir = Direction::DirectionValues::Down;
		break;
	case Direction::DirectionValues::Left :
		mDir = Direction::DirectionValues::DownLeft;
		break;
	case Direction::DirectionValues::UpLeft :
		mDir = Direction::DirectionValues::Left;
		break;
	}

	return result;
}

int 
Direction::getX() const
{
	switch (mDir)
	{
	case Direction::DirectionValues::Up:
		return 0;
	case Direction::DirectionValues::UpRight:
		return 1;
	case Direction::DirectionValues::Right:
		return 1;
	case Direction::DirectionValues::DownRight:
		return 1;
	case Direction::DirectionValues::Down:
		return -0;
	case Direction::DirectionValues::DownLeft:
		return -1;
	case Direction::DirectionValues::Left:
		return -1;
	case Direction::DirectionValues::UpLeft:
		return -1;
	}
}

int 
Direction::getY() const
{
	switch (mDir)
	{
	case Direction::DirectionValues::Up:
		return 1;
	case Direction::DirectionValues::UpRight:
		return 1;
	case Direction::DirectionValues::Right:
		return 0;
	case Direction::DirectionValues::DownRight:
		return -1;
	case Direction::DirectionValues::Down:
		return -1;
	case Direction::DirectionValues::DownLeft:
		return -1;
	case Direction::DirectionValues::Left:
		return 0;
	case Direction::DirectionValues::UpLeft:
		return 1;
	}
}