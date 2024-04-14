#include "leetcode.h"

int maximalRectangle(char **matrix, int matrixSize, int *matrixColSize)
{
    int maxArea = 0;
    // signed char lengths[matrixSize][*matrixColSize];
    //for each column
    for (int i = 0; i < *matrixColSize; i++)
    {
        int minLen = __INT_MAX__;
        int area = 0;
        //for each row
        for (int j = 0; j < matrixSize; j++)
        {
            int x = i;
            int len = 0;
            do
            {
                if (matrix[j][x] == '1')
                {
                    x--;
                }
                else if (matrix[j][x] == '0')
                    break;
            } while (x >= 0);
            len = i - x;
            if (len > 0)
            {
                minLen = minLen < len ? minLen : len;
                area += minLen;
                maxArea = maxArea > len ? maxArea : len;
            }
            maxArea = maxArea > area ? maxArea : area;
        }
    }

    return maxArea;
}