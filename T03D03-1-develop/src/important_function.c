#include <math.h>
#include <stdio.h>

int main() {
    float y, x;
    char del;
    if (scanf("%f%c", &x, &del) != 2 || del != '\n') {
        printf("n/a\n");
        return -1;
    }
    y = 7e-3 * pow(x, 4) + ((22.8 * pow(x, (double)(1 / 3)) - 1e3) * x + 3) / (x * x / 2) -
        x * pow(10 + x, 2 / x) - 1.01;
    if (isnan(y) || isinf(y)) {
        printf("n/a\n");
        return -1;
    }
    printf("%.1f\n", y);
    return 0;
}
