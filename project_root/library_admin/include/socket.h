#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <stdio.h>
#include <unistd.h>

int open_socket();

void connection_to_server(int library_admin_socket, struct sockaddr_in *server_address);

void bind_socket(int socket, struct sockaddr_in *address); 