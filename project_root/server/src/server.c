#include "../include/server.h"

// crea un thread dedicato per gestire un singolo client che ha effettuato la connessione al server
void client_request_initializer(pthread_t *tid, int *client_socket) {
    if ((pthread_create(tid, NULL, client_request_handler, (void *)client_socket)) != 0)
        perror("Create new Thread Failed"), exit(EXIT_FAILURE);
}
// gestione della richiesta del client da parte del thread creato, quando il client ha concluso la sua esecuzione il socket viene chiuso
void *client_request_handler(void *socket) {
    // casting per recuperare il valore del socket descriptor (la funzione da passare a pthread_create vuole per forza un agormento di tipo puntatore a void)
    int client_socket = *(int *)socket;

    // esecuzione delle richieste del client
    printf("Thread request handler\n");
    printf("socket: %d\n", client_socket);
    while (1) {
        sleep(2);
    }

    printf("Closing Connection...\n");
    close(client_socket);
}