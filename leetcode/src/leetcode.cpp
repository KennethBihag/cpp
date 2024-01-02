#include "leetcode.hpp"

#include <malloc.h>
#include <stdio.h>
#include <string.h>

#include <algorithm>

#include "common/include/sort.h"

#include "stack.hpp"

using std::vector;
using std::pair;
using std::sort;

vector<int> Solution::TwoSum(vector<int> &nums, int target)
{
	int lastI = nums.size();
	for (int i = 0; i < lastI - 1; i++)
	{
		for (int j = i + 1; j < lastI; j++)
		{
			if (nums[i] + nums[j] == target)
				return {i, j};
		}
	}
	return vector<int>();
}

bool Solution::IsPalindrome(int x)
{
	if (x < 0)
		return false;
	if (x < 10)
		return true;
	int digits[16];
	int cnt = 0;
	while (x)
	{
		++cnt;
		digits[cnt-1] = x % 10;
		x /= 10;
	}
	if (cnt % 2)
	{ // odd number
		int mid = cnt / 2;
		for (int i = mid - 1, j = mid + 1; i > -1; i--, j++)
		{
			if (digits[i] != digits[j])
				return false;
		}
	}
	else
	{
		int mid = cnt / 2;
		for (int i = mid - 1, j = mid; i > -1; i--, j++)
		{
			if (digits[i] != digits[j])
				return false;
		}
	}
	return true;
}

bool Solution::HasValidParentheses(char *s, int len)
{
	bool yes;
	Stack braceStk;
	for (int i = 0; i < len; i++)
	{
		yes = false;
		for (int j = 0; j < 6; j++)
		{
			if (_vInputs[j] == s[i])
			{
				yes = true;
				if (j < 3)
					braceStk.Push(s[i]);
				else{
					char c = braceStk.Pop();
					int cd = _vInputs+j - strchr(_vInputs, c);
					if(cd != 3)
						return yes=false;
				}
				break;
			}
		}
		if (!yes)
			break;
	}
	if(!braceStk.IsEmpty())
		yes = false;
	return yes;
}

bool Solution::_IsValid(char *s)
{
	int sLen = strlen(s);
	return HasValidParentheses(s, sLen);
}

int Solution::BiggestWidth(std::vector<std::pair<int, int>> pts)
{
	int x[pts.size()];

	for(int i=0; i<pts.size(); i++)
		x[i] = pts[i].first;
	int *y = bubblesort_int(x, pts.size());
/* 	auto ComparePointX = [](pair<int,int>& a, pair<int,int>& b){
		return a.first < b.first;
	};
	sort(pts.begin(), pts.end(), ComparePointX); */
	
	int answer = -1;
	for(int i=0; i<pts.size()-1; i++)
		answer = std::max(answer,y[i+1]-y[i]);
		// answer = std::max(answer,pts[i+1].first - pts[i].first);
	free(y);

	return answer;
}

#define AVE(a,b) (a+b)/2
/* double Solution::FindMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
	if(nums1.empty())
		return _GetMedian(nums2);
	if(nums2.empty())
		return _GetMedian(nums1);
	double mdn1 = _GetMedian(nums1);
	double mdn2 = _GetMedian(nums2);
	return AVE(mdn1,mdn2);
} */

double Solution::FindMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
	std::vector<int> combined;
	for(int i : nums1)
		combined.push_back(i);
	for(int i : nums2)
		combined.push_back(i);
	sort(combined.begin(),combined.end());
	return _GetMedian(combined);
}

double Solution::_GetMedian(vector<int>& sortedArr){
    int len = (int)sortedArr.size();
    int i=len/2;
    if(len%2)
        return sortedArr[i];
    else {
        return (double)AVE(sortedArr[i-1],sortedArr[i]);
    }
}
#undef AVE
