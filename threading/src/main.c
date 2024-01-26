#include "threading.h"

#include <stdio.h>
#include <stdlib.h>
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
    int fcount = 10;

#ifdef _WIN32
    printf("Running in windows.\n");
#else
    printf("Running in Linux.\n");
#endif
    thrd_func funcs[fcount];
    void *args[fcount];
    int a = 0, b = 1;
    char c = 'a' - 1;
    for (int i = 0; i < fcount; ++i)
    {
        a++, b++, c++;
        if (i % 3 == 0)
        {
            int *additionArgs = (int *)malloc(2 * sizeof(int));
            additionArgs[0] = a, additionArgs[1] = b;
            funcs[i] = addtl_helper;
            args[i] = (void *)additionArgs;
        }
        else if (i % 3 == 1)
        {
            char *gayArg = (char *)malloc(sizeof(char));
            *gayArg = c;
            funcs[i] = isgay_helper;
            args[i] = (void *)gayArg;
        }
        else
        {
            funcs[i] = dummy_helper;
            args[i] = NULL;
        }
    }

    parallel_run(funcs, args, fcount);

    printf("Results from parallel_run:\n");
    for (int i = 0; i < fcount; i++)
    {
        if (i % 3 == 0)
            printf("\tSUM: %d\n", *(int *)(results[i]));
        else if (i % 3 == 1)
            printf("\tGAY: %s\n", (const char *)(results[i]));
        else
            printf("\tDUMMY: %s\n", (const char *)(results[i]));
    }

    for (int i = 0; i < fcount; ++i)
    {
        free(args[i]);
        free(results[i]);
    }

    printf("Done!!!\n");
    return EXIT_SUCCESS;
}
