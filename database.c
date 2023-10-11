#include "database.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define safer_free(p) safe_free((void **)&(p))

void create_database(Connection *conn)
{
    for (int i = 0; i < MAX_ROWS; i++)
    {
        User user = {.id = i, .set = 0};

        conn->db->rows[i] = user;
    }
}

void load_database(Connection *conn)
{
    /**
     * fread function is used to read binary data from a file
     * typically used for reading structured data, such as records or binary data structures, from a file
     * - conn->db (ptr) is the pointer where data will be stored
     * - sizeof(Database) (size) is size of each element to be read
     * - 1 (count) is the number of elements to read
     * - conn->filename (stream) is the pointer to FILE representing the file to read from
     * it is reading 1 element of data of size sizeof(Database) bytes long, from conn->filename and storing them in conn->db pointer.
     * it returns the number of elements successfully read i.e 1
     */
    int rc = fread(conn->db, sizeof(Database), 1, conn->filename);

    if (rc != 1)
        die("Failed to load database. ");
}

Connection *open_database(const char *filename, char mode)
{
    Connection *conn = malloc(sizeof(Connection));

    if (!conn)
        die("memory error");

    conn->db = malloc(sizeof(Database));

    if (!conn->db)
        die("memory error");

    if (mode == 'c')
    {
        conn->filename = fopen(filename, "w");
    }
    else
    {
        conn->filename = fopen(filename, "r+");

        if (conn->filename)
            load_database(conn);
    }

    if (!conn->filename)
        die("failed to open the file");

    return conn;
}

void write_database(Connection *conn)
{
    rewind(conn->filename);

    // fwrite is similar to fread except it writes binary data from ptr to the file
    int rc = fwrite(conn->db, sizeof(Database), 1, conn->filename);

    if (rc != 1)
        die("failed to write database.");

    // fflush ensures that the data you've written to a stream is actually written to the file or device rather than being held in a buffer
    // used when you want to make sure the data you've written is immediately visible in the output file or on the screen
    // it returns zero if successful and returns EOF if an error occurs
    rc = fflush(conn->filename);

    if (rc == -1)
        die("cannot flush database.");
}

void close_database(Connection *conn)
{
    if (conn)
    {
        if (conn->filename)
            fclose(conn->filename);
        if (conn->db)
            safer_free(conn->db);

        safer_free(conn);
    }
}

void add_user(Connection *conn,
              int id,
              const char *first_name,
              const char *last_name,
              const char *email,
              const char *password_hash,
              const char *salt)
{
    User *user = &conn->db->rows[id];

    if (user->set)
        die("user already exists");

    user->set = 1;

    char *res = strncpy(user->first_name, first_name, MAX_DATA);
    user->first_name[MAX_DATA] = '\0';
    if (!res)
        die("first name copy failed");

    res = strncpy(user->last_name, last_name, MAX_DATA);
    user->last_name[MAX_DATA] = '\0';
    if (!res)
        die("last name copy failed");

    res = strncpy(user->email, email, MAX_DATA);
    user->email[MAX_DATA] = '\0';
    if (!res)
        die("email copy failed");

    res = strncpy(user->password_hash, password_hash, MAX_DATA);
    user->password_hash[MAX_DATA] = '\0';
    if (!res)
        die("password copy failed");

    res = strncpy(user->salt, salt, MAX_DATA);
    user->salt[MAX_DATA] = '\0';
    if (!res)
        die("salt copy failed");
}