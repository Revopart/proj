#include "bst.h"

#include <stdio.h>
#include <stdlib.h>
struct t_btree *bstree_create_node(int item) {
    struct t_btree *tree = malloc(sizeof(struct t_btree));
    tree->val = item;
    tree->left = NULL;
    tree->right = NULL;
    return tree;
};

int compare(int a, int b) { return a - b; }

void bstree_insert(struct t_btree *root, int item, int (*cmpf)(int, int)) {
    struct t_btree *new = bstree_create_node(item);
    while (root != NULL) {
        if (cmpf(new->val, root->val) > 0) {
            if (root->right != NULL) {
                root = root->right;
            } else {
                new->parent = root;
                root->right = new;
                break;
            }
        } else if (cmpf(new->val, root->val) < 0) {
            if (root->left != NULL) {
                root = root->left;
            } else {
                new->parent = root;
                root->left = new;
                break;
            }
        }
    }
}
void print(int a) { printf("%d ", a); }
void bstree_apply_infix(struct t_btree *root, void (*applyf)(int)) {
    if (root == NULL) {
        return;
    }
    bstree_apply_infix(root->left, applyf);
    applyf(root->val);
    bstree_apply_infix(root->right, applyf);
}
void bstree_apply_prefix(struct t_btree *root, void (*applyf)(int)) {
    if (root == NULL) {
        return;
    }
    bstree_apply_prefix(root->right, applyf);
    applyf(root->val);
    bstree_apply_prefix(root->left, applyf);
}
void bstree_apply_postfix(struct t_btree *root, void (*applyf)(int)) {
    if (root == NULL) {
        return;
    }
    applyf(root->val);
    bstree_apply_infix(root->left, applyf);
    bstree_apply_infix(root->right, applyf);
}
