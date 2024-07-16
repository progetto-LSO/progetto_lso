#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "../../config/request_config.h"
#include "../../database/include/database.h"

void client_request_initializer(pthread_t *tid, int *client_socket);

void *client_request_handler(void *socket);