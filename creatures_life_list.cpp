#include "creatures_life_list.h"

//--------------------------------------------------------------------------------
// Creatures Life List implementation
//--------------------------------------------------------------------------------

CreaturesLifeList::CreaturesLifeList(std::list<Point> aCreaturesCoordinates,
	std::list<sint_16> aCreaturesLifes)
{
	std::list<Point> ::iterator it1 = aCreaturesCoordinates.begin();
	std::list<sint_16> ::iterator it2 = aCreaturesLifes.begin();
	for(int i = 0; i < aCreaturesCoordinates.size(); ++i)
	{
		mList.emplace_back(*it1, *it2);

		it1++;
		//if (it1 == aCreaturesCoordinates.end()) 
		//	it1 = aCreaturesCoordinates.begin();
		it2++;
		//if (it2 == aCreaturesLifes.end())
		//	it2 = aCreaturesLifes.begin();
	}

	mIt = mList.begin();
}
//--------------------------------------------------------------------------------
uint_16 
CreaturesLifeList::size()
{
	return mList.size();
}
//--------------------------------------------------------------------------------
std::pair<Point, sint_16>
CreaturesLifeList::getNextValue()
{
	if (mIt == mList.end()) mIt = mList.begin();
	return *(mIt++);
}
//--------------------------------------------------------------------------------