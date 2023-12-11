#ifndef THREADING_H
#define THREADING_H

#include <threads.h>

extern mtx_t mtxShared;

int two_threads_test(int delay);
int multithrd_share_rsc(thrd_start_t,int threads,void *arg);
int incFunc(void*);

#endif