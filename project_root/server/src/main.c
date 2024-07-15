#include "../../database/include/database.h"
#include "../include/server.h"
#include "../include/socket.h"

#define ADDRESS "127.0.0.1"
#define PORT 8080 
#define MAX_LISTEN_QUEUE 10 

int main(int argc, char const *argv[]) {
    
    int welcoming_socket; 
    int dedicate_socket; 
    struct sockaddr_in server_address; 
    struct sockaddr_in client_address; 
    
    // configurazione del socket
    address_config(&server_address, ADDRESS, PORT);
    welcoming_socket = open_socket();
    bind_socket(welcoming_socket, &server_address);

    // listen delle connessioni in ingresso 
    if(listen(welcoming_socket, MAX_LISTEN_QUEUE) == -1)
        perror("Failed to listen"), exit(EXIT_FAILURE);
    
    printf("Server is listening on Port:%d \n", PORT); 

    while(1){
        printf("Waiting for connections...\n"); 
        
        dedicate_socket = accept_request_connection(welcoming_socket, &client_address);

        if(dedicate_socket > 0){
            pthread_t tid; 
            successfull_connection_message(&client_address);

            // crea un thread per gestire il client
            client_request_initializer(&tid, &dedicate_socket);

            // non aspetta che il thread termini 
            pthread_detach(tid); 

        } 

    }


    close(welcoming_socket);

    return 0;
}
