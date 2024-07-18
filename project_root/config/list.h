#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "request_config.h"

typedef struct ListNode {
    char isbn[MAX_REQUEST_BUFFER_LENGTH];
    struct ListNode* next;
} ListNode;

ListNode* build_list_node(char isbn[MAX_REQUEST_BUFFER_LENGTH]);
void list_insert(ListNode** list, char isbn[MAX_REQUEST_BUFFER_LENGTH]);
void print_list(ListNode* list);
