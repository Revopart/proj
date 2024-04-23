#ifndef STACK_H
#define STACK_H

struct el {
    int val;
    struct el *next;
};

struct el *init(int a);
struct el *push(int a, struct el *st);
int pop(struct el *st);
void destroy(struct el *st);

#endif
