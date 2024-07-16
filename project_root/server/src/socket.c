#include "../include/socket.h"


int open_socket() {
    
    int sock; 

    if((sock = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        perror("Failed to create Socket"), exit(EXIT_FAILURE);

    return sock; 

}

void bind_socket(int socket, struct sockaddr_in *address) {

    if(bind(socket, (struct sockaddr *)address, sizeof(*address)) < 0){
        close(socket);
        perror("Failed to Bind"), exit(EXIT_FAILURE);
    }

}

// accetta una richiesta di connessione e restituisce il nuovo socket dedicato (valore > 0), oppure -1 in caso di errore
int accept_request_connection(int socket, struct sockaddr_in *address) {

    int new_socket; 
    int addrlen = sizeof(*address);

    new_socket = accept(socket, (struct sockaddr *)&address, (socklen_t *)&addrlen); 

    return new_socket; 

}

void successfull_connection_message(struct sockaddr_in *address) {
    printf("Connection Established with %s:%d ...\n", 
    inet_ntoa(address->sin_addr), 
    ntohs(address->sin_port));
}