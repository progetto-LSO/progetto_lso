#include <libpq-fe.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../config/database_config.h"
#include "../../config/list.h"
#include "../../config/request_config.h"

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
int get_loan_books(PGresult **res, const char *username);

int create_loans(const char *username, ListNode *list);

int return_book(int loan_id);

void print_query_result(PGresult *res);

int check_loan_expired(PGresult **res, const char *username);

int change_loan_duration(int new_duration);

int get_expired_loan(PGresult **res);

int get_current_loan_duration(PGresult **res);
