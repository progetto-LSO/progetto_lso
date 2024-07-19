#include <pthread.h>
#include <unistd.h>

extern pthread_mutex_t sem; 

void initialize_mutex(pthread_mutex_t sem); 

void client_request_initializer(pthread_t *tid, int *client_socket);

void *client_request_handler(void *socket);