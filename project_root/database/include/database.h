#include <libpq-fe.h>  // sudo apt-get install libpq-dev
#include <stdio.h>
#include <stdlib.h>

static PGconn *connection = NULL;

void connect_database(char *db_info);
void disconnect_database();

/* returns 0 if no error occurred, 1 otherwise */

int sign_up(const char *username, const char *password);
int login(const char *username, const char *password);

int get_books(PGresult **res);
int search_avaiable_books(PGresult **res);
int search_books_by_genre(PGresult **res, const char *book_genre);
int search_books_by_name(PGresult **res, const char *book_name);


int create_loan(const char *ISBN, const char *username);


int update_loan(const char *ISBN, const char *username);