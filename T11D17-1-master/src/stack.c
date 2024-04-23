#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

struct el *init(int a) {
    struct el *tmp = malloc(sizeof(int));
    tmp->next = NULL;
    tmp->val = a;
    return tmp;
}
struct el *push(int a, struct el *st) {
    struct el *tmp = malloc(sizeof(int));
    tmp->val = st->val;
    tmp->next = st->next;
    st->val = a;
    st->next = tmp;
    return st;
}
int pop(struct el *st) {
    int temp = st->val;
    struct el *tmp = st->next;
    free(st);
    st = tmp;
    return temp;
}
void destroy(struct el *st) {
    struct el *tmp;
    while (tmp->next != NULL) {
        tmp = tmp->next;
        free(st);
    }
}
