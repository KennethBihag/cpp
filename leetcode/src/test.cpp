#include "test.hpp"

#include <assert.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <vector>

#include "leetcode.h"
#include "leetcode.hpp"

#define RETURN_CODE \
	void *res = malloc(sizeof(signed char)); \
	*(signed char *)res = 0; \
	return res;

Solution solution;

const char bar[] = "-----------------------------\n";

void *HouseRobberTest(void *args)
{
	printf(bar);
	std::vector<int> sample1{1, 2, 3, 1},
		sample2{2, 7, 9, 3, 1}, sample3{4, 1, 2, 7, 5, 3, 1};
	/* 	std::vector<int> sample4{114,117,207,117,235,82,90,67,143,
			146,53,108,200,91,80,223,58,170,110,236,81,90,222,160,
			165,195,187,199,114,235,197,187,69,129,64,214,228,78,
			188,67,205,94,205,169,241,202,144,240}; */
	int exp1{4}, exp2{12}, exp3{14};
	// int exp4{4173};
	int ans1 = solution.Rob(sample1);
	int ans2 = solution.Rob(sample2);
	int ans3 = solution.Rob(sample3);
	// int ans4 = solution.Rob(sample4);

	assert(exp1 == ans1);
	assert(exp2 == ans2);
	assert(exp3 == ans3);
	// assert(exp4 == ans4);
	printf("-- HOUSE ROBBER TESTS PASSED --\n");
	RETURN_CODE
}

void *EnclosedParenthesesTest(void *args)
{
	printf(bar);
	const char *testString = "{[()]}";
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
	RETURN_CODE
}

void *IsPalindromeTest(void *args)
{
	printf(bar);
	int a = 0, b = -23, c = 123, d = 1221, e = 12321;
	assert(solution.IsPalindrome(a));
	assert(!solution.IsPalindrome(b));
	assert(!solution.IsPalindrome(c));
	assert(solution.IsPalindrome(d));
	assert(solution.IsPalindrome(e));
	printf("-- PALINDROME TESTS PASSED --\n");
	RETURN_CODE
}

void *TwoSumTest(void *args)
{
	printf(bar);
	std::vector<int> nums = {0, 1, 2, 3, 4, 5, 6, 7, 8};
	int target = 9;
	std::vector<int> ans = solution.TwoSum(nums, target);
	assert(ans[0] == 1 && ans[1] == 8);
	printf("-- TWOSUM TEST PASSED --\n");
	RETURN_CODE
}

void *BiggestWidthTest(void *args)
{
	printf(bar);
	std::vector<std::pair<int, int>> points;
	std::vector nums = {3, 1, 9, 0, 1, 0, 1, 4, 5, 3, 8, 8};
	printf("POINTS: \n");
	for (int i = 0; i < nums.size(); i += 2)
	{
		points.push_back(std::make_pair(
			nums[i], nums[i + 1]));
		printf("\t(%d,%d)\n", points.back().first, points.back().second);
	}
	time_t start, end;
	time(&start);
	int width = solution.BiggestWidth(points);
	time(&end);
	printf("Biggest width is: %d\n", width);
	assert(width == 3);
	printf("-- BIGGEST WIDTH TEST PASSED --\n");
	printf("In %f\n", difftime(start, end));
	RETURN_CODE
}

void *MedianTest(void *args)
{
	printf(bar);
	std::vector<int> nums1 = {1, 3};
	std::vector<int> nums2 = {2};
	double r = solution.FindMedianSortedArrays(nums1, nums2);
	double d = r - 2;
	assert(d < 0.25 && d > -0.25);
	printf("Median is %lf\n", r);

	nums1 = {1, 2};
	nums2 = {3, 4};
	r = solution.FindMedianSortedArrays(nums1, nums2);
	d = r - 2.5;
	assert(d < 0.25 && d > -0.25);
	printf("Median is %lf\n", r);

	nums1 = {1, 3};
	nums2 = {2, 7};
	r = solution.FindMedianSortedArrays(nums1, nums2);
	d = r - 2.5;
	assert(d < 0.25 && d > -0.25);
	printf("Median is %lf\n", r);

	printf("MEDIAN TEST PASSED\n");
	RETURN_CODE
}

void *SumSubarrayMinsTest(void *args)
{
	printf(bar);
	std::vector<int> sample{3, 1, 2, 4};
	int ans1 = solution.sumSubarrayMins(sample);
	sample = {11, 81, 94, 43, 3};
	int ans2 = solution.sumSubarrayMins(sample);
	printf("First min: %d\n", ans1);
	printf("Second min: %d\n", ans2);
	assert(ans1 == 17);
	assert(ans2 == 444);
	printf("SUM SUBARRAY MINS TEST PASSED\n");
	RETURN_CODE
}

void *SetMismatchTest(void *args)
{
	printf(bar);
	int sample1[] = {3, 2, 2};
	int sample2[] = {1, 2, 2, 4};
	int exp1[] = {2, 1}, sz1;
	int exp2[] = {2, 3}, sz2;
	int *ans1 = findErrorNums(sample1, std::size(sample1), &sz1);
	int *ans2 = findErrorNums(sample2, std::size(sample2), &sz2);

	printf("Answer: {%d,%d}\n", ans1[0], ans1[1]);
	printf("Answer: {%d,%d}\n", ans2[0], ans2[1]);

	assert(ans1[0] == exp1[0] && ans1[1] == exp1[1]);
	assert(ans2[0] == exp2[0] && ans2[1] == exp2[1]);

	free(ans1);
	free(ans2);
	printf("-- SET MISMATCH TESTS PASSED --\n");
	RETURN_CODE
}

void *FindAllPeopleTest(void *args)
{
	printf(bar);
	std::vector<std::vector<int>> meetings{
		{1, 2, 5},
		{2, 3, 8},
		{1, 5, 10}};
	int p1 = 1;
	solution.FindAllPeople(6, meetings, p1);

	meetings = std::vector<std::vector<int>>{{0,2,1},{1,3,1},{4,5,1}};
	p1 = 1;
	solution.FindAllPeople(6, meetings,p1);

	meetings = std::vector<std::vector<int>>{{3, 1, 3}, {1, 2, 2}, {0, 3, 3}};
	p1 = 3;
	solution.FindAllPeople(4, meetings, p1);

	meetings = std::vector<std::vector<int>>{{3, 4, 2}, {1, 2, 1}, {2, 3, 1}};
	p1 = 1;
	solution.FindAllPeople(5, meetings, p1);

	meetings = std::vector<std::vector<int>>{{1, 4, 3}, {0, 4, 3}};
	p1 = 3;
	solution.FindAllPeople(5, meetings, p1);

	printf("--- FIND ALL PEOPLE TESTS PASSED ---\n");

	RETURN_CODE
}