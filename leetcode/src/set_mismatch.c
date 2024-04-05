#include "leetcode.h"

#include <malloc.h>

int* findErrorNums(int* nums, int numsSize, int* returnSize)
{
    int* result = (int*)malloc(2 * sizeof(int));
    *returnSize = 2;
    int rightSum = (double)numsSize / 2 * (1 + numsSize);
    int sumDiff = 0, dup = -1;
    for (int i = 0; i < numsSize; ++i)
    {
        sumDiff += nums[i];
        if (dup == -1)
        {
            for (int j = i + 1; j < numsSize; ++j)
                if (nums[i] == nums[j])
                {
                    result[0] = nums[i];
                    dup = j;
                    break;
                }
        }
    }
    sumDiff = sumDiff-rightSum;
    result[1] = result[0] - sumDiff;

    return result;
}