#include "leetcode.hpp"

#include <malloc.h>
#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>

#include "common/include/sort.h"

#include "stack.hpp"

using std::cout;
using std::pair;
using std::sort;
using std::string;
using std::vector;

#ifndef CODEIUM_GEN
static int largestSum;
static void sums(std::vector<int>::iterator,
				 std::vector<int>::iterator, const int &);
#endif
int Solution::Rob(std::vector<int> &money)
{
#ifndef CODEIUM_GEN
	int gaps = 2;
	for (int i = 0; i < money.size() - gaps + 1; ++i)
	{
		auto starting = money.begin() + i;
		::sums(starting, money.end(), 0);
	}
	return largestSum;
#else
	int n = money.size();
	if (n == 0)
	{
		return 0;
	}
	if (n == 1)
	{
		return money[0];
	}
	vector<int> dp(n);
	dp[0] = money[0];
	dp[1] = std::max(money[0], money[1]);
	for (int i = 2; i < n; ++i)
	{
		dp[i] = std::max(dp[i - 1], dp[i - 2] + money[i]);
	}
	return dp[n - 1];
#endif
}

#ifndef CODEIUM_GEN
void sums(std::vector<int>::iterator start,
		  std::vector<int>::iterator end, const int &sum)
{
	auto itr = start + 2;
	if (itr >= end)
	{
		largestSum = std::max(largestSum, *start + sum);
		return;
	}
	while (itr < end)
	{
		::sums(itr, end, sum + *start);
		++itr;
	}
}
#endif

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
		digits[cnt - 1] = x % 10;
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

bool Solution::HasValidParentheses(const char *s, int len)
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
				else
				{
					char c = braceStk.Pop();
					int cd = _vInputs + j - strchr(_vInputs, c);
					if (cd != 3)
						return yes = false;
				}
				break;
			}
		}
		if (!yes)
			break;
	}
	if (!braceStk.IsEmpty())
		yes = false;
	return yes;
}

bool Solution::_IsValid(const char *s)
{
	int sLen = strlen(s);
	return HasValidParentheses(s, sLen);
}

int Solution::BiggestWidth(std::vector<std::pair<int, int>> pts)
{
	int x[pts.size()];

	for (int i = 0; i < pts.size(); i++)
		x[i] = pts[i].first;
	int *y = bubblesort_int(x, pts.size());
	/* 	auto ComparePointX = [](pair<int,int>& a, pair<int,int>& b){
			return a.first < b.first;
		};
		sort(pts.begin(), pts.end(), ComparePointX); */

	int answer = -1;
	for (int i = 0; i < pts.size() - 1; i++)
		answer = std::max(answer, y[i + 1] - y[i]);
	// answer = std::max(answer,pts[i+1].first - pts[i].first);
	free(y);

	return answer;
}

#define AVE(a, b) (a + b) / 2
double Solution::FindMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
{
	std::vector<int> combined;
	for (int i : nums1)
		combined.push_back(i);
	for (int i : nums2)
		combined.push_back(i);
	sort(combined.begin(), combined.end());
	return _GetMedian(combined);
}

double Solution::_GetMedian(vector<int> &sortedArr)
{
	int len = (int)sortedArr.size();
	int i = len / 2;
	if (len % 2)
		return sortedArr[i];
	else
	{
		return (double)AVE(sortedArr[i - 1], sortedArr[i]);
	}
}
#undef AVE

int Solution::sumSubarrayMins(vector<int> &arr)
{
	int sum{};
	int len = arr.size();
	for (int sz = 1, c = len; sz <= len; ++sz, --c)
	{
		for (int k = 0; k < c; k++)
		{
			if (sz == 1)
			{
				sum += arr[k];
				continue;
			}
			else
			{
				auto first = arr.begin() + k;
				auto last = first + sz;
				auto res = min_element(first, last);
				sum += *res;
			}
		}
	}
	return sum;
}

// Find all people
static bool meetingComp(const vector<int> &a, const vector<int> &b)
{
	return a[2] < b[2];
}

/* void printMeetings(const vector<vector<int>> &meetings)
{
	for (auto i : meetings)
	{
		cout << '\t';
		cout << i[0] << " meets with " << i[1] << " on " << i[2] << '\n';
	}
} */

/* static void printWhoKnows(const vector<int> &knowers)
{
	cout << "Those who know:";
	for (auto i : knowers)
		cout << ' ' << i;
	cout << '\n';
} */

