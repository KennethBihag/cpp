#include <stdio.h>

#include "threading/include/threading.h"
#include "test.hpp"

int main()
{
	thrd_func tests[] = {
	SetMismatchTest
#ifdef ALL_CHALLENGES
	,HouseRobberTest
	,IsPalindromeTest
	,TwoSumTest
	,EnclosedParenthesesTest
	,BiggestWidthTest
	,MedianTest
	,SumSubarrayMinsTest
#endif
	};
	int fcount = sizeof(tests)/sizeof(thrd_func);
	void *args[fcount];
	parallel_run(tests,args,fcount);
	return 0;
}