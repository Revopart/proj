#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

int main() {
    struct t_btree *tree = bstree_create_node(5);
    printf("%p\n", tree->left);
    printf("%p\n", tree->right);
    printf("%p\n", tree->parent);
    printf("%d\n", tree->val);
    struct t_btree *tree1 = bstree_create_node(10);
    printf("%p\n", tree1->left);
    printf("%p\n", tree1->right);
    printf("%p\n", tree1->parent);
    printf("%d", tree1->val);
    free(tree);
    free(tree1);
    return 0;
}
