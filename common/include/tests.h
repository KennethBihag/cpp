#ifndef COMMON_TESTS_H
#define COMMON_TESTS_H

#define API_DECL

#ifdef __cplusplus
extern "C" {
#endif

#ifdef SHARED_LIB
	#ifdef EXPORT_LIB
		#define API_DECL __declspec(dllexport)
	#else
		#define API_DECL __declspec(dllimport)
	#endif
#endif

API_DECL void bubblesort_test(int, const char **);

#ifdef __cplusplus
}
#endif

#endif