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
    int a = 0, b = 1;
    char c = 'a' - 1;
    for (int i = 0; i < fcount; ++i)
    {
        mythreads[i] = (MyThread *)malloc(sizeof(MyThread));
        a++, b++, c++;
        if (i % 3 == 0)
        {
            int *additionArgs = (int *)malloc(2 * sizeof(int));
            additionArgs[0] = a, additionArgs[1] = b;
            mythreads[i]->func = addtl_helper;
            mythreads[i]->args = (void *)additionArgs;
        }
        else if (i % 3 == 1)
        {
            char *gayArg = (char *)malloc(sizeof(char));
            *gayArg = c;
            mythreads[i]->func = isgay_helper;
            mythreads[i]->args = (void *)gayArg;
        }
        else
        {
            mythreads[i]->func = dummy_helper;
            mythreads[i]->args = NULL;
        }
    }

    int code = parallel_run(mythreads, fcount);

    printf("Results from parallel_run:\n");
    for (int i = 0; i < fcount; i++)
    {
        if (i % 3 == 0)
        {
            int *sum = (int *)(mythreads[i]->result);
            printf("\tSUM: %d\n", *sum);
        }
        else if (i % 3 == 1)
        {
            const char **mess = (const char **)(mythreads[i]->result);
            printf("\tGAY: %s\n", *mess);
        }
        else
        {
            printf("\tDUMMY: %s\n", (const char *)mythreads[i]->result);
        }
    }

    for (int i = 0; i < fcount; ++i)
    {
        free(mythreads[i]->args);
        // if(i%3 != 1) free(mythreads[i]->result);
    }

    printf("Done!!!\n");
    return code;
}
