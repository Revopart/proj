#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
int max(int *a, int n);
int min(int *a, int n);
double mean(int *a, int n);
double variance(int *a, int n);

void output_result(int max_v, int min_v, double mean_v, double variance_v);

int main() {
    int n, data[NMAX];
    int status = input(data, &n);
    if (status == -1) {
        printf("n/a");
        return -1;
    }
    output(data, n);
    output_result(max(data, n), min(data, n), mean(data, n), variance(data, n));

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
            printf("%d\n", *p);
        } else {
            printf("%d ", *p);
        }
    }
}

int max(int *a, int n) {
    int max_v;
    for (int *p = a; p - a < n; p++) {
        if (p - a == 0) {
            max_v = *p;
        } else {
            if (max_v < *p) {
                max_v = *p;
            }
        }
    }
    return max_v;
}

int min(int *a, int n) {
    int min_v;
    for (int *p = a; p - a < n; p++) {
        if (p - a == 0) {
            min_v = *p;
        } else {
            if (min_v > *p) {
                min_v = *p;
            }
        }
    }
    return min_v;
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
