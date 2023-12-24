#include "tests.h"

#include <malloc.h>
#include <stdio.h>

#include "sort.h"

void bubblesort_test(int argc, const char **argv)
{
	if (argc < 2)
	{
		printf("Usage: <int> ...\n");
		return;
	}

	int o[argc - 1];
	int olength = sizeof(o) / sizeof(o[0]);
	for (int i = 0; i < olength; i++)
	{
		sscanf(argv[i + 1], "%d", o + i);
	}
	int *copied = bubblesort_int(o, olength, 1);
	printf("ORIG:");
	for (int i = 0; i < olength; ++i)
		printf(" %d", o[i]);
	printf("\nNEW:");
	for (int i = 0; i < olength; ++i)
		printf(" %d",copied[i]);
	printf("\n");
	free(copied);

	float p[argc - 1];
	for (int i = 0; i < olength; i++)
	{
		p[i] = (float)atof(*(argv + i + 1));
	}
	float *copied2 = bubblesort_flt(p, olength, -1);
	printf("ORIG:");
	for (int i = 0; i < olength; ++i)
		printf(" %f", p[i]);
	printf("\nNEW:");
	for (int i = 0; i < olength; ++i)
		printf(" %f",copied2[i]);
	printf("\n");
	free(copied2);

	return;
}