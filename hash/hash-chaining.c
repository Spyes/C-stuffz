#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 59

struct node {
    int val;
    struct node *next;
};
typedef struct node item;

item *create_node(int val)
{
    item *temp = (item*)malloc(sizeof(item));
    temp->val = val;
    temp->next = NULL;
    return temp;
}

int hash_function(int val)
{
    return val % HASH_SIZE;
}

void insert(item **hashTable, item **node)
{
    int val = (*node)->val;
    int key = hash_function(val);
    //    item *node = create_node(val);
    if (hashTable[val] == NULL)
        hashTable[val] = (*node);
    else {
        item *curr = hashTable[key];
        while(curr->next != NULL)
            curr = curr->next;
        curr->next = (*node);
    }
}

item *find(item **hashTable, int val)
{
    int key = hash_function(val);
    item *curr = hashTable[key];
    while (curr) {
	if (curr->val == val)
	    return curr;
	curr = curr->next;
    }
    return NULL;
}

int main(int argc, char **argv)
{
    item *hashTable[HASH_SIZE];
    int j;
    for (j = 0; j < HASH_SIZE; j++)
	hashTable[j] = NULL;

    item *n = create_node(10);
    insert(hashTable, &n);
    n = create_node(69);
    insert(hashTable, &n);

    item *f = find(hashTable, 69);
    printf("%i\n", f->val);
    f = find(hashTable, 10);
    printf("%i\n", f->val);

    free(f);
    free(n);
    return 0;
}