static bool exists(const vector<int> &vec, const int val)
{
	vector<int>::const_iterator ptr =
		std::find(vec.begin(), vec.end(), val);
	return ptr != vec.end();
}

static bool exists(const vector<int> &vec, const vector<int> &val, int *firstMatch)
{
	for (auto i : val)
	{
		if (exists(vec, i))
		{
			*firstMatch = i;
			return true;
		}
	}
	return false;
}

static void spread(vector<vector<int>> &meetings, vector<int> &knowers)
{
REPEAT:
	bool done = true;
	vector<vector<int>> tmpMeetings(meetings);
	for (auto &i : tmpMeetings)
	{
		std::vector<int> pair(i.begin(), i.end() - 1);
		int intrsctn = INT32_MAX;
		if (exists(pair, knowers, &intrsctn))
		{
			if (pair[0] != intrsctn)
			{
				if (!exists(knowers, pair[0]))
					knowers.push_back(pair[0]);
			}
			else
			{
				if (!exists(knowers, pair[1]))
					knowers.push_back(pair[1]);
			}
			done = false;
			auto newEnd = std::remove(meetings.begin(), meetings.end(), i);
			meetings.erase(newEnd);
		}
	}
	if (!done)
		goto REPEAT;
	return;
}

vector<int> Solution::FindAllPeople(int n, vector<vector<int>> &meetings, int firstPerson)
{
	vector<int> knowers{0, firstPerson};
	sort(meetings.begin(), meetings.end(), meetingComp);
	vector<vector<int>> meetingsSameTime;
	for (auto i : meetings)
	{
		static int t = i[2];
	UPDATE_MEETINGS_SAME_T:
		if (t == i[2])
		{
			meetingsSameTime.push_back(i);
		}
		else
		{
			spread(meetingsSameTime, knowers);
			meetingsSameTime.clear();
			t = i[2];
			goto UPDATE_MEETINGS_SAME_T;
		}
	}
	spread(meetingsSameTime, knowers);
	// printWhoKnows(knowers);
	return knowers;
}

// Minimum Length of string after removing like prefix and suffix
int minLenHelper(const char *s, const int slen)
{
#ifdef VERSION2
	if (slen <= 1)
		return slen;

	const char &frch = s[0];
	const char &lach = s[slen - 1];

	if (frch == lach)
	{
		if (slen == 2)
			return 0;
		auto pfi = s;
		auto sfi = s + slen - 1;

		if (pfi == sfi)
			return 1;

		for (; pfi < sfi; pfi++)
		{
			if (frch != *pfi)
				break;
		}

		for (; sfi > s; sfi--)
		{
			if (lach != *sfi)
				break;
		}
		if (sfi >= pfi)
		{
			((char *)sfi)[1] = 0;
			const char *sf = pfi;
			int tmpresult = minLenHelper(sf, sfi - pfi + 1);
			return tmpresult;
		}
		else
			return 0;
	}

	return slen;
#else
	const char *const start = s;
	const char *const end = s + slen - 1;
	const char *pf = start;
	const char *sf = end;
	char compare;
	int result;
STEP_1:
	result = sf - pf + 1;
	if (*pf != *sf || result == 1)
		return result;

	compare = *pf;
	for (; pf <= end; pf++)
	{
		if (*pf != compare)
			break;
	}
	if (pf == sf)
		return 0;
	for (; sf >= pf; sf--)
	{
		if (*sf != compare)
			break;
	}
	if (sf < pf)
		return 0;
	else
		goto STEP_1;

#endif
}

int Solution::minimumLength(string &s)
{
	return minLenHelper(s.c_str(), s.length());
}

// Reveal cards in increasing order
static std::vector<int> deckHelper(std::vector<int> &deck){
    switch(deck.size()){
        case 1:
        case 2:
            return deck;
    }
    int mid = deck.size()/2;
    if(deck.size()%2)
        mid++;

    std::vector<int> low(deck.begin(), deck.begin()+mid);
    std::vector<int> high(deck.begin()+mid,deck.end());
    deckHelper(high);
    if(deck.size()%2){
        high.emplace(high.begin(),high[high.size()-1]);
        high.erase(high.end()-1);
    }
    
    for(int i=0; i<high.size(); i++){
        deck[i*2] = low[i];
        deck[i*2+1] = high[i];
    }

    if(low.size() > high.size())
        deck[deck.size()-1] = low[low.size()-1];
    return deck;
}
std::vector<int> Solution::deckRevealedIncreasing(std::vector<int>& deck){
    std::sort(deck.begin(), deck.end());
    return deckHelper(deck);
}