#ifndef BUILD_LIB

#include <stdio.h>

#include "threading/include/threading.h"
#include "test.hpp"

int main()
{
	thrd_func tests[] = {
        ConstructDistancedSeqTest
#ifdef ALL_CHALLENGES
        ,
        MaximumSumTest,
        MaximalRectangleTest,
        DeckRevealedIncreasingTest,
        MinimumLengthTest,
		RemoveNodeFromEndTest,
		FindAllPeopleTest,
		SetMismatchTest,
		HouseRobberTest,
		IsPalindromeTest,
		TwoSumTest,
		EnclosedParenthesesTest,
		BiggestWidthTest,
		MedianTest,
		SumSubarrayMinsTest
#endif
	};
	unsigned char fcount = (unsigned char)(sizeof(tests) / sizeof(thrd_func));
	for (int i = 0; i < fcount; i++)
	{
		mythreads[i] = new MyThread;
		mythreads[i]->func = tests[i];
	}
	parallel_run(mythreads, fcount);
	return 0;
}

#endif