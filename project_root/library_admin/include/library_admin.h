#include <cjson/cJSON.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "../../config/request_config.h"

void press_key_to_continue() ;

void change_loan_duration(int library_socket);

void get_expired_loan(int library_socket);

char *recv_and_compose_segmented_string(int library_socket);
