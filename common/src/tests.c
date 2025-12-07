#include "tests.h"

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "permute.h"
#include "sort.h"

void bubblesort_test(int argc, const char **argv)
{
	if (argc < 2)
	{
		printf("Usage: <int> ...\n");
		return;
	}

	int* o = (int*)malloc((argc - 1) * sizeof(int));
	int olength = argc - 1;
	for (int i = 0; i < olength; i++)
	{
		sscanf(argv[i + 1], "%d", o + i);
	}
	int *copied = bubblesort_int(o, olength, 1);
	printf("ORIG: ");
	print_intarr_elems(o, olength);
	free(o);
	printf("NEW: ");
	print_intarr_elems(copied, olength);
	free(copied);
	float* p = (float*)malloc((argc - 1) * sizeof(float));
	for (int i = 0; i < olength; i++)
	{
		p[i] = (float)atof(*(argv + i + 1));
	}
	float *copied2 = bubblesort_flt(p, olength, -1);
	printf("ORIG: ");
	print_fltarr_elems(p, olength);
	free(p);
	printf("NEW: ");
	print_fltarr_elems(copied2, olength);
	free(copied2);

	return;
}

void mergesort_test(int argc, const char **argv)
{
	if (argc < 2)
	{
		printf("Usage: <int> ...\n");
		return;
	}
	int* o = (int*)malloc((argc - 1) * sizeof(int));
	int olength = argc - 1;
	for (int i = 0; i < olength; i++)
		sscanf(argv[i + 1], "%d", o + i);
	mergesort_int(o, olength, 1);
	free(o);
	return;
}

void *permute_test(void *arg)
{
	const int len = *(const int*)arg;
	const char *const numbers =
		(const char *)((char*)arg + sizeof(int));
	int r = 0, c = 0;
	char *res = permute_ch(numbers, len, &r, &c);
	int orders = 0;
	for (int i = 0; i < r; ++i)
	{
		++orders;
		for (int j = 0; j < c; ++j)
			printf("%hd ", res[i * c + j]);
		printf("\n");
	}
	printf("%d orders\n", orders);
	free((void *)res);
	return NULL;
}