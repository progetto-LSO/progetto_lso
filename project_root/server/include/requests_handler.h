#include <string.h>
#include <sys/socket.h>

#include "../../config/list.h"
#include "../../database/include/database.h"

void handle_signup(int client_socket, char *username);
void handle_signin(int client_socket, char *username);
void handle_explore_catalog(int client_socket);
void handle_search_available_books(int client_socket);
void handle_search_book_by_name(int client_socket);
void handle_search_books_by_genre(int client_socket);
void handle_loan_requests(int client_socket, char *username);
void handle_get_loan_books(int client_socket, char *username);
void handle_return_book(int client_socket);
void handle_change_loan_duration(int client_socket);
void handle_get_exiped_loan(int client_socket);
void handle_get_current_loan_duration(int client_socket);

