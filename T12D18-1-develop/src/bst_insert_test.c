#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

int main() {
    struct t_btree *tree = bstree_create_node(5);
    bstree_insert(tree, 10, compare);
    bstree_insert(tree, 3, compare);
    printf("%p\n", tree);
    printf("%p\n", tree->left);
    printf("%p\n", tree->right);
    printf("%p\n", tree->parent);
    printf("%d\n", tree->val);
    printf("%d\n", tree->left->val);
    printf("%p\n", tree->left->parent);
    printf("%d\n", tree->right->val);
    printf("%p\n", tree->right->parent);
    free(tree->left);
    free(tree->right);
    free(tree);
    return 0;
}
