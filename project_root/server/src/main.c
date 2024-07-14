#include "../../database/include/database.h"
#include "../include/server.h"

int main(int argc, char const *argv[]) {
    
    int connection_socket, communication_socket; 
    struct sockaddr_in server_address;

    // Creazione Connection Socket 
    if((connection_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        perror("Failed to Create Socket"), exit(EXIT_FAILURE);

    // Impostazione Indirizzo
    server_address.sin_family = AF_INET; 


    // Binding del Socket

    return 0;
}
