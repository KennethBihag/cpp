#include "threading.h"

#include <stdio.h>
#include <malloc.h>

int additional(int a, int b);
const char *isgay(char a);
void *addtl_helper(void *args);
void *isgay_helper(void *arg);
void *dummy_helper(void *args);

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
#else
    printf("Running in Linux.\n");
#endif
    thrd_func funcs[] = {addtl_helper, isgay_helper, dummy_helper};
    int additionArgs[] = {30, -13};
    char gayArg = 'g';
    int funcsz = sizeof(funcs) / sizeof(funcs[0]);
    void *args[funcsz];
    args[0] = (void *)additionArgs;
    args[1] = (void *)&gayArg;
    args[2] = NULL;
    parallel_run(funcs, args, fcount);

    printf("Results from parallel_run:\n");
    printf("\tSUM: %d\n", *(int *)(results[0]));
    printf("\tGAY: %s\n", (const char *)(results[1]));
    printf("\tDUMMY: %s\n", (const char *)(results[2]));

    for (int i = 0; i < fcount; ++i)
        free(results[i]);
    printf("RESULTS FREED\n");

    printf("Done!!!\n");

    return 0;
}
