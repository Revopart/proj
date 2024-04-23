#include <stdio.h>

int max(int a, int b) {
    int max = a;
    if (b > a) {
        max = b;
    }
    return max;
}

int main() {
    int a, b;
    char del1, del2;

    if (scanf("%d%c%d%c", &a, &del1, &b, &del2) != 4 || del1 != ' ' || del2 != '\n') {
        printf("n/a\n");
        return -1;
    }
    int max_number = max(a, b);
    printf("%d\n", max_number);
    return 0;
}
