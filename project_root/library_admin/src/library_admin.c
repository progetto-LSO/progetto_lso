#include "library_admin.h"

void change_loan_duration(int library_socket)
{
    int request_type = GET_CURRENT_LOAN_DURATION;
    int current_loan_duration;
    int scelta;
    int new_duration;
    if ((send(library_socket, (int *)&request_type, sizeof(request_type), 0)) == -1)
    {
        perror("Error to send request type message");
        return;
    }

    if ((recv(library_socket, (int *)&current_loan_duration, sizeof(current_loan_duration), 0)) == -1)
    {
        perror("Error to send request type message");
        return;
    }

    while (1)
    {
        system("clear");
        printf("Durata prestito attuale: %d giorni\n", current_loan_duration);

        printf("---------- MENU ----------\n");
        printf("1. Cambia durata\n");
        printf("2. Torna indietro\n\n");
        printf("Inserisci la tua scelta: ");
        scanf("%d", &scelta);

        switch (scelta)
        {
        case 1:
            request_type = CHANGE_LOAN_DURATION;
            if ((send(library_socket, (int *)&request_type, sizeof(request_type), 0)) == -1)
            {
                perror("Error to send request type message");
                return;
            }

            printf("Inserisci la nuova durata del prestito ");
            scanf("%d", &new_duration);

            if ((send(library_socket, (int *)&new_duration, sizeof(new_duration), 0)) == -1)
            {
                perror("Error to send request type message");
                return;
            }
            return;
        case 2:
            return;
        default:
            break;
        }
    }
}

void get_expired_loan(int library_socket)
{
    char *message;
    int request_type = GET_EXPIRED_LOAN;
    if ((send(library_socket, (int *)&request_type, sizeof(request_type), 0)) == -1)
    {
        perror("Error to send request type message");
        return;
    }
    message = recv_and_compose_segmented_string(library_socket);

    // parse the JSON data
    cJSON *json = cJSON_Parse(message);
    if (json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            printf("Error: %s\n", error_ptr);
        }
        cJSON_Delete(json);
        return NULL;
    }

    cJSON *item;
    cJSON_ArrayForEach(item, json)
    {
        cJSON *isbn = cJSON_GetObjectItemCaseSensitive(item, "isbn");
        cJSON *username = cJSON_GetObjectItemCaseSensitive(item, "username");
        cJSON *loan_end = cJSON_GetObjectItemCaseSensitive(item, "loan_end");

        if (cJSON_IsString(isbn) && cJSON_IsString(username) && cJSON_IsString(loan_end))
        {
            printf("ISBN: %s\n", isbn->valuestring);
            printf("Username: %s\n", username->valuestring);
            printf("Fine prestito: %s\n\n\n", loan_end->valuestring);
        }
    }

    // delete the JSON object
    cJSON_Delete(json);

    free(message);
}

char *recv_and_compose_segmented_string(int library_socket)
{
    char buffer[MAX_REQUEST_BUFFER_LENGTH];
    char *message = NULL;
    size_t total_received = 0;
    ssize_t received;

    while ((received = recv(library_socket, buffer, MAX_REQUEST_BUFFER_LENGTH, 0)) > 0)
    {
        char *temp = realloc(message, total_received + received + 1); // +1 for the null terminator
        if (temp == NULL)
        {
            perror("realloc");
            free(message);
            return NULL;
        }
        message = temp;

        memcpy(message + total_received, buffer, received);
        total_received += received;

        if (received < MAX_REQUEST_BUFFER_LENGTH)
            break;
    }

    if (received == -1)
    {
        perror("recv");
        free(message);
        return NULL;
    }
    message[total_received] = '\0'; // Null terminate the final string

    return message;
}