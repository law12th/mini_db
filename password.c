#include "password.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// char *password declares a pointer to a character, often used to point to a string or beginning of character array.
// it doesn't allocate memory for the string itself, but holds address (memory location) of existing character array,
// or can be used to create dynamic string using memory allocation

unsigned long hash_password(char *password)
{
    unsigned long hash = 5381;

    char c;

    // djb2 algorithm
    while ((c = *password++))
    {
        hash = ((password << 5) + hash) + c;
    }

    return hash;
}

bool compare_password(char *stored_password, char *given_password, char *salt)
{
    unsigned long password_hash = hash_password(strcat(given_password, salt));

    return strcmp(stored_password, password_hash) == 0;
}

// char salt[] declares and allocates memory for a character array with a specific size, which can hold the string and null terminator '\0'

void generate_salt(char salt[], int salt_length)
{
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const int charset_size = sizeof(charset) - 1; // 0 -> 62

    srand(time(NULL)); // seed random number generator with current time to ensure different salts are generated each time

    for (int i = 0; i < salt_length; i++)
    {
        salt[i] = charset[rand() % charset_size];
    }

    salt[salt_length] = '\0';
}