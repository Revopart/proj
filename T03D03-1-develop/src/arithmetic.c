#include <stdio.h>

int sum(int a, int b) {
    int result = a + b;
    if (result - a != b) {
        return 0;
    } else {
        return 1;
    }
}

int difference(int a, int b) {
    int result = a - b;
    if (result + b != a) {
        return 0;
    } else {
        return 1;
    }
}

int product(int a, int b) {
    int result = a * b;
    if (result / a != b) {
        return 0;
    } else {
        return 1;
    }
}

int devision(int a, int b) {
    if (b == 0) {
        return 0;
    } else {
        return 1;
    }
}

int main(void) {
    int a, b;
    char del1, del2;

    if (scanf("%d%c%d%c", &a, &del1, &b, &del2) != 4 && del1 != ' ' && del2 != '\n') {
        printf("n/a n/a n/a n/a\n");
        return -1;
    }

    if (sum(a, b)) {
        int sum_result = a + b;
        printf("%d ", sum_result);
    } else {
        printf("n/a ");
    }

    if (difference(a, b)) {
        int diff_result = a - b;
        printf("%d ", diff_result);
    } else {
        printf("n/a ");
    }

    if (product(a, b)) {
        int pr_result = a * b;
        printf("%d ", pr_result);
    } else {
        printf("n/a ");
    }

    if (devision(a, b)) {
        int div_result = a / b;
        printf("%d\n", div_result);
    } else {
        printf("n/a\n");
    }

    return 0;
}
