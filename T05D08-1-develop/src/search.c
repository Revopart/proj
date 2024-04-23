#include <math.h>
#include <stdio.h>
#define NMAX 30

int input(int *a, int *n);
void output(int *a, int n);
double mean(int *a, int n);
double variance(int *a, int n);
int is_even(int a) {
    if (a % 2 == 0) {
        return 1;
    } else {
        return 0;
    }
}
void output_result(int max_v, int min_v, double mean_v, double variance_v);

int main() {
    int n, data[NMAX];
    int status = input(data, &n);
    if (status == -1) {
        printf("n/a");
        return -1;
    }
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
    int finded = 0;
    for (int *p = a; p - a < n; p++) {
        if (is_even(*p) && *p >= mean(a, n) && *p <= (mean(a, n) + 3 * sqrt(variance(a, n))) && *p != 0) {
            if (finded == 0) {
                finded = 1;
                printf("%d", *p);
            }
        }
    }
    if (finded == 0) {
        printf("0");
    }
}

double mean(int *a, int n) {
    double sum = 0;
    for (int *p = a; p - a < n; p++) {
        sum += *p;
    }
    double mean_v = sum / n;
    return mean_v;
}

double variance(int *a, int n) {
    double m = mean(a, n);
    double variance_sum = 0.0;
    for (int *p = a; p - a < n; p++) {
        variance_sum = variance_sum + ((*p - m) * (*p - m));
    }
    double variance_v = variance_sum / n;
    return variance_v;
}

void output_result(int max_v, int min_v, double mean_v, double variance_v) {
    printf("%d %d %.6f %.6f", max_v, min_v, mean_v, variance_v);
}
