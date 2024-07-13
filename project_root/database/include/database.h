#include <libpq-fe.h>  // sudo apt-get install libpq-dev
#include <stdio.h>
#include <stdlib.h>

static PGconn *connection = NULL;

typedef struct {
    char **values;
    int rows;
    int fields_number;
} query_result;

void connect_database(char *db_info);
void disconnect_database();
void execute_query(const char *query);

/* returns 0 if no error occurred, 1 otherwise */

int sign_in(const char *username, const char *password);
int login(const char *username, const char *password);

int get_books(PGresult **res);
int search_avaiable_books(PGresult **res);
int search_books_by_genre(PGresult **res, const char *book_genre);
int search_books_by_name(PGresult **res, const char *book_name);

// INSERT
int create_loan(const char *ISBN, const char *user_id);

// DELETE
int delete_loan(const char *ISBN, const char *user_id);

/*
    FUNZIONE TIPO :
        1) eseguo get_books()
        2) ottengo un db_status
        3)


*/