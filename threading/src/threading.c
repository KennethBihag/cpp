#include "threading.h"

#include <stdio.h>
#include <malloc.h>

extern char *g_hrule;
extern char *g_srule;
void *results[0xFF] = {0};

typedef struct
{
    thrd_func func;
    void *args;
    void *result;
#ifndef _WIN32
    thrd_t id;
#else
    pthread_t id;
#endif
} MyThread;

static void thrd_create_dummy
#ifndef _WIN32
    (thrd_t *ID, int (*FUNC)(void *), void *ARGS)
#else
    (pthread_t *ID, thrd_func FUNC, void *ARGS)
#endif
{
    FUNC(ARGS);
}

static
#ifndef _WIN32
    int
#else
    void *
#endif
    RunInNewThrd(void *arg)
{
    MyThread *mth = (MyThread *)arg;
    mth->result = mth->func(mth->args);
    if (mth->result)
    {
        printf(g_hrule);
        printf("Result%010d\n\t(int): %d\n", (unsigned long)mth->id, *(int *)mth->result);
        printf("\t(char): %c\n", *(char *)mth->result);
        printf("\t(string):%s\n", (const char *)mth->result);
        printf(g_hrule);
    }
#ifndef _WIN32
    return mth->result ? 0 : -1;
#else
    void *retval = mth->result ? NULL : (void *)-1;
    pthread_exit(retval);
    return retval;
#endif
}

void parallel_run(thrd_func *funcs, void **args, int fcount)
#ifndef _WIN32
{
    MyThread threads[fcount];
    for (int i = 0; i < fcount; ++i)
    {
        threads[i].func = funcs[i];
        threads[i].args = args[i];
        thrd_create(&threads[i].id, RunInNewThrd, (void *)(threads + i));
        // thrd_create_dummy(&threads[i].id, RunInNewThrd, (void *)(threads + i));
    }
    for (int i = 0; i < fcount; i++)
    {
        int code;
        thrd_join(threads[i].id, &code);
        results[i] = threads[i].result;
        printf("Thread%010lu exited with %d\n",
               threads[i].id, code);
    }
}
#else
{
    MyThread threads[fcount];
    for (int i = 0; i < fcount; ++i)
    {
        threads[i].func = funcs[i];
        threads[i].args = args[i];
        pthread_create(&threads[i].id, NULL, RunInNewThrd, (void *)(threads + i));
        // thrd_create_dummy(&threads[i].id, RunInNewThrd, (void *)(threads + i));
    }
    for (int i = 0; i < fcount; i++)
    {
        int code;
        void *codeptr = (void *)&code;
        pthread_join(threads[i].id, codeptr);
        results[i] = threads[i].result;
        printf("Thread%010llu exited with %d\n",
               threads[i].id, code);
    }
}
#endif
