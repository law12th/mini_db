#ifndef DATABASE_H
#define DATABASE_H

#include <stdio.h>

#define MAX_DATA 512
#define MAX_ROWS 100

typedef struct
{
    int set;
    int id;
    char first_name[MAX_DATA];
    char last_name[MAX_DATA];
    char email[MAX_DATA];
    char password_hash[MAX_DATA];
    char salt[MAX_DATA];
} User;

typedef struct
{
    User rows[MAX_ROWS];
} Database;

typedef struct
{
    FILE *filename;
    Database *db;
} Connection;

void create_database(Connection *conn);

void load_database(Connection *conn);

Connection *open_database(const char *filename, char mode);

void write_database(Connection *conn);

void close_database(Connection *conn);

void add_user(
    Connection *conn,
    int id,
    const char *first_name,
    const char *last_name,
    const char *email,
    const char *password_hash,
    const char *salt);

#endif