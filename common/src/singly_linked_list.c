#include "singly_linked_list.h"

#include <malloc.h>
#include <stdio.h>
#include <string.h>

const char *node_to_string(struct ListNode *node){
    char *result = (char*) malloc(32);
    result[0] = 0;

    while(node){
        if(*result)
            strcat(result,", ");
        char tmp[32]="";
        sprintf(tmp,"%d",node->val);
        strcat(result, (const char*)tmp);
        node=node->next;
    }

    return (const char*)result;
}