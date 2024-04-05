#include "permute.h"

#include <assert.h>
#include <malloc.h>
#include <stdio.h>

int *permute(const int *const nums, int len, int *rrows, int *rcols)
{
	if (len < 0 || nums == NULL)
		assert("Array must not be empty!");
	if (len == 1)
	{
		*rrows = *rcols = 1;
		int *res = (int *)malloc(sizeof(int));
		res[0] = *nums;
		return res;
	}
	else
	{
		int rows, cols;
		int *tmp = permute(nums + 1, len - 1, &rows, &cols);
		*rcols = len;
		*rrows = len * rows;
		int *res = (int *)malloc((*rrows) * (*rcols) * sizeof(int));

		int tmpp = 0, cur;
		for (int i = 0; i < *rrows; ++i)
		{
			for (int j = 0; j < *rcols; ++j)
			{
				cur = i * len + j;
				int offset = cur / (rows * len);
				if (cur % *rcols == offset)
				{
					res[cur] = *nums;
				}
				else
				{
					res[cur] = tmp[tmpp++];
				}
			}
			tmpp = tmpp >= rows * cols ? 0 : tmpp;
		}

		free(tmp);
		return res;
	}
}

char *permute_ch(const char *const nums, int len, int *rrows, int *rcols)
{
	if (len < 0 || nums == NULL)
		assert("Array must not be empty!");
	if (len == 1)
	{
		*rrows = *rcols = 1;
		char *res = (char*)malloc(sizeof(char));
		res[0] = *nums;
		return res;
	}
	else
	{
		int rows, cols;
		char *tmp = permute_ch(nums + 1, len - 1, &rows, &cols);
		*rcols = len;
		*rrows = len * rows;
		char *res = (char *)malloc((*rrows) * (*rcols) * sizeof(char));

		int tmpp = 0, cur;
		for (int i = 0; i < *rrows; ++i)
		{
			for (int j = 0; j < *rcols; ++j)
			{
				cur = i * len + j;
				int offset = cur / (rows * len);
				if (cur % *rcols == offset)
				{
					res[cur] = *nums;
				}
				else
				{
					res[cur] = tmp[tmpp++];
				}
			}
			tmpp = tmpp >= rows * cols ? 0 : tmpp;
		}

		free(tmp);
		return res;
	}
}
