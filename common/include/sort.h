
// Sort algorithms implementations.
// Each have 2 versions, modifying orig. data and returning new data.

#ifndef SORT_H
#define SORT_H
// does not work for pointer types
// #define bubblesort(...) _Generic((VA_ARG1(__VA_ARGS__)),\
// 	int*: bubblesort_int, float*: bubblesort_flt)(__VA_ARGS__)

#include "exports.hpp"

#ifdef __cplusplus
extern "C"
{
#else
#endif
	COMMON_API int *bubblesort_int(int *origArray, unsigned int length, int order);
	COMMON_API float *bubblesort_flt(float *origArray, unsigned int length, int order);
	COMMON_API int *mergesort_int(int *origArray, unsigned int length, int order);
#ifdef __cplusplus
}
#endif

#endif