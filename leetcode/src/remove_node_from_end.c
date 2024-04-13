#include "remove_node_from_end.h"

#include "common/include/singly_linked_list.h"

struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
#ifndef RECURSIVE
    struct ListNode* nodes[30];
    struct ListNode* node = head;
    int i = -1;
    do {
        i++;
        nodes[i] = node;
        node = node->next;
    } while (node != 0);
    int bfi = i - n;
    if (bfi < 0)
        head = head->next;
    else
        nodes[bfi]->next = nodes[bfi]->next->next;
    return head;
#else
#endif
}