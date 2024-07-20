#ifndef CONFIG_H
#define CONFIG_H

#define SERVER_ADDRESS "127.0.0.3"
#define SERVER_PORT 8080
#define MAX_LISTEN_QUEUE 5

#endif

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

void address_config(struct sockaddr_in *address, const char *ip_address, int port_number);
