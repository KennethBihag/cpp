#include "threading.h"

#include <stdio.h>
#include <malloc.h>

void *results[0xFF] = {0};

void parallel_run(thrd_func *func, void **args, int fcount)
{
#ifdef _WIN32
#else
#endif
    for (int i = 0; i < fcount; ++i)
    {
        void *result = func[i](*(args + i));
        results[i] = result;
        if (result)
        {
            printf("Result%02d\n\t(int): %d\n", i + 1, *(int *)result);
            printf("\t(char): %c\n", *(char *)result);
            printf("\t(string):%s\n", (const char *)result);
        }
    }
}