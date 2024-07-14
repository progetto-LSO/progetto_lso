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

#define PORT 8080 
#define BUFFER_SIZE 1024 