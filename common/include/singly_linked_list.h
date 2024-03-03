#ifndef COMMON_SINGLY_LINKED_LIST_H
#define COMMON_SINGLY_LINKED_LIST_H

struct ListNode {
    int val;
    struct ListNode *next;
};

#ifdef __cplusplus
extern "C" {
#endif
const char *node_to_string(struct ListNode*);
#ifdef __cplusplus
}
#endif

#endif