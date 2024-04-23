#include <stdio.h>

int main() {
    float a, b;
    char del1, del2;

    if (scanf("%f%c%f%c", &a, &del1, &b, &del2) != 4 || del1 != ' ' || del2 != '\n') {
        printf("n/a\n");
        return -1;
    }
    if (a * a + b * b < 25) {
        printf("GOTCHA\n");
    } else {
        printf("MISS\n");
    }
    return 0;
}
