#include <stdio.h>
#include <stdlib.h>
#include "password.h"
#include "database.h"
#include "utils.h"

int main(int argc, char **argv)
{
    if (argc < 3)
        die("usage: mini_db <dbfile> <action> [action params]");

    return EXIT_SUCCESS;
}