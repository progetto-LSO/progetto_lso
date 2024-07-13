#include <libpq-fe.h>  // sudo apt-get install libpq-dev

void connect_database(char *db_info);
void disconnect_database();
void execute_query(const char *query);

// altre funzioni specifiche ...
