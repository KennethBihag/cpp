#ifndef WINTHREADING_H
#define WINTHREADING_H

#include <pthread.h>

#ifdef _WIN32
typedef void *(*thrd_func)(void *);
#else
#endif

#ifdef __cplusplus
extern "C"
{
#endif

	/*
	Run an array of functions sequentially by index. Caller must call free on returned results.
	PARAMS:
		func - array of functions to run
		args - array of any data type pointer to args of a function
		fcount - number of functions passed and results expected
	RETURNS:
		an array to any data type pointer to a function result
	*/
	void **parallel_run(thrd_func *func, void **args, int fcount);

#ifdef __cplusplus
}
#endif

#endif