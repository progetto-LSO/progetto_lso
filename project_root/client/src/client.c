#include "../include/client.h"

char username[STRING_BUFFER_LENGTH];

// riceve una stringa e se questa è più grande del buffer
// rimane in ascolto finché non termina di leggere
//
// Restituisce la stringa completa
char *recv_and_compose_segmented_string(int client_socket) {
    char buffer[MAX_REQUEST_BUFFER_LENGTH];
    char *message = NULL;
    size_t total_received = 0;
    ssize_t received;

    while ((received = recv(client_socket, buffer, MAX_REQUEST_BUFFER_LENGTH, 0)) > 0) {
        char *temp = realloc(message, total_received + received + 1);  // +1 for the null terminator
        if (temp == NULL) {
            perror("realloc");
            free(message);
            return NULL;
        }
        message = temp;

        memcpy(message + total_received, buffer, received);
        total_received += received;

        if (received < MAX_REQUEST_BUFFER_LENGTH) break;
    }

    if (received == -1) {
        perror("recv");
        free(message);
        return NULL;
    }
    message[total_received] = '\0';  // Null terminate the final string

    return message;
}

void press_key_to_continue() {
    printf("Premi invio per continuare...");
    getchar();  // Per assorbire il newline rimasto nel buffer
    getchar();  // Per aspettare l'invio da parte dell'utente
}

int sign_in(int client_socket) {
    int signin_result;

    int request_type = SIGN_IN;

    char _username[MAX_REQUEST_BUFFER_LENGTH];
    char password[MAX_REQUEST_BUFFER_LENGTH];

    printf("-------- SIGN IN --------\n");
    printf("Username: ");
    scanf("%s", _username);
    printf("Password: ");
    scanf("%s", password);

    if ((send(client_socket, (int *)&request_type, sizeof(request_type), 0)) == -1) {
        perror("Error to send message");
        return 1;
    }

    if ((send(client_socket, (char *)_username, MAX_REQUEST_BUFFER_LENGTH, 0)) == -1) {
        perror("Error to send message");
        return 1;
    }
    if ((send(client_socket, (char *)password, MAX_REQUEST_BUFFER_LENGTH, 0)) == -1) {
        perror("Error to send message");
        return 1;
    }

    printf("Aspettando la risposta del server...\n");

    ssize_t result = recv(client_socket, (int *)&signin_result, sizeof(signin_result), 0);
    if (result == -1) {
        perror("Error to receive message");
        return 1;
    }

    if (signin_result == 0) {
        strcpy(username, _username);
        return 0;
    } else {
        return 1;
    }
}

int sign_up(int client_socket) {
    int signup_result;

    int request_type = SIGN_UP;

    char _username[MAX_REQUEST_BUFFER_LENGTH];
    char password[MAX_REQUEST_BUFFER_LENGTH];

    printf("-------- SIGN UP --------\n");
    printf("Username: ");
    scanf("%s", _username);
    printf("Password: ");
    scanf("%s", password);

    if ((send(client_socket, (int *)&request_type, sizeof(request_type), 0)) == -1) {
        perror("Error to send message");
        return 1;
    }

    if ((send(client_socket, (char *)_username, MAX_REQUEST_BUFFER_LENGTH, 0)) == -1) {
        perror("Error to send message");
        return 1;
    }

    if ((send(client_socket, (char *)password, MAX_REQUEST_BUFFER_LENGTH, 0)) == -1) {
        perror("Error to send message");
        return 1;
    }

    printf("Aspettando la risposta del server...\n");

    ssize_t result = recv(client_socket, (int *)&signup_result, sizeof(signup_result), 0);
    if (result == -1) {
        perror("Error to receive message");
        return 1;
    }

    if (signup_result == 0) {
        strcpy(username, _username);
        return 0;
    } else {
        return 1;
    }
}

