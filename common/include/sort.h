
// Sort algorithms implementations.
// Each have 2 versions, modifying orig. data and returning new data.

#ifndef COMMON_SORT_H
#define COMMON_SORT_H

// does not work for pointer types
// #define bubblesort(...) _Generic((VA_ARG1(__VA_ARGS__)),\
// 	int*: bubblesort_int, float*: bubblesort_flt)(__VA_ARGS__)

#ifdef __cplusplus
extern "C"
{
	int *bubblesort_int(int *origArray, unsigned int length, int order = 1);
	float *bubblesort_flt(float *origArray, unsigned int length, int order = 1);
	int *mergesort_int(int *origArray, unsigned int length, int order = 1);
#else
int *bubblesort_int(int *origArray, unsigned int length, int order);
float *bubblesort_flt(float *origArray, unsigned int length, int order);
int *mergesort_int(int *origArray, unsigned int length, int order);
#endif

#ifdef __cplusplus
}
#endif

#endif