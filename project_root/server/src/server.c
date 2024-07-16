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

    char buffer[512];

    while (1) {
        ssize_t result = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        if (result == -1) {
            perror("Error to receive message");
            break;
        } else if (result == 0) {
            // Il client ha chiuso la connessione
            printf("Client disconnected.\n");
            break;
        }

        // Null-terminate the received data
        buffer[result] = '\0';

        printf("result: %ld\n", result);
        printf("Messaggio: %s\n", buffer);

        // Se vuoi rispondere al client, puoi usare send qui
        // send(client_socket, response, strlen(response), 0);
    }

    printf("Closing Connection...\n");
    close(client_socket);
    return NULL;
}