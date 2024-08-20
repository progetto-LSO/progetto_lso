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

    // configurazione indirizzo server
    address_config(&server_address, SERVER_ADDRESS, SERVER_PORT);

    // creazione client socket
    library_admin_socket = open_socket();

    // Connessione al server
    connection_to_server(library_admin_socket, &server_address);

    return 0;
}
