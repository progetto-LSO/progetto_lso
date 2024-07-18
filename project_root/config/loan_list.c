#include "loan_list.h"

LoanListNode* build_loan_list_node(
    int id,
    char isbn[MAX_REQUEST_BUFFER_LENGTH],
    char title[MAX_REQUEST_BUFFER_LENGTH],
    char loan_end[MAX_REQUEST_BUFFER_LENGTH]) {
    LoanListNode* newNode = (LoanListNode*)malloc(sizeof(LoanListNode));

    if (newNode != NULL) {
        newNode->id = id;
        strcpy(newNode->isbn, isbn);
        strcpy(newNode->title, title);
        strcpy(newNode->loan_end, loan_end);

        newNode->next = NULL;
    }

    return newNode;
}

void loan_list_insert(
    LoanListNode** list,
    int id,
    char isbn[MAX_REQUEST_BUFFER_LENGTH],
    char title[MAX_REQUEST_BUFFER_LENGTH],
    char loan_end[MAX_REQUEST_BUFFER_LENGTH]) {
    LoanListNode* newNode = build_loan_list_node(id, isbn, title, loan_end);

    if (newNode != NULL) {
        newNode->next = *list;
        *list = newNode;
    }
}

void print_loan_list_aux(LoanListNode* list, int index) {
    if (list != NULL) {
        printf("%3d)\t", index);
        printf("ISBN: %s\n", list->isbn);
        printf("   \tTitolo: %s\n", list->title);
        printf("   \tData restituzione: %s", list->loan_end);
        printf("\n\n");
        print_loan_list_aux(list->next, index + 1);
    }
}
void print_loan_list(LoanListNode* list) { print_loan_list_aux(list, 1); }

void free_loan_list(LoanListNode** list) {
    LoanListNode* temp;
    while (*list != NULL) {
        temp = *list;
        *list = (*list)->next;
        free(temp);
    }
}

void remove_ith_loan_element(LoanListNode** list, int i) {
    if (list == NULL || *list == NULL || i < 0) {
        return;
    }

    LoanListNode* temp = *list;

    // If the node to be deleted is the first node
    if (i == 0) {
        *list = temp->next;  // Change head
        free(temp);          // Free old head
        return;
    }

    // Find the previous node of the node to be deleted
    for (int j = 0; temp != NULL && j < i - 1; j++) {
        temp = temp->next;
    }

    // If the position is more than the number of nodes
    if (temp == NULL || temp->next == NULL) {
        return;
    }

    // Node temp->next is the node to be deleted
    LoanListNode* next = temp->next->next;

    free(temp->next);  // Free the memory of the node to be deleted

    temp->next = next;  // Unlink the deleted node from the list
}

LoanListNode* get_ith_loan_element(LoanListNode* list, int i) {
    int count = 0;
    LoanListNode* current = list;

    while (current != NULL) {
        if (count == i) return current;

        count++;
        current = current->next;
    }

    // If the ith element doesn't exist, return NULL
    return NULL;
}
