#include "../include/socket.h"


// configurazione indirizzo server 
void address_config(struct sockaddr_in *address, const char *ip_address, int port_number) {

    // Imposta la famiglia dell'indirizzo IP ad IPv4 
    address->sin_family = AF_INET; 
    // htons -> host to network short = conversione numero di porta dal formato host byte order a network byte order
    address->sin_port = htons(port_number);

    // configurazione dell'indirizzo IP 
    if(ip_address == NULL){
        // se nessun indirizzo IP specifico è stato passato alla funzione, 
        // usiamo INADDR_ANY che consente al server di accettare connessioni su tutte le interfacce di rete disponibili
        address->sin_addr.s_addr = INADDR_ANY; 
    } else {
        // se è stato passato un indirizzo IP alla funzione, 
        // tramite inet_pton (presentation to numeric) converte l'indirizzo IP da formato testuale a formato binario
        if(inet_pton(AF_INET, ip_address, &address->sin_addr) <= 0)
            perror("Invalid Address / Adress Not Supported"), exit(EXIT_FAILURE);

    } 

}

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