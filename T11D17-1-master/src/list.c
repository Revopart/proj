#include "list.h"

#include <stdlib.h>

struct node* init(struct door* door) {
    struct node* temp = malloc(sizeof(struct node));
    temp->value = door;
    temp->next = NULL;
    return temp;
}

struct node* add_door(struct node* elem, struct door* door) {
    struct node* tmp = elem->next;
    struct node* new = malloc(sizeof(struct node));
    new->next = tmp;
    new->value = door;
    elem->next = new;

    return new;
}

struct node* find_door(int door_id, struct node* root) {
    struct node* now = root;
    struct node* result = NULL;
    while (now->next != NULL && now->value->id != door_id) {
        now = now->next;
    }
    if (now->value->id == door_id) {
        result = now;
    }
    return result;
}

struct node* remove_door(struct node* elem, struct node* root) {
    struct node* tmp = elem->next;
    struct node* now = root;
    struct node* prev;
    if (root == elem) {
        root = root->next;
        free(elem);
    } else {
        while (now->next != NULL && now != elem) {
            prev = now;
            now = now->next;
        }
        if (now == elem) {
            prev->next = tmp;
            free(elem);
        }
    }
    return root;
}

void destroy(struct node* root) {
    struct node* now = root;
    while (now->next != NULL) {
        struct node* tmp = now->next;
        free(now);
        now = tmp;
    }
    free(now);
}
