#include "leetcode.hpp"
#include <thread>
#include <iostream>

using namespace std;

inline int sumDigits(int num){
    // clog << "sumDigits: " << "num=" << num << '\n';
    int sum = 0;

    while(num){
        int rem = num % 10;
        num /= 10;
        sum += rem;
    }
    // clog << "sum=" << sum << "\n\n";
    return sum;
}

int Solution::maximumSum(vector<int>& nums){
    int result = -1;
    int i=0, j;

    for(; i < nums.size()-1; i++){
        j = i+1;
        for(; j < nums.size(); j++){
            int temp = sumDigits(nums[i]);
            if(temp == sumDigits(nums[j]))
                result = std::max(result, nums[i]+nums[j]);
        }
    }

    return result;
}