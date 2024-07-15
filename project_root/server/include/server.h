#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <sys/types.h>
 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 


void client_request_initializer(pthread_t *tid, int *client_socket); 

void *client_request_handler(void *socket);