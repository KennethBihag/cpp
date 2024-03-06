#ifndef LEETCODE_HPP
#define LEETCODE_HPP

#include <vector>
#include <map>
#include <string>

class Solution
{
    const char _vInputs[7] = "{[(}])";
    double _GetMedian(std::vector<int> &sortedArr);

protected:
    bool _IsValid(const char *s);

public:
    int Rob(std::vector<int> &money);
    std::vector<int> TwoSum(std::vector<int> &nums, int target);
    bool IsPalindrome(int x);
    bool HasValidParentheses(const char *s, int len);
    int BiggestWidth(std::vector<std::pair<int, int>> pts);
    double FindMedianSortedArrays(std::vector<int> &nums1, std::vector<int> &nums2);
    int sumSubarrayMins(std::vector<int> &arr);
    std::vector<int> FindAllPeople(
        int n, std::vector<std::vector<int>> &meetings, int firstPerson);
    int minimumLength(std::string& s);

    friend void *EnclosedParenthesesTest(void*);
};

#endif