#include <math.h>
#include <stdio.h>

int devisor(int a) {
    int greatest_dev = 1;
    for (size_t i = 1; i <= fabs(a); i++) {
        int temp_a = fabs(a);
        while (temp_a >= i) {
            temp_a = temp_a - i;
            if (temp_a == 0) {
                int status = 1;
                for (size_t j = 2; j < i; j++) {
                    int temp_i = i;
                    while (temp_i >= j) {
                        temp_i = temp_i - j;
                        if (temp_i == 0) {
                            status = 0;
                        }
                    }
                }
                if (status == 1) {
                    greatest_dev = i;
                }
            }
        }
    }
    return greatest_dev;
}

int main() {
    int a;
    char del;
    if (scanf("%d%c", &a, &del) != 2 || del != '\n') {
        printf("n/a\n");
    } else {
        if (a == 0) {
            printf("0\n");
        } else {
            printf("%d\n", devisor(a));
        }
    }
    return 0;
}
