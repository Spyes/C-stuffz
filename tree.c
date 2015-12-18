#include <stdio.h>
#include <stdlib.h>

struct node {
    int val;
    struct node *left;
    struct node *right;
};
typedef struct node node;

node *create_leaf(int val)
{
    node *n = (node*)malloc(sizeof(node));
    n->left = NULL;
    n->right = NULL;
    n->val = val;
    return n;
}

void insert(node **root, int val)
{
    node *temp = NULL;
    if (!(*root)) {
	temp = create_leaf(val);
	*root = temp;
	return;
    }

    if (val < (*root)->val)
	insert(&(*root)->left, val);
    else if (val > (*root)->val)
	insert(&(*root)->right, val);
}

void setup_tree(node **root)
{
    insert(root, 5);
    insert(root, 6);
    insert(root, 7);
    insert(root, 2);
    insert(root, 10);
    insert(root, 13);
    insert(root, 11);
    insert(root, 4);
    insert(root, 20);
    insert(root, 15);
    insert(root, 1);
    insert(root, 22);
    insert(root, 3);
}

node *cleanup_tree(node **root)
{
    if (!(*root)) return NULL;
    cleanup_tree(&(*root)->left);
    cleanup_tree(&(*root)->right);
    free((*root));
}

node *find(node **root, int search_val)
{
    if (!(*root)) return NULL;
    if ((*root)->val == search_val)
	return (*root);
    if (search_val < (*root)->val)
	find(&(*root)->left, search_val);
    else if (search_val > (*root)->val)
	find(&(*root)->right, search_val);
}

void traverse(node *root)
{
    if (!root) return;
    traverse(root->left);
    traverse(root->right);
    printf("%i\n", root->val);
}

int tree_size(node *root)
{
    int lsize, rsize;
    if (!root) return 0;
    return (tree_size(root->left) + 1 + tree_size(root->right));
}

int max_depth(node *root)
{
    if (!root) return 0;
    int ldepth = max_depth(root->left);
    int rdepth = max_depth(root->right);
    if (ldepth > rdepth) return ldepth + 1;
    return rdepth + 1;
}

int min_value(node *root)
{
    if (!root->left) return root->val;
    min_value(root->left);
}

int max_value(node *root)
{
    if (!root->right) return root->val;
    max_value(root->right);
}

int main(int argc, char **argv)
{
    node *root = create_leaf(5);
    setup_tree(&root);
    node *f = find(&root, 7);
    if (f)
	printf("Found %i\n", f->val);
    int maxd = max_depth(root);
    printf("Max depth: %i\n", maxd);
    int s = tree_size(root);
    printf("Size: %i\n", s);
    int minv = min_value(root);
    printf("Minimum value: %i\n", minv);
    int maxv = max_value(root);
    printf("Maximum value: %i\n", maxv);
    traverse(root);
    cleanup_tree(&root);
    return 0;
}
