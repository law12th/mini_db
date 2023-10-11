#ifndef PASSWORD_H
#define PASSWORD_H

#include <stdbool.h>

unsigned long hash_password(char *password);

bool compare_password(char *stored_password, char *given_password, char *salt);

void generate_salt(char salt[], int salt_length);

#endif