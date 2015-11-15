#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 60

struct DataItem {
    int val;
};
typedef struct DataItem item;

int hashFunc(int key)
{
    return key % ARRAY_SIZE;
}

item *create_node(int val)
{
    item *temp = (item*)malloc(sizeof(item));
    temp->val = val;
    return temp;
}

void insert(item **table, item **node)
{
    int key = hashFunc((*node)->val);
    while (table[key] != NULL && (*table[key]).val != -1) {
        key++;
        key %= ARRAY_SIZE;
    }
    table[key] = (*node);
}

item *find(item **table, int val)
{
    int key = hashFunc(val);
    while (table[key] != NULL) {
        if ((*table[key]).val == val)
            return table[key];
        ++key;
        key %= ARRAY_SIZE;
    }
    return NULL;
}

item *delete(item **table, int val, item **nonItem)
{
    int key = hashFunc(val);
    while (table[key] != NULL) {
        if ((*table[key]).val == val) {
            item *temp = table[key];
            table[key] = (*nonItem);
            return temp;
        }
        ++key;
        key %= ARRAY_SIZE;
    }
    return NULL;
}

int main(int argc, char **argv)
{
    item *hashTable[ARRAY_SIZE] = { 0 };

    item *nonItem = (item*)malloc(sizeof(item));
    nonItem->val = -1;

    item *i = create_node(172);
    insert(hashTable, &i);

    i = create_node(833);
    insert(hashTable, &i);

    i = create_node(413);
    insert(hashTable, &i);

    item *r = delete(hashTable, 413, &nonItem);
    if (!r)
        printf("Could not remove 413\n");
    else {
        printf("Removed 413\n");
    }
    
    r = delete(hashTable, 833, &nonItem);
    if (!r)
        printf("Could not remove 833\n");
    else {
        printf("Removed 833\n");
    } 

    int j;
    for (j = 0; j < ARRAY_SIZE; j++)
        if (hashTable[j])
            free(hashTable[j]);

    return 0;
}
