#include <pthread.h>
#include <unistd.h>

void client_request_initializer(pthread_t *tid, int *client_socket);

void *client_request_handler(void *socket);