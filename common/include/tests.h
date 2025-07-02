#ifndef TESTS_H
#define TESTS_H

#include "exports.hpp"

#ifdef __cplusplus
extern "C"
{
#endif

    COMMON_API void bubblesort_test(int, const char**);
    COMMON_API void mergesort_test(int, const char**);
    COMMON_API void *permute_test(void*);

#ifdef __cplusplus
}
#endif

#endif