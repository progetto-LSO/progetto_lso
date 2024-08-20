#include "../include/client.h"

char username[STRING_BUFFER_LENGTH];
ListNode *carrello = NULL;

ListNode *search_book_by(int client_socket, int search_type);
void print_array_books(cJSON *json);
char *recv_and_compose_segmented_string(int client_socket);

void print_array_books(cJSON *json) {
    printf("\n\n");

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
}

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
    fflush(stdin);

    printf("Password: ");
    scanf("%s", password);
    fflush(stdin);

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

    printf("Aspettando la risposta del server...\n\n\n");

    ssize_t result = recv(client_socket, (int *)&signin_result, sizeof(signin_result), 0);
    if (result == -1) {
        perror("Error to receive message");
        return 1;
    }

    if (signin_result == 0) {
        strcpy(username, _username);

        result = recv(client_socket, (int *)&signin_result, sizeof(signin_result), 0);
        if (result == -1) {
            perror("Error to receive message");
            return 1;
        }

        if (signin_result == 0) {
            printf("Hai dei libri da restituire, vai nella sezione \"Visualizza prestiti\" per restituirli.\n");
        }

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
    fflush(stdin);

    printf("Password: ");
    scanf("%s", password);
    fflush(stdin);

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
        printf("----- AUTH MENU -----\n");
        printf("1. Registrati\n");
        printf("2. Accedi\n");
        printf("3. Esci\n\n");
        printf("Scegli un'opzione: ");

        scanf("%d", &scelta);
        fflush(stdin);

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

        system("clear");
    }
}

void explore_catalog(int client_socket) {
    search_book_by(client_socket, 2);
}

void search_book_by_name(int client_socket) {
    search_book_by(client_socket, 0);
}

void search_book_by_genre(int client_socket) {
    search_book_by(client_socket, 1);
}

// search type:
// - 0: search by name
// - 1: search by genre
// - 2: search by nothing, get all catalog
// - 3: search by nothing, get all catalog and return a list of ListNode of received books
// - default: search by name
ListNode *search_book_by(int client_socket, int search_type) {
    ListNode *books = NULL;
    int request_type;
    int db_result;
    char search_key[MAX_REQUEST_BUFFER_LENGTH];

    switch (search_type) {
        default:
        case 0:
            request_type = SEARCH_BOOK_BY_NAME;
            break;
        case 1:
            request_type = SEARCH_BOOK_BY_GENRE;
            break;
        case 2:
        case 3:
            request_type = EXPLORE_CATALOG;
            break;
    }

    switch (search_type) {
        default:
        case 0:
            printf("Inserisci il nome del libro: ");
            scanf("%s", search_key);
            fflush(stdin);
            break;
        case 1:
            printf("Inserisci il genere del libro: ");
            scanf("%s", search_key);
            fflush(stdin);
            break;
        case 2:
        case 3:
            break;
    }

    if ((send(client_socket, (int *)&request_type, sizeof(request_type), 0)) == -1) {
        perror("Error to send message");
        return NULL;
    }

    switch (search_type) {
        default:
        case 0:
        case 1:
            if ((send(client_socket, (char *)search_key, MAX_REQUEST_BUFFER_LENGTH, 0)) == -1) {
                perror("Error to send message");
                return NULL;
            }
            break;
        case 2:
        case 3:
            break;
    }

    // controlla se la query è stata eseguita correttamente
    ssize_t result = recv(client_socket, (int *)&db_result, sizeof(db_result), 0);
    if (result == -1) {
        perror("Error to receive message");
        return NULL;
    }

    // query fallita
    if (db_result == 1) {
        printf("Errore nell'esecuzione della query\n");
        return NULL;
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
        return NULL;
    }

    if (search_type == 3) {
        cJSON *item;
        cJSON_ArrayForEach(item, json) {
            cJSON *isbn = cJSON_GetObjectItemCaseSensitive(item, "isbn");
            cJSON *title = cJSON_GetObjectItemCaseSensitive(item, "title");

            if (cJSON_IsString(isbn) && cJSON_IsString(title)) {
                list_insert(&books, isbn->valuestring, title->valuestring);
            }
        }
    } else {
        print_array_books(json);
        printf("Libri trovati: %d\n", cJSON_GetArraySize(json));
    }

    // delete the JSON object
    cJSON_Delete(json);

    free(message);

    return books;
}

