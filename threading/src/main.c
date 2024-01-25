#ifdef _WIN32
#include "winthreading.h"
#else
#include "linuxthreading.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int additional(int a, int b)
{
    printf("Adding %d & %d\n", a, b);
    return a + b;
}

const char *isgay(char a)
{
    printf("Is %c gay or not?\n", a);
    const char *r = (const char *)malloc(sizeof(const char) * 5);
    memset((void *)(r + 3), 0, 2);
    if (a == 'm' || a == 'b' || a == 'f' || a == 'g')
        memcpy((void *)r, (const void *)"GOOD", 4);
    else
        memcpy((void *)r, (const void *)"GAY", 3);
    return r;
}

#ifdef _WIN32

void *addtl_helper(void *args)
{
    int *numbers = (int *)args;
    int *ans = (int *)malloc(sizeof(int));
    *ans = additional(numbers[0], numbers[1]);
    return (void *)ans;
}

void *isgay_helper(void *arg)
{
    char *arg_ch = (char *)arg;
    return (void *)isgay(*arg_ch);
}

void *dummy_helper(void *args)
{
    printf("This is dumb!\n");
    return NULL;
}

#else

int sharedInt;
thrd_start_t funcp = incFunc;

#endif

#ifdef BUILD_MAIN
int main
#else
int threading_test
#endif
    (int argc, const char **argv)
{
    int fcount = 3;

#ifdef _WIN32
    printf("Running in windows.\n");

    thrd_func *funcs =
        (thrd_func *)malloc(4 * sizeof(thrd_func));
    funcs[0] = addtl_helper;
    funcs[1] = isgay_helper;
    funcs[2] = dummy_helper;

    void **args = (void **)malloc(sizeof(void *) * 4);
    int additionArgs[] = {30, -13};
    args[0] = (void *)additionArgs;
    char gayArg = 'g';
    args[1] = (void *)&gayArg;
    args[2] = NULL;
    void **results = parallel_run(funcs, args, fcount);

    printf("Results from parallel_run:\n");
    printf("\tSUM: %d\n", *(int *)(results[0]));
    printf("\tGAY: %s\n", (const char *)(results[1]));
    printf("\tDUMMY: %s\n", (const char *)(results[2]));

    free(args);
    printf("ARGS FREED\n");
    for (int i = 0; i < fcount; ++i)
        free(results[i]);
    printf("RESULTS FREED\n");
    free(results);
    printf("RESULT ARRAY FREED\n");

#else
    printf("Running in Linux.\n");
//     int delay = 10;
//     if(argc>1)
//         delay = atoi(argv[1]);

//     char* os = getenv("OS");
//     if(os == NULL)
//         os = "linux-gnu";
//     char osstr[64]={0};
//     strcat(osstr,"Running in a ");
//     strcat(osstr,os);
// /*     if (strcmp(os, "Windows_NT")==0)
//         strcat(osstr," Windows ");
//     else
//         strcat(osstr," Linux "); */
//     strcat(osstr," environment.\n");
//     printf(osstr);
//     system("pwd");

//     multithrd_share_rsc(funcp, 10, (void*)&sharedInt);
//     printf("\n\n---------------------------------\n\n");
//     two_threads_test(delay);
//     printf("\n\n---------------------------------\n\n");
//     return multithrd_share_rsc(funcp, 10, (void*)&sharedInt);
#endif
    printf("Done!!!\n");

    return 0;
}
