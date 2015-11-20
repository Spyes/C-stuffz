#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void displayWord(char *word)
{
    printf("%s\n", word);
}

void rotate(int orgSize, int newSize, char *word)
{
    int j;
    int position = orgSize - newSize;
    char temp = word[position];
    for (j = position + 1; j < orgSize; j++)
	word[j - 1] = word[j];
    word[j - 1] = temp;
}

void anagram(int orgSize, int newSize, char *word)
{
    if (newSize == 1)
	return;

    int j;
    for (j = 0; j < newSize; j++) {
	anagram(orgSize, newSize - 1, word);
	if (newSize == 2)
	    displayWord(word);
	rotate(orgSize, newSize, word);
    }
}

int main(int argc, char **argv)
{
    char input[10];
    scanf("%s", input);
    int len = strlen(input);
    anagram(len, len, input);
    return 0;
}
