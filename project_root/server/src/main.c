#include "../../database/include/database.h"

int main(int argc, char const *argv[]) {
    connect_database("dbname=library user=postgres password=admin host=localhost port=5432");

    int result = create_loan("2024-7-20", "978-1-5011-2637-0", "Simone");
    printf("res: %d\n", result);

    disconnect_database();

    return 0;
}
