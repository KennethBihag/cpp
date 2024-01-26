#ifndef THREADING_H
#define THREADING_H

#ifdef _WIN32
#include <pthread.h>
#else
#include <threads.h>
#endif

typedef void *(*thrd_func)(void *);
extern void *results[0xFF];

#ifdef __cplusplus
extern "C"
{
#endif

	/*
	Run an array of functions sequentially by index. Caller must call free on global results
	if needed.
	PARAMS:
		func - array of functions to run
		args - array of any data type pointer to args of a function
		fcount - number of functions passed and results expected
	RETURNS:
		none but modifies the global results array
	*/
	void parallel_run(thrd_func *func, void **args, int fcount);

#ifdef __cplusplus
}
#endif

#endif