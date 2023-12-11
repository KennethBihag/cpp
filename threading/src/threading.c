#include "threading.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>

#include "common/include/common.h"

struct ECA {
    char ch;
    int k;
};

mtx_t mtxShared;

int echelper(void *ecaStruct)
{
    struct ECA *a = (struct ECA*)ecaStruct;
    char newc = 0;
    for (char x = a->ch;x < 'K';x++)
    {
        newc = encrypt_char(x, a->k);
        printf("Orig:%c -> New:%c\n", x, newc);
        printf("Orig:%d -> New:%d\n", x, newc);
    }
    return newc;
}

static int timeout(void *seconds)
{
    int s = *((int*)seconds);
    char *os = getenv("OS");
    if(os == NULL)
        os = "linux-gnu";
    char formatted[64] = { 0 };
    if(strcmp(os,"Windows_NT")==0){
        sprintf(formatted, "timeout %d /nobreak", s);
    } else {
        sprintf(formatted, "sleep %d", s);
    }
    system(formatted);
    return s * 1000;
}
 
int two_threads_test(int delay)
{
    thrd_t child = 0;
    int createdThrd = thrd_create(&child, timeout, (void*)&delay);
    if (createdThrd != thrd_success)
    {
        printf("Could not created thread\n");
        return EXIT_FAILURE;
    }

    printf("Let's wait a while and start another thread.\n");
    thrd_t child2 = 0;
    struct ECA ecarg;
    ecarg.ch = 'A'; ecarg.k = 100;
    createdThrd = thrd_create(&child2, echelper, (void*)&ecarg);
    thrd_detach(child2);

    int millis = 0;
    thrd_join(child, &millis);
    printf("%d milliseconds\n",millis);
    return EXIT_SUCCESS;
}

/*
test on mutex by accessing a common int variable
somehow works properly in Windows, not in Linux
*/
int multithrd_share_rsc(thrd_start_t func, int threads, void* arg)
{
    mtx_init(&mtxShared,mtx_plain);
    thrd_t ths[threads];
    for (int i = 0;i < threads;i++)
    {
        int created = thrd_create(ths + i, func, arg);
        if (created != thrd_success)
        {
            printf("Failed to create thread %d\n", i + 1);
            mtx_destroy(&mtxShared);
            return EXIT_FAILURE;
        }
    }
    int res;
    for(int i=0;i<threads;i++){
        thrd_join(ths[i],&res);
        printf("Thread-%d done. ARG:%d\n",i+1,res);
    }
    mtx_destroy(&mtxShared);
    return EXIT_SUCCESS;
}

int incFunc(void* sharedInt)
{
    int *iSharedInt = (int*)sharedInt;
    mtx_lock(&mtxShared);
    (*iSharedInt)++;
    mtx_unlock(&mtxShared);
    return *iSharedInt;
}
