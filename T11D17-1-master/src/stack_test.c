#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

void push_test();
void pop_test();

int main() {
    push_test();
    pop_test();
    return 0;
}

void push_test() {
    struct el *a = init(1);
    struct el *temp = a;
    struct el *temp2 = push(2, a);
    if (temp2 == temp) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }
    free(temp->next);
    free(temp);
}
void pop_test() {
    struct el *a = init(1);
    push(2, a);
    if (pop(a) == 2) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }
}