void show_auth_menu(int client_socket) {
    int scelta;
    int result;

    while (1) {
        // system("clear");
        printf("----- AUTH MENU -----\n");
        printf("1. Registrati\n");
        printf("2. Accedi\n");
        printf("3. Esci\n\n");
        printf("Scegli un'opzione: ");
        scanf("%d", &scelta);

        system("clear");
        switch (scelta) {
            case 1:
                result = sign_up(client_socket);

                if (result == 0) {
                    printf("Registrazione effettuata con successo\n\n");
                    press_key_to_continue();
                    return;
                } else {
                    printf("\nErrore durante la registrazione, riprova\n\n\n");
                    press_key_to_continue();
                }

                break;
            case 2:
                result = sign_in(client_socket);

                if (result == 0) {
                    printf("Accesso effettuato con successo\n\n");
                    press_key_to_continue();
                    return;
                } else {
                    printf("\nErrore durante l'accesso, riprova\n\n\n");
                    press_key_to_continue();
                }

                break;
            case 3:
                close(client_socket);
                exit(EXIT_SUCCESS);
                break;
            default:
                break;
        }
    }
}

void explore_catalog(int client_socket) {
    int request_type = EXPLORE_CATALOG;
    int db_result;

    if ((send(client_socket, (int *)&request_type, sizeof(request_type), 0)) == -1) {
        perror("Error to send message");
        return;
    }

    // controlla se la query è stata eseguita correttamente
    ssize_t result = recv(client_socket, (int *)&db_result, sizeof(db_result), 0);
    if (result == -1) {
        perror("Error to receive message");
        return;
    }

    // query fallita
    if (db_result == 1) {
        printf("Errore nell'esecuzione della query\n");
        return;
    }

    char *message = recv_and_compose_segmented_string(client_socket);

    // parse the JSON data
    cJSON *json = cJSON_Parse(message);
    if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            printf("Error: %s\n", error_ptr);
        }
        cJSON_Delete(json);
        return;
    }

    // Iterazione attraverso gli oggetti nell'array json
    // il quale stampa la lista dei libri
    cJSON *item;
    cJSON_ArrayForEach(item, json) {
        cJSON *isbn = cJSON_GetObjectItemCaseSensitive(item, "isbn");
        cJSON *title = cJSON_GetObjectItemCaseSensitive(item, "title");
        cJSON *authors = cJSON_GetObjectItemCaseSensitive(item, "authors");
        cJSON *genre = cJSON_GetObjectItemCaseSensitive(item, "genre");
        cJSON *quantity = cJSON_GetObjectItemCaseSensitive(item, "quantity");
        cJSON *available_quantity = cJSON_GetObjectItemCaseSensitive(item, "available_quantity");

        if (cJSON_IsString(isbn) && cJSON_IsString(title) && cJSON_IsArray(authors) &&
            cJSON_IsArray(genre) && cJSON_IsNumber(quantity) && cJSON_IsNumber(available_quantity)) {
            // Stampa delle informazioni
            printf("ISBN: %s\n", isbn->valuestring);
            printf("Titolo: %s\n", title->valuestring);

            // Stampa degli autori
            printf("Autori: ");
            cJSON *author;
            cJSON_ArrayForEach(author, authors) {
                printf("%s", author->valuestring);
                if (author->next != NULL) {
                    printf(", ");
                }
            }
            printf("\n");

            // Stampa del genere
            printf("Genere: ");
            cJSON *genre_item;
            cJSON_ArrayForEach(genre_item, genre) {
                printf("%s", genre_item->valuestring);
                if (genre_item->next != NULL) {
                    printf(", ");
                }
            }
            printf("\n");

            // Stampa della quantità disponibile e totale
            printf("Quantità totale: %d\n", quantity->valueint);
            printf("Quantità disponibile: %d\n", available_quantity->valueint);

            printf("\n");
        }
    }

    // delete the JSON object
    cJSON_Delete(json);

    free(message);
}

void search_book_by_name() {
}

void search_book_by_genre() {
}

void view_loans() {
}

void return_book() {
}