#include <stdio.h>
#include "hash.h"

int encode_string(char *str)
{
    int i,
	ch,
	n,
	hash_key = 0;
    for (i = 0, ch = str[i]; ch != '\0'; i++, ch = str[i]) {
	n = ch - '0';
	hash_key += n;
    }

    hash_key %= (i * 12);
    return hash_key;
}

int main(int argc, char **argv)
{
    char input[30];
    scanf("%30[^\n]", input);
    int hash_key = encode_string(input);
    printf("%i\n", hash_key);
    return 0;
}
