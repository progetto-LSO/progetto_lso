#include "../include/database.h"

void disconnect_database() {
    PQfinish(connection);
}

void connect_database(char *conninfo) {
    connection = PQconnectdb(conninfo);
    if (PQstatus(connection) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(connection));
        disconnect_database();
        exit(EXIT_FAILURE);
    }
}

// registrazione utente sul database, insert into user
int sign_up(const char *username, const char *password) {
    char query_string[256];
    PGresult *res = NULL;

    // utilizzo di sprintf per formattare la stringa ed inserirla all'interno del buffer che conterrà l'intera query
    sprintf(query_string,
            "INSERT INTO public.\"user\" (username, passw) VALUES ('%s', '%s') ",
            username, password);

    printf("Executing Query: %s \n", query_string);

    // esecuzione query
    res = PQexec(connection, query_string);

    // la query non restituisce tuple, se è andata a buon fine il suo result status dovrebbe essere: PGRES_COMMAND_OK
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Query Failed: %s \n", PQerrorMessage(connection));
        PQclear(res);
        return 1;
    } else {
        PQclear(res);
        return 0;
    }
}

// login dell'utente sul database, select from user
int login(const char *username, const char *password) {
    char query_string[256];
    PGresult *res = NULL;

    // utilizzo di sprintf per formattare la stringa ed inserirla all'interno del buffer che conterrà l'intera query
    sprintf(query_string,
            "SELECT * from public.user WHERE username = '%s' AND passw = '%s' ",
            username, password);

    printf("Executing Query: %s \n", query_string);

    // esecuzione query
    res = PQexec(connection, query_string);

    // la query restituisce tuple, se è andata a buon fine il suo result status dovrebbe essere: PGRES_TUPLES_OK
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Query Failed: %s \n", PQerrorMessage(connection));
        PQclear(res);
        return 1;
    } else if (PQntuples(res) != 1) {
        PQclear(res);
        return 1;
    } else {
        PQclear(res);
        return 0;
    }
}

// salva in res tutti i libri salvati sul dabatase, select from book
int get_books(PGresult **res) {
    char query_string[256] = "SELECT * FROM book";

    printf("Executing Query: %s \n", query_string);
    *res = PQexec(connection, query_string);

    if (PQresultStatus(*(res)) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Query Failed: %s \n", PQerrorMessage(connection));
        PQclear(*(res));
        return 1;
    }

    return 0;
}

// salva in res tutti i libri per cui la disponibilità non supera il numero di loan effettuati per quel libro
int search_avaiable_books(PGresult **res) {
    char *query_string =
        "SELECT b.*, b.quantity - COALESCE(l.borrowed_quantity, 0) AS available_quantity "
        "FROM book b "
        "LEFT JOIN ( "
        "    SELECT isbn, COUNT(*) AS borrowed_quantity "
        "    FROM loan "
        "    WHERE returned IS NULL "
        "    GROUP BY isbn "
        ") l ON b.isbn = l.isbn "
        "WHERE b.quantity > COALESCE(l.borrowed_quantity, 0)"
        ;

    printf("Executing Query: %s \n", query_string);
    *res = PQexec(connection, query_string);

    if (PQresultStatus(*(res)) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Query Failed: %s \n", PQerrorMessage(connection));
        PQclear(*(res));
        return 1;
    }

    return 0;
}

// salva in res tutti i libri di un certo genere
int search_books_by_genre(PGresult **res, const char *book_genre) {
    char query[256];

    sprintf(query,
            "SELECT * FROM book WHERE LOWER('%s') = ANY(SELECT LOWER(unnest(texts)))",
            book_genre);

    *res = PQexec(connection, query);

    if (PQresultStatus(*(res)) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Query Failed: %s \n", PQerrorMessage(connection));
        PQclear(*(res));
        return 1;
    }

    return 0;
}

// salva in res il libro con il nome specificato
int search_books_by_name(PGresult **res, const char *book_name) {
    char query_string[256]; 

    sprintf(query_string, "SELECT * FROM book WHERE title ILIKE '%%%s%%' ", book_name);

    printf("Executing Query: %s \n", query_string);

    // esecuzione query
    *res = PQexec(connection, query_string);

    if(PQresultStatus(*(res)) != PGRES_TUPLES_OK){
        fprintf(stderr, "Query Failed: %s \n", PQerrorMessage(connection));
        PQclear(*(res));
        return 1;
    } else {
        return 0; 
    }

}

// crea un prestito per un libro
int create_loan(const char *loan_end, const char *ISBN, const char *username) {
    char query_string[500];
    PGresult *res = NULL;

    // utilizzo di sprintf per formattare la stringa ed inserirla all'interno del buffer che conterrà l'intera query
    sprintf(query_string,
            "INSERT INTO loan (loan_start, loan_end, returned, username, isbn) VALUES (current_timestamp, '%s', NULL, '%s', '%s') ",
            loan_end, username, ISBN);

    printf("Executing Query: %s \n", query_string);

    // esecuzione query
    res = PQexec(connection, query_string);

    // la query non restituisce tuple, se è andata a buon fine il suo result status dovrebbe essere: PGRES_COMMAND_OK
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Query Failed: %s \n", PQerrorMessage(connection));
        PQclear(res);
        return 1;
    } else {
        PQclear(res);
        return 0;
    }
}

// aggiorna lo stato del prestito quando il libro viene restituito
int update_loan(const char *ISBN, const char *username) {
}

// dato un generico risultato di una query, ne stampa a video l'intera struttura
void print_query_result(PGresult *res) {
    for (int i = 0; i < PQntuples(res); i++) {
        for (int j = 0; j < PQnfields(res); j++) {
            printf("%s\t", PQgetvalue(res, i, j));
        }
        printf("\n");
    }
}