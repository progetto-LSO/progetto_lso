#include "request_config.h"

typedef struct ListNode {
    char isbn[MAX_REQUEST_BUFFER_LENGTH];
    struct ListNode* next;
} ListNode;

ListNode* build_list_node(int key);

void list_insert(ListNode** list, int key);

void print_list(ListNode* list);