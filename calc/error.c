#include "error.h"
#include "main.h"
#include <stdio.h>
#include <stdlib.h>

void quit_error(const char *msg)
{
    printf("Error! %s\nQuitting\n", msg);
    cleanup();
    exit(1);
}

void error(const char *msg)
{
    printf("Error! %s\n", msg);
}

void quit_elegantly()
{
    printf("Goodbye!\n");
    cleanup();
    exit(0);
}
