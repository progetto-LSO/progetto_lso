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

int get_books(PGresult **res) {
    (*res) = PQexec(connection, "SELECT * FROM public.\"book\"");

    // Controlla se la query è andata a buon fine
    if (PQresultStatus(*res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "SELECT failed: %s", PQerrorMessage(connection));
        PQclear(*res);
        return 1;
    }

    return 0;
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
