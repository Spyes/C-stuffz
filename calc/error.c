#include "error.h"
#include <stdio.h>
#include <stdlib.h>

void cleanup()
{
}

void error(const char *msg)
{
    printf("Error! %s\n", msg);
    cleanup();
    exit(1);
}
