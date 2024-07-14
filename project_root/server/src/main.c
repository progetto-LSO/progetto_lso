#include "../../database/include/database.h"

int main(int argc, char const *argv[]) {
    connect_database("dbname=library user=postgres password=admin host=localhost port=5432");

    char *username = "Simone";

    int result = login(username, "mypsw");

    if(result == 0){
        printf("User %s Logged In \n", username); 
    }

    printf("Querying Books...\n");
    
    PGresult *query_result; 

    result = get_books(&query_result);

    if(result != 0){
        printf("Error from database\n"); 
    } else {
        print_query_result(query_result); 
    }

    PQclear(query_result);

    disconnect_database();

    return 0;
}
