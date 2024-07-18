#include "../include/server.h"
#include "../include/requests_handler.h"

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

    char username[MAX_REQUEST_BUFFER_LENGTH];

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
                handle_signup(client_socket, username);
                break;

            case SIGN_IN:
                handle_signin(client_socket, username);
                break;

            case EXPLORE_CATALOG:
                handle_explore_catalog(client_socket);
                break;

            case SEARCH_AVAILABLE_BOOKS:
                handle_search_available_books(client_socket);
                break;

            case SEARCH_BOOK_BY_NAME:
                handle_search_book_by_name(client_socket);
                break;

            case SEARCH_BOOK_BY_GENRE:
                handle_search_books_by_genre(client_socket);
                break;

            case MAKE_LOAN: 
                handle_loan_requests(client_socket, username);
                break; 

            default:
                break;
        }
    }

    printf("Closing Connection...\n");
    close(client_socket);
    return NULL;
}
