#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 

int address_config(struct sockaddr_in *server_address, const char *ip_address, int port_number);

int open_socket(int socket); 

int close_socket(int socket); 

int bind_socket(int socket, struct sockaddr_in *server_address); 

