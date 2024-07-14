#include "../../database/include/database.h"
#include "../include/server.h"
#include "../include/socket.h"

#define ADDRESS "127.0.0.1"
#define PORT 8080 


int main(int argc, char const *argv[]) {
    
    int socket; 
    struct sockaddr_in server_address; 
    

    address_config(&server_address, ADDRESS, PORT);
    
    // open_socket(socket);


    return 0;
}
