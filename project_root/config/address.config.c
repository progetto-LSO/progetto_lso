#include "address.config.h"

// configurazione indirizzo 
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