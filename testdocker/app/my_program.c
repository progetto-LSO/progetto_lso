#include <libpq-fe.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *conninfo = "host=postgres port=5432 dbname=mydatabase user=myuser password=mypassword";
    PGconn *conn;
    PGresult *res;

    conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s", PQerrorMessage(conn));
        PQfinish(conn);
        exit(1);
    }

    res = PQexec(conn, "SELECT current_schema();");

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "SELECT failed: %s", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        exit(1);
    }

    printf("PostgreSQL version: %s\n", PQgetvalue(res, 0, 0));

    PQclear(res);
    PQfinish(conn);

    return 0;
}
