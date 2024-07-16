#include "../include/client.h"

void login() {
    int logged;

    char username[STRING_BUFFER_LENGTH];
    char password[STRING_BUFFER_LENGTH];

    while (1) {
        printf("-------- LOGIN --------\n");
        printf("Username: ");
        scanf("%s", username);
        printf("Password: ");
        scanf("%s", password);

        // Logica per il login ...
        logged = 1;
        if (logged) {
            return;
        } else {
            printf("\n!! Credenziali non valide, riprova\n\n\n");
        }
    }
}

void explore_catalog(int socket) {
    char *buffer = "del testo";
    ssize_t result = send(socket, (char *)buffer, strlen(buffer), 0);
    if (result == -1)
        perror("Error to send message");
}

void search_book_by_name() {
}

void search_book_by_genre() {
}

void view_loans() {
}

void return_book() {
}