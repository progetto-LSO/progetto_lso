#include "../../database/include/database.h"

int main(int argc, char const *argv[]) {
    connect_database("dbname=library user=postgres password=admin host=localhost port=5432");

    PGresult *res;

    get_books(&res);

    // Stampa le righe del risultato
    for (int i = 0; i < PQntuples(res); i++) {
        for (int j = 0; j < PQnfields(res); j++) {
            printf("%s\t", PQgetvalue(res, i, j));
        }
        printf("\n");
    }

    PQclear(res);

    disconnect_database();

    return 0;
}
