#include "list.h"
#include "singly_linked_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

ListNode* build_list_node(char isbn[MAX_REQUEST_BUFFER_LENGTH]) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));

    if (newNode != NULL) {
        newNode->isbn = isbn;
        newNode->next = NULL;
    }

    return newNode;
}

void list_insert(ListNode** list, char isbn[MAX_REQUEST_BUFFER_LENGTH]) {
    ListNode* newNode = build_list_node(isbn);

    if (newNode != NULL) {
        newNode->next = *list;
        *list = newNode;
    }
}

void print_list(ListNode* list) {
    if (list != NULL) {
        printf("%s ", list->isbn);
        print_list(list->next);
    }
}
