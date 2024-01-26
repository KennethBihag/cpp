#include "threading.h"

#include <stdio.h>
#include <malloc.h>

extern char *g_hrule;
extern char *g_srule;
void *results[0xFF] = {0};

#ifndef _WIN32
typedef struct
{
    thrd_t id;
    thrd_func func;
    void *args;
    void *result;
} MyThread;
#endif

static void thrd_create_dummy(unsigned long *, int (*func)(void *), void *);
static int RunInNewThrd(void *);

void parallel_run(thrd_func *funcs, void **args, int fcount)
#ifdef _WIN32
{
    for (int i = 0; i < fcount; ++i)
    {
        void *result = funcs[i](*(args + i));
        results[i] = result;
        if (result)
        {
            printf(g_hrule);
            printf("Result%02d\n\t(int): %d\n", i + 1, *(int *)result);
            printf("\t(char): %c\n", *(char *)result);
            printf("\t(string):%s\n", (const char *)result);
            printf(g_hrule);
        }
    }
}
#else
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
    }
}
#endif

static void thrd_create_dummy(unsigned long *ID, int (*FUNC)(void *), void *ARGS)
{
    FUNC(ARGS);
}

static int RunInNewThrd(void *arg)
#ifndef _WIN32
{
    MyThread *mth = (MyThread *)arg;
    mth->result = mth->func(mth->args);
    if (mth->result)
    {
        printf(g_hrule);
        printf("Result%010d\n\t(int): %d\n", mth->id, *(int *)mth->result);
        printf("\t(char): %c\n", *(char *)mth->result);
        printf("\t(string):%s\n", (const char *)mth->result);
        printf(g_hrule);
    }
    return mth->result ? 0 : -1;
}
#else
{
    return 0;
}
#endif