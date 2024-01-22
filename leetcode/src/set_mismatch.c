#include "leetcode.h"

#include <malloc.h>

int* findErrorNums(int* nums, int numsSize, int* returnSize)
{
    int* result = (int*)malloc(2 * sizeof(int));
    *returnSize = 2;
    int rightSum = (double)numsSize / 2 * (1 + numsSize);
    int sum = 0, dup = -1;
    for (int i = 1; i <= numsSize; ++i)
    {
        if (dup == -1)
        {
            for (int j = i + 1; j <= numsSize; ++j)
                if (nums[i - 1] == nums[j - 1])
                {
                    result[0] = nums[i - 1];
                    dup = j - 1;
                    sum -= nums[i - 1] * 2;
                    break;
                }
        }
        sum += nums[i - 1];

    }
    result[1] = rightSum - sum - result[0];

    return result;
}