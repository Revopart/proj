#include "list.h"

#include <stdio.h>

#include "door_struct.h"

void add_door_test();
void remove_door_test();

int main() {
    add_door_test();
    remove_door_test();
}
void add_door_test() {
    struct door d1 = {1, 1};
    struct door d2 = {1, 1};
    struct node* a = init(&(d1));
    struct node* b = add_door(a, &(d2));
    if (a->next == b) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }
    destroy(a);
}
void remove_door_test() {
    struct door d1 = {1, 1};
    struct door d2 = {1, 1};
    struct node* a = init(&(d1));
    struct node* b = add_door(a, &(d2));
    remove_door(b, a);
    if (a->next == NULL) {
        printf("SUCCESS");
    } else {
        printf("FAIL");
    }
    destroy(a);
}
