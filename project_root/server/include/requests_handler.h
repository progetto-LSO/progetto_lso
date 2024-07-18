#include <string.h>
#include <sys/socket.h>

#include "../../config/request_config.h"
#include "../../database/include/database.h"

void handle_signup(int client_socket, char *username);
void handle_signin(int client_socket, char *username);
void handle_explore_catalog(int client_socket);
void handle_search_available_books(int client_socket);
void handle_search_book_by_name(int client_socket);
void handle_search_books_by_genre(int client_socket);