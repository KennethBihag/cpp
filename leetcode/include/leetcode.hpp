#ifndef LEETCODE_HPP
#define LEETCODE_HPP

#include <vector>

class Solution {
    const char _vInputs[7] = "{[(}])";
protected:
    bool _IsValid(char *s);
public:
    std::vector<int> TwoSum(std::vector<int>& nums, int target);
    bool IsPalindrome(int x);
    bool HasValidParentheses(char *s, int len);

    friend void EnclosedParenthesesTest();
};

#endif