#ifndef PERMUTE_H
#define PERMUTE_H

#ifdef __cplusplus
extern "C"
{
#endif

	int *permute(const int *const nums, int len, int *rrows, int *rcols);
	char *permute_ch(const char *const nums, int len, int *rrows, int *rcols);

#ifdef __cplusplus
}
#endif

#endif