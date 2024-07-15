#include <stdio.h>
#include <stdlib.h>

#define STRING_BUFFER_LENGTH 256

extern char username[STRING_BUFFER_LENGTH];

void login();

void explore_catalog();

void search_book_by_name();

void search_book_by_genre();

void request_loan();

void return_book();

/* int sign_up(const char *username, const char *password);
int login(const char *username, const char *password);

int get_books(PGresult **res);
int search_available_books(PGresult **res);
int search_books_by_genre(PGresult **res, const char *book_genre);
int search_books_by_name(PGresult **res, const char *book_name);


int create_loan(const char *loan_end, const char *ISBN, const char *username);


int return_book(int loan_id);

void print_query_result(PGresult *res);  */