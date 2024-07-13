#include "../include/database.h"

#include <stdio.h>
#include <stdlib.h>

static PGconn *connection = NULL;

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

void execute_query(const char *query) {
    PGresult *res = PQexec(connection, query);
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Failed to execute Query: %s \n", PQerrorMessage(connection));
        PQclear(res);
        exit(EXIT_FAILURE);
    }

    // Ottieni il numero di campi (colonne) nel risultato
    int nFields = PQnfields(res);
    int i, j;

    // Stampa i nomi delle colonne
    for (i = 0; i < nFields; i++) {
        printf("%-15s", PQfname(res, i));
    }
    printf("\n");

    // Stampa le righe del risultato
    for (i = 0; i < PQntuples(res); i++) {
        for (j = 0; j < nFields; j++) {
            printf("%-15s", PQgetvalue(res, i, j));
        }
        printf("\n");
    }
    PQclear(res);
}

void exit_nicely(PGconn *conn) {
    PQfinish(conn);
    exit(1);
}

int main(int argc, char const *argv[]) {
    // connect_database("dbname=postgres user=postgres password=admin host=localhost port=5432");
    PGconn *conn;
    PGresult *res;
    int nFields;
    int i, j;

    // Connessione al database
    conn = PQconnectdb("dbname=postgres user=postgres password=admin host=localhost port=5432");

    // Controlla se la connessione è andata a buon fine
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s", PQerrorMessage(conn));
        exit_nicely(conn);
    }

    // Esegui una query SELECT
    res = PQexec(conn, "SELECT * FROM public.user");

    // Controlla se la query è andata a buon fine
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "SELECT failed: %s", PQerrorMessage(conn));
        PQclear(res);
        exit_nicely(conn);
    }

    // Ottieni il numero di campi (colonne) nel risultato
    nFields = PQnfields(res);

    // Stampa i nomi delle colonne
    for (i = 0; i < nFields; i++) {
        printf("%-15s", PQfname(res, i));
    }
    printf("\n");

    // Stampa le righe del risultato
    for (i = 0; i < PQntuples(res); i++) {
        for (j = 0; j < nFields; j++) {
            printf("%-15s", PQgetvalue(res, i, j));
        }
        printf("\n");
    }

    // Libera il risultato
    PQclear(res);

    // Chiudi la connessione
    PQfinish(conn);

    return 0;
}
