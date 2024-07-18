#include <signal.h>
#include <unistd.h>

#include "../../config/address_config.h"
#include "../include/client.h"
#include "../include/socket.h"

static int client_socket;

void sig_handler(int signo) {
    if (signo == SIGINT || signo == SIGTERM || signo == SIGKILL) {
        printf("Exiting... closing socket.\n");
        close(client_socket);  // Chiude il socket prima di uscire
        exit(0);
    }
}

int main() {
    // Imposta il gestore di segnali per SIGINT e SIGTERM
    signal(SIGINT, sig_handler);
    signal(SIGTERM, sig_handler);
    signal(SIGKILL, sig_handler);

    int scelta;

    struct sockaddr_in server_address;

    // configurazione indirizzo server
    address_config(&server_address, SERVER_ADDRESS, SERVER_PORT);

    // creazione client socket
    client_socket = open_socket();

    // Connessione al server
    connection_to_server(client_socket, &server_address);

    show_auth_menu(client_socket);

    while (1) {
        system("clear");

        printf("---------- MENU ----------\n");
        printf("1. Esplora catalogo\n");
        printf("2. Cerca libro per nome\n");
        printf("3. Cerca libro per genere\n");
        printf("4. Richiedi prestito\n");
        printf("5. Visualizza prestiti\n");
        printf("6. Esci\n\n");
        printf("Inserisci la tua scelta: ");
        scanf("%d", &scelta);

        switch (scelta) {
            case 1:
                explore_catalog(client_socket);
                press_key_to_continue();
                break;
            case 2:
                search_book_by_name(client_socket);
                press_key_to_continue();
                break;
            case 3:
                search_book_by_genre(client_socket);
                press_key_to_continue();
                break;
            case 4:
                view_loans();
                press_key_to_continue();
                break;
            case 5:
                return_book();
                press_key_to_continue();
                break;
            case 6:
                close(client_socket);
                exit(EXIT_SUCCESS);
                break;
            default:
                break;
        }
    }

    return 0;
}
