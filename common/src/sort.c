#include "sort.h"

#include <malloc.h>
#include <stdio.h>
#include <string.h>

#include "common.h"

// internal functions

static void swap_int(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
	return;
}

static void swap_float(float *a, float *b)
{
	int t = *a;
	*a = *b;
	*b = t;
	return;
}

static void printTabs(int tcount)
{
	for (; tcount > 0; --tcount)
		printf("\t");
	return;
}

// public functions
/*
Returns a sorted array of integers, allocated in the heap.
*/
int *bubblesort_int(int *origArray, unsigned int length, int order)
{
	int *sorted = (int *)malloc(length * sizeof(int));
	memcpy(sorted, origArray, (size_t)(length * sizeof(int)));

	for (unsigned int i = 0; i < length - 1; i++)
		for (unsigned int j = 0; j < length - 1; j++)
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

	for (unsigned int i = 0; i < length - 1; i++)
		for (unsigned int j = 0; j < length - 1; j++)
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

int *mergesort_int(int *origArray, unsigned int length, int order)
{
	int *sortedArray = (int*)malloc(length*sizeof(int));
	void mergesort_asc(int*, unsigned int, int*);
	int level = 0;
	switch (order)
	{
	case 1:
		mergesort_asc(origArray, length, &level);
		break;
	default:
		break;
	}
	memcpy(sortedArray, origArray, length*sizeof(int));
	return sortedArray;
}

void mergesort_asc(int *origArray, unsigned int length, int *level)
{
	if (length < 2)
		return;

	(*level)++;
	printf("LEVEL%d\n", *level);
	// break part
	int iMid = length % 2 ? length / 2 : length / 2 - 1;
	unsigned int leftSize = iMid + 1, rightSize = length - iMid - 1;
	int* leftArr = (int*)malloc(leftSize * sizeof(int));
	int* rightArr = (int*)malloc(rightSize * sizeof(int));
	
	memcpy(leftArr, origArray, leftSize * sizeof(int));
	if (length % 2 == 0)
		memcpy(rightArr, origArray + rightSize, rightSize * sizeof(int));
	else
		memcpy(rightArr, origArray + rightSize + 1, rightSize * sizeof(int));
	printTabs(*level - 1);
	printf("Orig. array:");
	print_intarr_elems(origArray, length);
#ifdef LOG_DBG
	printTabs(*level - 1);
	printf("Left: ");
	print_intarr_elems(leftArr, leftSize);
#endif
	mergesort_asc(leftArr, leftSize, level);
#ifdef LOG_DBG
	printTabs(*level - 1);
	printf("Right: ");
	print_intarr_elems(rightArr, rightSize);
#endif
	mergesort_asc(rightArr, rightSize, level);
	// sort and merge part
	unsigned int i = 0, j = 0, k = 0;
	for (; k < length && i < leftSize && j < rightSize; ++k)
	{
		if (leftArr[i] < rightArr[j])
			origArray[k] = leftArr[i++];
		else
			origArray[k] = rightArr[j++];
	}
	while (i < leftSize)
		origArray[k++] = leftArr[i++];
	while (j < rightSize)
		origArray[k++] = rightArr[j++];

	printTabs(*level - 1);
	printf("Sorted array:");
	print_intarr_elems(origArray, length);
	(*level)--;

	free(leftArr); free(rightArr);
	return;
}
