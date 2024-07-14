#include "../../database/include/database.h"
#include "../include/server.h"
#include "../include/socket.h"

#define ADDRESS "127.0.0.1"
#define PORT 8080 


int main(int argc, char const *argv[]) {
    
    int socket; 
    struct sockaddr_in server_address; 
    
    address_config(&server_address, ADDRESS, PORT);
    
    socket = open_socket();

    bind_socket(socket, &server_address);


    close(socket);
    
    return 0;
}
