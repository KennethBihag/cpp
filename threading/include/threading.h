#ifndef THREADING_H
#define THREADING_H

#ifdef _WIN32
#include <pthread.h>
#else
#include <threads.h>
#endif

typedef void *(*thrd_func)(void *);

// code: -1:not run, 0:success, 1:fail
typedef struct
{
	thrd_func func;
	void *args;
	void *result;
	signed char *code;
#ifndef _WIN32
	thrd_t id;
#else
	pthread_t id;
#endif
} MyThread;

#ifdef __cplusplus
extern "C"
{
#endif

extern MyThread *mythreads[0xFF];

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
int parallel_run(MyThread *thrds[], unsigned char fcount);

#ifdef __cplusplus
}
#endif

#endif