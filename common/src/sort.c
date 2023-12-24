#include "sort.h"

#include <malloc.h>
#include <string.h>

void swap_int(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
	return;
}

void swap_float(float *a, float *b)
{
	int t = *a;
	*a = *b;
	*b = t;
	return;
}

/*
Returns a sorted array of integers, allocated in the heap.
*/
int *bubblesort_int(int *origArray, unsigned int length, int order)
{
	int *sorted = (int *)malloc(length * sizeof(int));
	memcpy(sorted, origArray, (size_t)(length * sizeof(int)));

	for (int i = 0; i < length - 1; i++)
		for (int j = 0; j < length - 1; j++)
			if (order <= 0)
			{
				if (sorted[j] < sorted[j + 1])
					swap_int(sorted + j, sorted + j + 1);
			}
			else
			{
				if (sorted[j] > sorted[j + 1])
					swap_int(sorted + j, sorted + j + 1);
			}

	return sorted;
}

float *bubblesort_flt(float *origArray, unsigned int length, int order)
{
	float *sorted = (float *)malloc(length * sizeof(float));
	memcpy(sorted, origArray, (size_t)(length * sizeof(float)));

	for (int i = 0; i < length - 1; i++)
		for (int j = 0; j < length - 1; j++)
			if (order <= 0)
			{
				if (sorted[j] < sorted[j + 1])
					swap_float(sorted + j, sorted + j + 1);
			}
			else
			{
				if (sorted[j] > sorted[j + 1])
					swap_float(sorted + j, sorted + j + 1);
			}

	return sorted;
}
