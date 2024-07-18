#include <cjson/cJSON.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "../../config/list.h"
#include "../../config/loan_list.h"
#include "../../config/request_config.h"

#define STRING_BUFFER_LENGTH 256

extern char username[STRING_BUFFER_LENGTH];
extern ListNode *carrello;

// 0: sign in success
// 1: sign in failed
int sign_in(int client_socket);

// 0: sign up success
// 1: sign up failed
int sign_up(int client_socket);

void show_auth_menu(int client_socket);

void explore_catalog(int client_socket);

void search_book_by_name(int client_socket);

void search_book_by_genre(int client_socket);

void loan_request(int client_socket);

void view_loans(int client_socket);

void press_key_to_continue();

/* int sign_up(const char *username, const char *password);
int login(const char *username, const char *password);

int get_books(PGresult **res);
int search_available_books(PGresult **res);
int search_books_by_genre(PGresult **res, const char *book_genre);
int search_books_by_name(PGresult **res, const char *book_name);


int create_loan(const char *loan_end, const char *ISBN, const char *username);


int return_book(int loan_id);

void print_query_result(PGresult *res);  */