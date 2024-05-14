#ifndef LEETCODE_H
#define LEETCODE_H

#ifdef __cplusplus
extern "C" {
#endif

/* caller must call free */
int* findErrorNums(int* nums, int numsSize, int* returnSize);
int maximalRectangle(char **matrix, int matrixSize, int *matrixColSize);

#ifdef __cplusplus
}
#endif

#endif