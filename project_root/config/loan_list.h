#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "request_config.h"

typedef struct LoanListNode {
    int id;
    char isbn[MAX_REQUEST_BUFFER_LENGTH];
    char title[MAX_REQUEST_BUFFER_LENGTH];
    char loan_end[MAX_REQUEST_BUFFER_LENGTH];

    struct LoanListNode* next;
} LoanListNode;

LoanListNode* build_loan_list_node(int id, char isbn[MAX_REQUEST_BUFFER_LENGTH], char title[MAX_REQUEST_BUFFER_LENGTH], char loan_end[MAX_REQUEST_BUFFER_LENGTH]);
void loan_list_insert(LoanListNode** list, int id, char isbn[MAX_REQUEST_BUFFER_LENGTH], char title[MAX_REQUEST_BUFFER_LENGTH], char loan_end[MAX_REQUEST_BUFFER_LENGTH]);
void print_loan_list(LoanListNode* list);
void free_loan_list(LoanListNode** list);
void remove_ith_loan_element(LoanListNode** list, int i);
LoanListNode* get_ith_loan_element(LoanListNode* list, int i);