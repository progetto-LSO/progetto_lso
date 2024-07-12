#include <stdio.h> 
#include <stdlib.h> 

#include "database.h"

static PGconn = *connection = NULL; 

void disconnect_database(){
    PQfinish(connection); 
}

void connect_database(const char *conninfo){
    connection = PQconnectdb(conninfo); 
    if(PQstatus(conn) != CONNECTION_OK){
        print(stderr, "Connection to database failed: %s\n", PQerrorMessage(connection)); 
        disconnect_database(); 
        exit(EXIT_FAILURE); 
    }
}

void execute_query(const char *query){
    PGresult = *result = PQexec(connection, query); 
    if(PQresultStatus(result) != PGRES_COMMAND_OK){
        print(stderr, "Failed to execute Query: %s \n", PQerrorMessage(connection)); 
        PQclear(result); 
        exit(EXIT_FAILURE); 
    }
    PQclear(result); 
}

