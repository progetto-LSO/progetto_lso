#include <libpq-fe.h>  // sudo apt-get install libpq-dev

typedef struct {
    char *user;
    char *password;
    char *dbname;
    char *hostaddr;
    int port;
} database_connection_info;

void connect_database(const char *conninf);
void disconnect_database();
void execute_query(const char *query);

// altre funzioni specifiche ...
