#include <stdio.h>

#include "test.hpp"

int main()
{
	SetMismatchTest();
#ifdef ALL_CHALLENGES
	HouseRobberTest();
	IsPalindromeTest();
	TwoSumTest();
	EnclosedParenthesesTest();
	BiggestWidthTest();
	MedianTest();
	SumSubarrayMinsTest();
#endif
	return 0;
}