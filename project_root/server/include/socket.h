#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <stdio.h>
#include <unistd.h>

void address_config(struct sockaddr_in *address, const char *ip_address, int port_number);

int open_socket();

void bind_socket(int socket, struct sockaddr_in *address); 

int accept_request_connection(int socket, struct sockaddr_in *address); 

void successfull_connection_message(struct sockaddr_in *address);