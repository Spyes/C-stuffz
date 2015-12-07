#include <stdio.h>
#include <stdlib.h>

struct node {
    int val;
    struct node *left;
    struct node *right;
};
typedef struct node node;

void setup_tree(node **root)
{
    node *r = (node*)malloc(sizeof(node));
    node *l = (node*)malloc(sizeof(node));
    r->val = 5;
    l->val = 6;
    (*root)->right = r;
    (*root)->left = l;

    r->left = (node*)malloc(sizeof(node));
    r->left->val = 7;
}

node *cleanup_tree(node **root)
{
    node *cur, *left, *right;
    cur = (*root);
    if (!cur) return NULL;
    cleanup_tree(&cur->left);
    cleanup_tree(&cur->right);
}

int main(int argc, char **argv)
{
    node *root = (node*)malloc(sizeof(node));
    cleanup_tree(&root);
    return 0;
}
