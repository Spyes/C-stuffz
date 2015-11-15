#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

#define MULTIPLIER 37

unsigned long hash(const char *str)
{
    unsigned long h;
    unsigned const char *ch;

    ch = (unsigned const char *) str;
    h = 0;
    while (*ch != '\0') {
	h = h * MULTIPLIER + *ch;
	ch++;
    }

    return h;
}

int main(int argc, char **argv)
{
    unsigned long *hash_table = malloc(sizeof(unsigned long));
    char input[30];
    scanf("%30[^\n]", input);
    unsigned long hash_key = hash(input);
    hash_table[hash_key] = 2;
    printf("%lu\n", hash_table[hash_key]);
    return 0;
}
