#include <signal.h>
#include <unistd.h>

#include "../../config/address_config.h"
#include "../../database/include/database.h"
#include "../include/server.h"
#include "../include/socket.h"

int welcoming_socket;

void sig_handler(int signo) {
    if (signo == SIGINT || signo == SIGTERM) {
        printf("Exiting... closing socket.\n");
        close(welcoming_socket);  // Chiude il socket prima di uscire
        exit(0);
    }
}

int main() {
    // Imposta il gestore di segnali per SIGINT e SIGTERM
    signal(SIGINT, sig_handler);
    signal(SIGTERM, sig_handler);

    int dedicate_socket;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;

    // inizializzazione mutex per la gestione delle sezioni critiche
    initialize_mutex(sem);

    // configurazione indirizzo server
    address_config(&server_address, SERVER_ADDRESS, SERVER_PORT);
    // configurazione del socket
    welcoming_socket = open_socket();
    bind_socket(welcoming_socket, &server_address);

    // listen delle connessioni in ingresso
    if (listen(welcoming_socket, MAX_LISTEN_QUEUE) == -1)
        perror("Failed to listen"), exit(EXIT_FAILURE);

    printf("Server is listening on: %s:%d \n", SERVER_ADDRESS, SERVER_PORT);

    connect_database();

    while (1) {
        printf("Waiting for connections...\n");

        dedicate_socket = accept_request_connection(welcoming_socket, &client_address);

        if (dedicate_socket > 0) {
            pthread_t tid;
            successfull_connection_message(&client_address);

            // crea un thread per gestire il client
            client_request_initializer(&tid, &dedicate_socket);

            // non aspetta che il thread termini
            pthread_detach(tid);
        }
    }

    close(welcoming_socket);
    disconnect_database();
    return 0;
}
