#include <stdio.h>

int fib(int a) {
    if (a == 2 || a == 1) {
        return 1;
    } else {
        return fib(a - 1) + fib(a - 2);
    }
}

int main() {
    int a;
    char del;
    if (scanf("%d%c", &a, &del) != 2 || del != '\n') {
        printf("n/a\n");
        return -1;
    }
    if (a < 1) {
        printf("n/a\n");
        return -1;
    }
    printf("%d\n", fib(a));
    return 0;
}
