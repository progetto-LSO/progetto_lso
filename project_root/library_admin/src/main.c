#include <signal.h>
#include <unistd.h>

#include "../../config/address_config.h"
#include "../include/socket.h"

static int library_admin_socket;

void sig_handler(int signo)
{
    if (signo == SIGINT || signo == SIGTERM || signo == SIGKILL)
    {
        printf("Exiting... closing socket.\n");
        close(library_admin_socket); // Chiude il socket prima di uscire
        exit(0);
    }
}

int main(int argc, char const *argv[])
{
    // Imposta il gestore di segnali per SIGINT e SIGTERM
    signal(SIGINT, sig_handler);
    signal(SIGTERM, sig_handler);
    signal(SIGKILL, sig_handler);

    struct sockaddr_in server_address;

    int scelta;

    // configurazione indirizzo server
    address_config(&server_address, SERVER_ADDRESS, SERVER_PORT);

    // creazione client socket
    library_admin_socket = open_socket();

    // Connessione al server
    connection_to_server(library_admin_socket, &server_address);

    while (1)
    {
        system("clear");

        printf("---------- MENU ----------\n");
        printf("1. Modifica durata prestito\n");
        printf("2. Visualizza utenti con prestiti scaduti\n");
        printf("3. Esci\n\n");
        printf("Inserisci la tua scelta: ");
        scanf("%d", &scelta);

        switch (scelta)
        {
        case 1:

            break;
        case 2:

            break;
        case 3:
            close(library_admin_socket);
            exit(EXIT_SUCCESS);
            break;
        default:
            break;
        }
    }

    return 0;
}
