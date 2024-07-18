#include "list.h"

ListNode* build_list_node(char isbn[MAX_REQUEST_BUFFER_LENGTH], char title[MAX_REQUEST_BUFFER_LENGTH]) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));

    if (newNode != NULL) {
        strcpy(newNode->isbn, isbn);
        strcpy(newNode->title, (title = (title != NULL ? title : "")));

        newNode->next = NULL;
    }

    return newNode;
}

void list_insert(ListNode** list, char isbn[MAX_REQUEST_BUFFER_LENGTH], char title[MAX_REQUEST_BUFFER_LENGTH]) {
    ListNode* newNode = build_list_node(isbn, title);

    if (newNode != NULL) {
        newNode->next = *list;
        *list = newNode;
    }
}

void print_list_aux(ListNode* list, int index) {
    if (list != NULL) {
        printf("%3d)\t", index);
        printf("ISBN: %s\n", list->isbn);
        printf("   \tTitolo: %s", list->title);
        printf("\n\n");
        print_list_aux(list->next, index + 1);
    }
}
void print_list(ListNode* list) { print_list_aux(list, 1); }

void free_list(ListNode** list) {
    ListNode* temp;
    while (*list != NULL) {
        temp = *list;
        *list = (*list)->next;
        free(temp);
    }
}

void insert_book(ListNode** carrello, ListNode* catalogo, int indice_libro_scelto) {
    int index = 1;

    while (catalogo != NULL && index != indice_libro_scelto) {
        index++;
        catalogo = catalogo->next;
    }

    if (catalogo == NULL) {
        printf("Numero libro non valido\n");
    } else {
        list_insert(carrello, catalogo->isbn, catalogo->title);
    }
}

void remove_ith_element(ListNode** list, int i) {
    if (list == NULL || *list == NULL || i < 0) {
        return;
    }

    ListNode* temp = *list;

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
    ListNode* next = temp->next->next;

    free(temp->next);  // Free the memory of the node to be deleted

    temp->next = next;  // Unlink the deleted node from the list
}
