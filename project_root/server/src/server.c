#include "../include/server.h"

// db functions
void handle_signup(int client_socket);
void handle_signin(int client_socket);
void handle_explore_catalog(int client_socket);
void handle_search_available_books(int client_socket);
void handle_search_book_by_name(int client_socket);
void handle_search_books_by_genre(int client_socket);

// send db result to client
void getJSONResultAndSend(int client_socket, PGresult **query_result);

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

void getJSONResultAndSend(int client_socket, PGresult **query_result) {
    size_t message_length = 0;
    size_t total_sent = 0;
    char *json_result = NULL;

    json_result = PQgetvalue(*query_result, 0, 0);
    message_length = strlen(json_result);

    while (total_sent < message_length) {
        size_t to_send = (message_length - total_sent) > MAX_REQUEST_BUFFER_LENGTH ? MAX_REQUEST_BUFFER_LENGTH : (message_length - total_sent);
        ssize_t sent = send(client_socket, json_result + total_sent, to_send, 0);
        if (sent == -1) {
            perror("send");
            break;
        }
        total_sent += sent;
    }
}

void handle_explore_catalog(int client_socket) {
    PGresult *query_result;
    int result = 0;

    result = get_books(&query_result);

    if (result == 1) {  // query failed, send 1 to client to say "Query Failed"
        send(client_socket, (int *)&result, sizeof(result), 0);
    } else {
        send(client_socket, (int *)&result, sizeof(result), 0);
        getJSONResultAndSend(client_socket, &query_result);
    }
}

void handle_search_available_books(int client_socket) {
    PGresult *query_result;
    int result = 0;

    result = search_available_books(&query_result);

    if (result == 1) {  // query failed, send 1 to client to say "Query Failed"
        send(client_socket, (int *)&result, sizeof(result), 0);
    } else {
        send(client_socket, (int *)&result, sizeof(result), 0);
        getJSONResultAndSend(client_socket, &query_result);
    }
}

void handle_search_book_by_name(int client_socket) {
    PGresult *query_result;
    char book_name[MAX_REQUEST_BUFFER_LENGTH];
    int query_status = 0;
    size_t book_name_recv;

    // wait for user to send the book name
    book_name_recv = recv(client_socket, (char *)book_name, MAX_REQUEST_BUFFER_LENGTH, 0);

    if (book_name_recv == -1) {
        perror("Error to receive message");
        return;
    } else if (book_name_recv == 0) {
        // Il client ha chiuso la connessione
        printf("Client disconnected.\n");
        return;
    }

    // query database
    query_status = search_books_by_name(&query_result, book_name);

    // send query result to the client
    if (query_status == 1) {  // query failed, send 1 to client to say "Query Failed"
        send(client_socket, (int *)&query_status, sizeof(query_status), 0);
    } else {
        send(client_socket, (int *)&query_status, sizeof(query_status), 0);
        getJSONResultAndSend(client_socket, &query_result);
    }
}

void handle_search_books_by_genre(int client_socket) {
    PGresult *query_result;
    char book_genre[MAX_REQUEST_BUFFER_LENGTH];
    int query_status = 0;
    size_t book_genre_recv;

    // wait for user to send the book genre
    book_genre_recv = recv(client_socket, (char *)book_genre, MAX_REQUEST_BUFFER_LENGTH, 0);

    if (book_genre_recv == -1) {
        perror("Error to receive message");
        return;
    } else if (book_genre_recv == 0) {
        // Il client ha chiuso la connessione
        printf("Client disconnected.\n");
        return;
    }

    // query database
    query_status = search_books_by_genre(&query_result, book_genre);

    // send query result to the client
    if (query_status == 1) {  // query failed, send 1 to client to say "Query Failed"
        send(client_socket, (int *)&query_status, sizeof(query_status), 0);
    } else {
        send(client_socket, (int *)&query_status, sizeof(query_status), 0);
        getJSONResultAndSend(client_socket, &query_result);
    }
}
