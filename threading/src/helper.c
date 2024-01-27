#include <malloc.h>
#include <stdio.h>
#include <string.h>

#define INIT_RES(A)                                      \
    void *res = malloc(sizeof(signed char) + sizeof(A)); \
    signed char *code = (signed char *)res;

static char g_sharedch = 'S';
const char *g_hrule =
    "----------------------------------------------------\n";
const char *g_srule =
    "****************************************************\n";

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
    if (a == 'm' || a == 'f')
        memcpy((void *)r, (const void *)"GOOD", 4);
    else
        memcpy((void *)r, (const void *)"GAY", 3);
    return r;
}

// returns code and sum as ints
void *addtl_helper(void *args)
{
    printf("SHARED CHAR:%c\n", g_sharedch++);
    int *numbers = (int *)args;
    INIT_RES(int)
    *(int *)(res + 1) = additional(numbers[0], numbers[1]);
    *code = 0;
    return res;
}

// returns code as void* and string as const char*
void *isgay_helper(void *arg)
{
    printf("SHARED CHAR:%c\n", g_sharedch++);
    INIT_RES(const char *)
    const char **tmp = (const char **)(res + 1);
    *tmp = isgay(*(char *)arg);
    *code = 0;
    return res;
}

// returns both 0's for code & result as void*
void *dummy_helper(void *args)
{
    printf("SHARED CHAR:%c\n", g_sharedch++);
    INIT_RES(void *)
    *code = 0;
    void **tmp = (void **)(res + 1);
    *tmp = (void *)0;
    printf("This is dumb!\n");
    return res;
}