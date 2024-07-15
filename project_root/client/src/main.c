#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#include "../include/client.h"

#define ADDRESS "127.0.0.1"
#define PORT 8080

int socket_fd;

void sig_handler(int signo) {
    if (signo == SIGINT || signo == SIGTERM) {
        printf("Exiting... closing socket.\n");
        close(socket_fd);  // Chiude il socket prima di uscire
        exit(0);
    }
}

int main(int argc, char const *argv[]) {
    // Imposta il gestore di segnali per SIGINT e SIGTERM
    signal(SIGINT, sig_handler);
    signal(SIGTERM, sig_handler);

    int scelta;

    struct sockaddr_in server_address;

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed"), exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr(ADDRESS);

    // Connect to server
    if (connect(socket_fd, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Connection failed"), exit(EXIT_FAILURE);
    }

    login();

    while (1) {
        system("clear");

        printf("-------- MENU --------\n");
        printf("1. Esplora catalogo\n");
        printf("2. Cerca libro per nome\n");
        printf("3. Cerca libro per genere\n");
        printf("4. Richiedi prestito\n");
        printf("5. Restituisci libro\n");
        printf("6. Esci\n");
        printf("----------------------\n");
        printf("Inserisci la tua scelta: ");
        scanf("%d", &scelta);

        switch (scelta) {
            case 1:
                explore_catalog();
                break;
            case 2:
                search_book_by_name();
                break;
            case 3:
                search_book_by_genre();
                break;
            case 4:
                request_loan();
                break;
            case 5:
                return_book();
                break;
            case 6:
                close(socket_fd);
                exit(EXIT_SUCCESS);
                break;
            default:
                break;
        }
    }

    return 0;
}