void loan_request(int client_socket) {
    ListNode *catalogo = search_book_by(client_socket, 3);

    int scelta;
    int indice_libro_scelto;

    while (1) {
        system("clear");

        if (catalogo == NULL) {
            printf("Errore nella visualizzazione del catalogo\n");
            press_key_to_continue();
            return;
        }

        printf("----- CARRELLO -----\n");
        if (carrello == NULL) {
            printf("Vuoto\n");
        } else {
            print_list(carrello);
        }
        printf("\n\n");

        printf("----- RICHIEDI PRESTITO -----\n");
        printf("1. Aggiungi al carrello\n");
        printf("2. Svuota carrello\n");
        printf("3. Checkout\n");
        printf("4. Torna indietro\n\n");
        printf("Scegli un'opzione: ");
        scanf("%d", &scelta);
        fflush(stdin);

        system("clear");

        switch (scelta) {
            case 1:
                print_list(catalogo);
                printf("Inserisci il numero del libro: \n");
                scanf("%d", &indice_libro_scelto);
                fflush(stdin);
                insert_book(&carrello, catalogo, indice_libro_scelto);
                press_key_to_continue();
                break;
            case 2:
                free_list(&carrello);
                break;
            case 3:
                int request_type = MAKE_LOAN;
                if (carrello == NULL) {
                    printf("Il carrello e' vuoto\n");
                } else if ((send(client_socket, (int *)&request_type, sizeof(request_type), 0)) == -1) {
                    perror("Error to start checkout");
                } else {
                    ListNode *tmp = carrello;
                    char stop_message[MAX_REQUEST_BUFFER_LENGTH] = "STOP";

                    while (tmp != NULL) {
                        if ((send(client_socket, (char *)&(tmp->isbn), MAX_REQUEST_BUFFER_LENGTH, 0)) == -1)
                            perror("Error to send book");

                        tmp = tmp->next;
                    }

                    // send stop message
                    if ((send(client_socket, (char *)&stop_message, MAX_REQUEST_BUFFER_LENGTH, 0)) == -1) {
                        perror("Error to send stop message");
                    }

                    int query_result;
                    ssize_t result = recv(client_socket, (int *)&query_result, sizeof(query_result), 0);
                    if (result == -1) {
                        perror("Error to receive message");
                    } else if (query_result == 1) {  // query fallita
                        printf("Checkout fallito\n");
                    } else {
                        printf("Prestito effettuato!\n");
                        free_list(&carrello);
                    }
                }
                press_key_to_continue();
                break;
            case 4:
                return;
            default:
                break;
        }
    }
}

void view_loans(int client_socket) {
    int request_type = GET_LOAN_BOOKS;

    int scelta;
    int indice_libro_scelto;
    int db_result;

    LoanListNode *loan_books = NULL;

    if ((send(client_socket, (int *)&request_type, sizeof(request_type), 0)) == -1) {
        perror("Error to send request type message");
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

    cJSON *item;
    cJSON_ArrayForEach(item, json) {
        cJSON *id = cJSON_GetObjectItemCaseSensitive(item, "id");
        cJSON *isbn = cJSON_GetObjectItemCaseSensitive(item, "isbn");
        cJSON *title = cJSON_GetObjectItemCaseSensitive(item, "title");
        cJSON *loan_end = cJSON_GetObjectItemCaseSensitive(item, "loan_end");

        if (cJSON_IsNumber(id) && cJSON_IsString(isbn) && cJSON_IsString(title) && cJSON_IsString(loan_end)) {
            loan_list_insert(&loan_books, id->valueint, isbn->valuestring, title->valuestring, loan_end->valuestring);
        }
    }

    while (1) {
        system("clear");

        printf("----- LIBRI IN PRESTITO -----\n");
        if (loan_books == NULL) {
            printf("Nessun libro in prestito\n\n");
            press_key_to_continue();
            return;
        } else {
            print_loan_list(loan_books);
        }
        printf("\n\n");

        printf("-----------------------------\n");
        printf("1. Restituisci libro\n");
        printf("2. Torna indietro\n\n");
        printf("Scegli un'opzione: ");
        scanf("%d", &scelta);
        fflush(stdin);

        switch (scelta) {
            case 1:
                printf("Inserisci il numero del libro: \n");
                scanf("%d", &indice_libro_scelto);
                fflush(stdin);

                LoanListNode *loan = get_ith_loan_element(loan_books, indice_libro_scelto - 1);

                if (loan == NULL) {
                    printf("Numero libro non valido\n");
                    press_key_to_continue();
                    break;
                }

                request_type = RETURN_BOOK;
                if ((send(client_socket, (int *)&request_type, sizeof(request_type), 0)) == -1) {
                    perror("Error to send request type message");
                    break;
                }

                if ((send(client_socket, (int *)&(loan->id), sizeof(loan->id), 0)) == -1) {
                    perror("Error to send message");
                    break;
                }

                // controlla se la query è stata eseguita correttamente
                ssize_t result = recv(client_socket, (int *)&db_result, sizeof(db_result), 0);
                if (result == -1) {
                    perror("Error to receive message");
                    break;
                }

                // query fallita
                if (db_result == 1) {
                    printf("Errore nell'esecuzione della query\n");
                    break;
                }

                remove_ith_loan_element(&loan_books, indice_libro_scelto - 1);
                break;
            case 2:
                free_loan_list(&loan_books);
                return;
            default:
                break;
        }
    }
}