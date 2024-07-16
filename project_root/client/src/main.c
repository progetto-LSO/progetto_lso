#include <signal.h>

#include "../../config/address.config.h"

#include "../include/client.h"
#include "../include/socket.h"

int client_socket;

void sig_handler(int signo) {
    if (signo == SIGINT || signo == SIGTERM) {
        printf("Exiting... closing socket.\n");
        close(client_socket);  // Chiude il socket prima di uscire
        exit(0);
    }
}

int main(int argc, char const *argv[]) {
    // Imposta il gestore di segnali per SIGINT e SIGTERM
    signal(SIGINT, sig_handler);
    signal(SIGTERM, sig_handler);

    int scelta;

    struct sockaddr_in server_address;

    // configurazione indirizzo server 
    address_config(&server_address, SERVER_ADDRESS, SERVER_PORT);

    // creazione client socket 
    client_socket = open_socket();

    // Connessione al server
    connection_to_server(); 

    login();

    while (1) {
        system("clear");

        printf("-------- MENU --------\n");
        printf("1. Esplora catalogo\n");
        printf("2. Cerca libro per nome\n");
        printf("3. Cerca libro per genere\n");
        printf("4. Richiedi prestito\n");
        printf("5. Restituisci libro\n");
        printf("6. Esci\n");
        printf("----------------------\n");
        printf("Inserisci la tua scelta: ");
        scanf("%d", &scelta);

        switch (scelta) {
            case 1:
                explore_catalog();
                break;
            case 2:
                search_book_by_name();
                break;
            case 3:
                search_book_by_genre();
                break;
            case 4:
                request_loan();
                break;
            case 5:
                return_book();
                break;
            case 6:
                close(socket_fd);
                exit(EXIT_SUCCESS);
                break;
            default:
                break;
        }
    }

    return 0;
}
