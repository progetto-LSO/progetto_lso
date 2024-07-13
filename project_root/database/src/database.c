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
        fprintf(stderr, "Query Failed: %s", PQerrorMessage(connection));
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
            "SELECT * from public.\"user\" WHERE username = '%s' AND passw = '%s' ",
            username, password);

    printf("Executing Query: %s \n", query_string);

    // esecuzione query
    res = PQexec(connection, query_string);

    // la query restituisce tuple, se è andata a buon fine il suo result status dovrebbe essere: PGRES_TUPLES_OK
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Query Failed: %s", PQerrorMessage(connection));
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
}

// salva in res tutti i libri per cui la disponibilità non supera il numero di loan effettuati per quel libro
int search_avaiable_books(PGresult **res) {
}

// salva in res tutti i libri di un certo genere
int search_books_by_genre(PGresult **res, const char *book_genre) {
}

// salva in res il libro con il nome specificato
int search_book_by_name(PGresult **res, const char *book_name) {
}

// crea un prestito per un libro
int create_loan(const char *ISBN, const char *username) {
}

// aggiorna lo stato del prestito quando il libro viene restituito
int update_loan(const char *ISBN, const char *username) {
}

/* int main(int argc, char const *argv[]) {
    PGresult *res;
    int i, j;

    // Connessione al database
    connection = PQconnectdb("dbname=library user=postgres password=admin host=localhost port=5432");

    // Controlla se la connessione è andata a buon fine
    if (PQstatus(connection) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s", PQerrorMessage(connection));
        exit_nicely(connection);
    }

    // Esegui una query SELECT
    get_books(&res);

    // Stampa le righe del risultato
    for (i = 0; i < PQntuples(res); i++) {
        for (j = 0; j < PQnfields(res); j++) {
            printf("%-15s", PQgetvalue(res, i, j));
        }
        printf("\n");
    }
    printf("%d", PQntuples(res));

    // Libera il risultato
    PQclear(res);

    // Chiudi la connessione
    PQfinish(connection);

    return 0;
} */
