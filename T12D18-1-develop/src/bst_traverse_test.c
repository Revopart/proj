#include <stdio.h>
#include <stdlib.h>

#include "bst.h"
int main() {
    struct t_btree *tree = bstree_create_node(5);
    bstree_insert(tree, 10, compare);
    bstree_insert(tree, 3, compare);
    bstree_apply_infix(tree, print);
    printf("\n");
    bstree_apply_prefix(tree, print);
    printf("\n");
    bstree_apply_postfix(tree, print);
    printf("\n");

    free(tree->left);
    free(tree->right);
    free(tree);
    return 0;
}
