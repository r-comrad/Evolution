#ifndef DIRECTION_H
#define DIRECTION_H

#include "domain.h"

class Direction
{
public:
	//Direction();
	Direction(uint_16 aValue); 

	const Direction& operator++();
	const Direction operator++(int);

	const Direction& operator--();
	const Direction operator--(int);

	int getX() const;
	int getY() const;

private:
	enum DirectionValues
	{ 
		Up, UpRight, Right, DownRight, 
		Down, DownLeft, Left, UpLeft 
	};

	DirectionValues mDir;
};

#endif //DIRECTION_H