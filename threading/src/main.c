#include "threading.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sharedInt;
thrd_start_t funcp = incFunc;

int main(int argc,const char **argv)
{
    int delay = 10;
    if(argc>1)
        delay = atoi(argv[1]);
    
    char* os = getenv("OS");
    if(os == NULL)
        os = "linux-gnu";
    char osstr[64]={0};
    strcat(osstr,"Running in a ");
    strcat(osstr,os);
/*     if (strcmp(os, "Windows_NT")==0)
        strcat(osstr," Windows ");
    else
        strcat(osstr," Linux "); */
    strcat(osstr," environment.\n");
    printf(osstr);
    system("pwd");

    
    multithrd_share_rsc(funcp, 10, (void*)&sharedInt);
    printf("\n\n---------------------------------\n\n");
    two_threads_test(delay);
    printf("\n\n---------------------------------\n\n");
    return multithrd_share_rsc(funcp, 10, (void*)&sharedInt);
}
