#include "test.hpp"

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <vector>

#include "leetcode.hpp"

Solution solution;

void EnclosedParenthesesTest()
{
	char *testString = "{[()]}";
	bool success = solution._IsValid(testString);
	assert(success);

	testString = "([]){}";
	success = solution._IsValid(testString);
	assert(success);

	testString = "abcde";
	success = solution._IsValid(testString);
	assert(!success);

	testString = "([{abe";
	success = solution._IsValid(testString);
	assert(!success);

	testString = "([}])";
	success = solution._IsValid(testString);
	assert(!success);

	testString = ")[][]";
	success = solution._IsValid(testString);
	assert(!success);

	testString = "{[(";
	success = solution._IsValid(testString);
	assert(!success);

	printf("-- ENCLOSED PARENTHESES TESTS PASSED --\n");
}

void IsPalindromeTest(){
	int a = 0, b = -23, c = 123, d = 1221, e = 12321;
	assert(solution.IsPalindrome(a));
	assert(!solution.IsPalindrome(b));
	assert(!solution.IsPalindrome(c));
	assert(solution.IsPalindrome(d));
	assert(solution.IsPalindrome(e));
	printf("-- PALIDROME TESTS PASSED --\n");
}

void TwoSumTest(){
	std::vector<int> nums = {0, 1, 2, 3, 4, 5, 6, 7, 8};
	int target = 9;
	std::vector<int> ans = solution.TwoSum(nums, target);
	assert(ans[0] == 1 && ans[1] == 8);
	printf("-- TWOSUM TEST PASSED --\n");
}