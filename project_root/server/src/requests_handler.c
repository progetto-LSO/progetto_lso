
#include "../include/requests_handler.h"

// invia una stringa al client, a blocchi grandi MAX_REQUEST_BUFFER_LENGTH
void send_string_segmented(int client_socket, char *string);

void send_string_segmented(int client_socket, char *string) {
    size_t message_length = 0;
    size_t total_sent = 0;

    message_length = strlen(string);

    while (total_sent < message_length) {
        size_t to_send = (message_length - total_sent) > MAX_REQUEST_BUFFER_LENGTH ? MAX_REQUEST_BUFFER_LENGTH : (message_length - total_sent);
        ssize_t sent = send(client_socket, string + total_sent, to_send, 0);
        if (sent == -1) {
            perror("send");
            break;
        }
        total_sent += sent;
    }
}

void handle_signup(int client_socket, char *username) {
    // 0: if signup succeed
    // 1: otherwise
    int signup_result;

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

void handle_signin(int client_socket, char *username) {
    // 0: if signin succeed
    // 1: otherwise
    int signin_result;

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

void handle_explore_catalog(int client_socket) {
    PGresult *query_result;
    int result = 0;

    result = get_books(&query_result);

    if (result == 1) {  // query failed, send 1 to client to say "Query Failed"
        send(client_socket, (int *)&result, sizeof(result), 0);
    } else {
        send(client_socket, (int *)&result, sizeof(result), 0);
        send_string_segmented(client_socket, PQgetvalue(query_result, 0, 0));
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
        send_string_segmented(client_socket, PQgetvalue(query_result, 0, 0));
    }
}

void handle_search_book_by_name(int client_socket) {
    PGresult *query_result;
    char book_name[MAX_REQUEST_BUFFER_LENGTH];
    int query_status = 0;
    size_t book_name_recv;

    // wait for user to send the book name
    book_name_recv = recv(client_socket, (char *)book_name, MAX_REQUEST_BUFFER_LENGTH, 0);

    if (book_name_recv == -1UL) {
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
        send_string_segmented(client_socket, PQgetvalue(query_result, 0, 0));
    }
}

void handle_search_books_by_genre(int client_socket) {
    PGresult *query_result;
    char book_genre[MAX_REQUEST_BUFFER_LENGTH];
    int query_status = 0;
    size_t book_genre_recv;

    // wait for user to send the book genre
    book_genre_recv = recv(client_socket, (char *)book_genre, MAX_REQUEST_BUFFER_LENGTH, 0);

    if (book_genre_recv == -1UL) {
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
        send_string_segmented(client_socket, PQgetvalue(query_result, 0, 0));
    }
}

void handle_loan_requests(int client_socket, char *username) {
    ListNode *list = NULL;
    char buffer[MAX_REQUEST_BUFFER_LENGTH];
    int query_status = 0;

    // ricevo gli isbn di cui fare il loan dal client
    while (recv(client_socket, (char *)buffer, MAX_REQUEST_BUFFER_LENGTH, 0) > 0) {
        if (strcmp("STOP", buffer) == 0) break;
        list_insert(&list, buffer, NULL);
    }

    query_status = create_loans(username, list);

    // send 1 to client to say "Query Failed"
    // send 0 to client to say "Query succeded"
    send(client_socket, (int *)&query_status, sizeof(query_status), 0);
}

void handle_get_loan_books(int client_socket, char *username) {
    PGresult *query_result;
    int result = 0;

    result = get_loan_books(&query_result, username);

    if (result == 1) {  // query failed, send 1 to client to say "Query Failed"
        send(client_socket, (int *)&result, sizeof(result), 0);
    } else {
        send(client_socket, (int *)&result, sizeof(result), 0);
        send_string_segmented(client_socket, PQgetvalue(query_result, 0, 0));
    }
}

void handle_return_book(int client_socket) {
    int query_result = 0;
    int loan_id;

    ssize_t result = recv(client_socket, (int *)&loan_id, sizeof(loan_id), 0);
    if (result == -1) {
        perror("Error to receive message");
        send(client_socket, (int *)&result, sizeof(result), 0);
        return;
    }

    query_result = return_book(loan_id);
    send(client_socket, (int *)&query_result, sizeof(query_result), 0);
}
