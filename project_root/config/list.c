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