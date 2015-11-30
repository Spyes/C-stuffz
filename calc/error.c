#include "error.h"
#include "main.h"
#include <stdio.h>
#include <stdlib.h>

void error(const char *msg)
{
    printf("Error! %s\n", msg);
    cleanup();
    exit(1);
}

void quit_elegantly()
{
    printf("Goodbye!\n");
    cleanup();
    exit(0);
}
