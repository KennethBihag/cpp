#include <malloc.h>
#include <stdio.h>
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