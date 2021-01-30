#ifndef CREATURES_LIFE_LIST_H
#define CREATURES_LIFE_LIST_H

#include <list>
#include <queue>

#include "domain.h"

//CHARACTERISTIC_H
//class Characteristic
class CreaturesLifeList
{
public:
	CreaturesLifeList(std::list<Point> aCreaturesCoordinates, 
		std::list<sint_16> aCreaturesLifes);

	std::pair<Point, sint_16> getNextValue();

	uint_16 size();

private:
	std::list<std::pair<Point, sint_16>> ::iterator mIt;
	// -TODO: pair -> uint_16 (first element kept in Field)
	std::list<std::pair<Point, sint_16>> mList;
};

#endif // CREATURES_LIFE_LIST_H