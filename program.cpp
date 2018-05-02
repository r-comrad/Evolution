#include "program.h"

//--------------------------------------------------------------------------------
// Program implementation
//--------------------------------------------------------------------------------

Program::Program(std::vector<uint_8>& aProbability)
{
	//int sum = aProbability[0];
	//for (uint_16 i = 1; i < aProbability.size(); ++i)
	//{
	//	sum += aProbability[i];
	//	aProbability[i] += aProbability[i - 1];;
	//}

	int sum = aProbability[0];
	for (uint_16 i = 1; i < aProbability.size(); ++i)
	{
		sum += aProbability[i] - aProbability[i - 1];;
	}

	for (uint_16 i = 0; i < mProgram.size(); ++i)
	{
		int cur = rnd1(sum);
		for (uint_16 j = 0; j < aProbability.size(); ++j)
		{
			if (cur < aProbability[j])
			{
				//mProgram[i] = ;
				break;
			}
		}
	}
}