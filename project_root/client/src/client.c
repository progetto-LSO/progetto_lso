#include "../include/client.h"

char username[STRING_BUFFER_LENGTH];

void login() {
    int logged;

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

void explore_catalog() {
}

void search_book_by_name() {
}

void search_book_by_genre() {
}

void request_loan() {
}

void return_book() {
}