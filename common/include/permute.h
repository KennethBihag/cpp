#ifndef PERMUTE_H
#define PERMUTE_H

#include "exports.hpp"

#ifdef __cplusplus
extern "C"
{
#endif

	COMMON_API int *permute(const int *const nums, int len, int *rrows, int *rcols);
	COMMON_API char *permute_ch(const char *const nums, int len, int *rrows, int *rcols);

#ifdef __cplusplus
}
#endif

#endif