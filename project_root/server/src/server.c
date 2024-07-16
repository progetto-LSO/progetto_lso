#include "../include/server.h"

void handle_signup(int client_socket);
void handle_signin(int client_socket);

// crea un thread dedicato per gestire un singolo client che ha effettuato la connessione al server
void client_request_initializer(pthread_t *tid, int *client_socket) {
    if ((pthread_create(tid, NULL, client_request_handler, (void *)client_socket)) != 0)
        perror("Create new Thread Failed"), exit(EXIT_FAILURE);
}

// gestione della richiesta del client da parte del thread creato, quando il client ha concluso la sua esecuzione il socket viene chiuso
void *client_request_handler(void *socket) {
    // casting per recuperare il valore del socket descriptor (la funzione da passare a pthread_create vuole per forza un agormento di tipo puntatore a void)
    int client_socket = *(int *)socket;

    int request_type;

    while (1) {
        ssize_t result = recv(client_socket, (int *)&request_type, sizeof(request_type), 0);
        if (result == -1) {
            perror("Error to receive message");
            continue;
        } else if (result == 0) {
            // Il client ha chiuso la connessione
            printf("Client disconnected.\n");
            break;
        }

        switch (request_type) {
            case SIGN_UP:
                handle_signup(client_socket);
                break;

            case SIGN_IN:
                handle_signin(client_socket);
                break;

            default:
                break;
        }
    }

    printf("Closing Connection...\n");
    close(client_socket);
    return NULL;
}

void handle_signup(int client_socket) {
    // 0: if signup succeed
    // 1: otherwise
    int signup_result;

    char username[MAX_REQUEST_BUFFER_LENGTH];
    char password[MAX_REQUEST_BUFFER_LENGTH];

    ssize_t username_recv;
    ssize_t password_recv;

    username_recv = recv(client_socket, (char *)username, MAX_REQUEST_BUFFER_LENGTH, 0);
    password_recv = recv(client_socket, (char *)password, MAX_REQUEST_BUFFER_LENGTH, 0);

    if (username_recv == -1 || password_recv == -1) {
        perror("Error to receive message");
        return;
    } else if (username_recv == 0 || password_recv == 0) {
        // Il client ha chiuso la connessione
        printf("Client disconnected.\n");
        return;
    }

    signup_result = sign_up(username, password);

    send(client_socket, (int *)&signup_result, sizeof(signup_result), 0);
}

void handle_signin(int client_socket) {
    // 0: if signin succeed
    // 1: otherwise
    int signin_result;

    char username[MAX_REQUEST_BUFFER_LENGTH];
    char password[MAX_REQUEST_BUFFER_LENGTH];

    ssize_t username_recv;
    ssize_t password_recv;

    username_recv = recv(client_socket, (char *)username, MAX_REQUEST_BUFFER_LENGTH, 0);
    password_recv = recv(client_socket, (char *)password, MAX_REQUEST_BUFFER_LENGTH, 0);

    if (username_recv == -1 || password_recv == -1) {
        perror("Error to receive message");
        return;
    } else if (username_recv == 0 || password_recv == 0) {
        // Il client ha chiuso la connessione
        printf("Client disconnected.\n");
        return;
    }

    signin_result = sign_in(username, password);

    send(client_socket, (int *)&signin_result, sizeof(signin_result), 0);
}
