#include <stdio.h>

#include "test.hpp"

int main(){
	HouseRobberTest();
#ifdef ALL_CHALLENGES
	IsPalindromeTest();
	TwoSumTest();
	EnclosedParenthesesTest();
	BiggestWidthTest();
	MedianTest();
	SumSubarrayMinsTest();
#endif
	return 0;
}