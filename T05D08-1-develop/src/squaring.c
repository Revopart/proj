#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
void squaring(int *a, int n);

int main() {
    int n, data[NMAX];
    int status = input(data, &n);
    if (status == -1) {
        printf("n/a");
        return -1;
    }
    squaring(data, n);
    output(data, n);
    return 0;
}

int input(int *a, int *n) {
    char ch;
    if (scanf("%d%c", &(*n), &ch) != 2 || ch != '\n' || *n > NMAX || *n < 1) {
        return -1;
    }
    for (int *p = a; p - a < *n; p++) {
        if ((p - a) == (*n - 1)) {
            if (scanf("%d%c", p, &ch) != 2 || ch != '\n') {
                return -1;
            }
        } else {
            if (scanf("%d%c", p, &ch) != 2 || ch != ' ') {
                return -1;
            }
        }
    }
    return 0;
}

void output(int *a, int n) {
    for (int *p = a; p - a < n; p++) {
        if (p - a == (n - 1)) {
            printf("%d", *p);
        } else {
            printf("%d ", *p);
        }
    }
}

void squaring(int *a, int n) {
    for (int *p = a; p - a < n; p++) {
        *p = *p * *p;
    }
}
