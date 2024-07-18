#include <libpq-fe.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../config/request_config.h"
#include "../../config/list.h"

extern PGconn *connection;

void connect_database();
void disconnect_database();

/* returns 0 if no error occurred, 1 otherwise */

int sign_up(const char *username, const char *password);
int sign_in(const char *username, const char *password);

int get_books(PGresult **res);
int search_available_books(PGresult **res);
int search_books_by_genre(PGresult **res, const char *book_genre);
int search_books_by_name(PGresult **res, const char *book_name);

int create_loans(const char *username, const ListNode *list);

int return_book(int loan_id);

void print_query_result(PGresult *res);