#include <libpq-fe.h>  // sudo apt-get install libpq-dev

typedef struct {
    char **values; 
    int rows; 
    int fields_number; 
} query_result; 

typedef struct {
    DB_OK, 
    DB_CONNECTION_FAILED, 
    DB_QUERY_FAILED, 
    DB_NO_RESULT
} db_status; 

void connect_database(char *db_info);
void disconnect_database();
void execute_query(const char *query);

// altre funzioni specifiche ...

db_status sign_in(const char *username, const char *password); 
db_status login(const char *username, const char *password);  


// SELECT 
db_status get_books(query_result *res);
db_status search_avaiable_books(query_result *res);
db_status search_books_by_genre(query_result *res, const char *book_genre);
db_status search_books_by_name(query_result *res, const char *book_name);

// INSERT 
db_status make_loan(const char *ISBN, const char *user_id);

// DELETE 
db_status delete_loan(const char *ISBN, const char *user_id);


// svuotare la struttura che contiene il risultato della query 
void free_db_result(query_result *res); 

// stampa di messaggio personalizzato in base al valore db_status restituito
char *query_result_message(db_status query_result_status);

/* 
    FUNZIONE TIPO : 
        1) eseguo get_books() 
        2) ottengo un db_status 
        3) 


*/