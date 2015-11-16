#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 59

struct node {
    int val;
    char *str;
    struct node *next;
};
typedef struct node item;

item *create_node(int val, char *str)
{
    item *temp = (item*)malloc(sizeof(item));
    temp->val = val;
    temp->str = str;
    temp->next = NULL;
    return temp;
}

int hash_function(int val)
{
    return val % HASH_SIZE;
}

int hash_string_function(char *str)
{
    int hashVal = 0;
    int ch, i;
    for (i = 0, ch = str[i]; ch != '\0'; i++, ch = str[i]) {
	hashVal = (hashVal * 27 + (ch - '0')) % HASH_SIZE;
    }
    return hashVal;
}

void insert(item **hashTable, item **node)
{
    int key;
    if ((*node)->val && (*node)->val > -1)
	key = hash_function((*node)->val);
    else if ((*node)->str)
	key = hash_string_function((*node)->str);

    if (hashTable[key] == NULL)
        hashTable[key] = (*node);
    else {
        item *curr = hashTable[key];
        while(curr->next != NULL)
            curr = curr->next;
        curr->next = (*node);
    }
}

item *find(item **hashTable, int val, char *str)
{
    int key;
    if (val > -1)
	key = hash_function(val);
    else if (str)
	key = hash_string_function(str);
    item *curr = hashTable[key];
    while (curr) {
	if ((val > -1 && curr->val == val) ||
	    (str && (strcmp(str, curr->str) == 0)))
	    return curr;
	curr = curr->next;
    }
    return NULL;
}

void print(item *node)
{
    if (node)
	node->str ? printf("%s\n", node->str) : printf("%i\n", node->val);
}

int main(int argc, char **argv)
{
    item *hashTable[HASH_SIZE];
    int j;
    for (j = 0; j < HASH_SIZE; j++)
	hashTable[j] = NULL;

    item *n = create_node(-1, "test");
    insert(hashTable, &n);
    n = create_node(10, NULL);
    insert(hashTable, &n);

    item *f = find(hashTable, -1, "test");
    print(f);
    f = find(hashTable, 10, NULL);
    print(f);

    for (j = 0; j < HASH_SIZE; j++)
	if (hashTable[j]) free(hashTable[j]);

    return 0;
}
