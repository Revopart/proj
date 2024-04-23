#ifndef BST_H
#define BST_H

struct t_btree {
    struct t_btree *left;
    struct t_btree *right;
    struct t_btree *parent;
    int val;
};

struct t_btree *bstree_create_node(int item);
void bstree_insert(struct t_btree *root, int item, int (*cmpf)(int, int));
int compare(int a, int b);
void bstree_apply_infix(struct t_btree *root, void (*applyf)(int));
void bstree_apply_prefix(struct t_btree *root, void (*applyf)(int));
void bstree_apply_postfix(struct t_btree *root, void (*applyf)(int));
void print(int val);
#endif
