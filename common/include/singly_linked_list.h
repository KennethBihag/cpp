#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

struct ListNode {
    int val;
    struct ListNode *next;
};

const char *node_to_string(struct ListNode*);

#ifdef __cplusplus
}
#endif

#endif