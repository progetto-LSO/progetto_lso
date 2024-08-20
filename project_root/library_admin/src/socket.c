#include "../include/socket.h"

int open_socket() {
    int sock;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        perror("Failed to create Socket"), exit(EXIT_FAILURE);

    return sock;
}

void connection_to_server(int library_admin_socket, struct sockaddr_in *server_address) {
    if (connect(library_admin_socket, (struct sockaddr *)server_address, sizeof(*server_address)) == -1) {
        perror("Connection failed"), exit(EXIT_FAILURE);
    }
}

void bind_socket(int socket, struct sockaddr_in *address) {
    if (bind(socket, (struct sockaddr *)address, sizeof(*address)) < 0) {
        close(socket);
        perror("Failed to Bind"), exit(EXIT_FAILURE);
    }
}