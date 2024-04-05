#include "threading.h"

#include <stdio.h>
#include <malloc.h>

extern char *g_hrule;
extern char *g_srule;

MyThread *mythreads[0xFF] = {0};

#ifndef _WIN32
static int thrd_create_dummy(thrd_t *ID, int (*FUNC)(void*), void *ARGS)
{
    *ID = *ID % 256;
    int code = FUNC(ARGS);
    printf("Thread%03lu exited with %d\n",
           *ID, code);
    return code;
}
#else
static void thrd_create_dummy(pthread_t *ID, thrd_func FUNC, void *ARGS)
{
    *ID = *ID % 256;
    void *code = FUNC(ARGS);
    printf("Thread%03llu exited with %hd\n",
           *ID, *(signed char *)code);
}
#endif

static
#ifndef _WIN32
    int
#else
    void *
#endif
    RunInNewThrd(void *arg)
{
    MyThread *mth = (MyThread *)arg;
    void *tmpres = mth->func(mth->args);
    mth->code = (signed char *)tmpres;
    mth->result = tmpres + 1;
#ifndef _WIN32
    return *mth->code;
#else
    return (void*)mth->code;
#endif
}

int parallel_run(MyThread *thrds[], unsigned char fcount)
#ifndef _WIN32
{
    for (int i = 0; i < fcount; ++i)
#ifndef NO_PARALLEL
        thrd_create(&thrds[i]->id, RunInNewThrd, (void*)thrds[i]);
#else
        thrd_create_dummy(
            &thrds[i]->id, RunInNewThrd, (void*)thrds[i]);
#endif

#ifndef NO_PARALLEL
    for (int i = 0; i < fcount; i++)
        thrd_join(thrds[i]->id, NULL);
#endif
    return 0;
}
#else
{
    for (int i = 0; i < fcount; ++i)
#ifndef NO_PARALLEL
        pthread_create(&thrds[i]->id, NULL, RunInNewThrd, (void*)(thrds[i]));
#else
        thrd_create_dummy(&thrds[i]->id, RunInNewThrd, (void*)thrds[i]);
#endif
#ifndef NO_PARALLEL
    for (int i = 0; i < fcount; i++)
        pthread_join(thrds[i]->id, NULL);
#endif
    return 0;
}
#endif
