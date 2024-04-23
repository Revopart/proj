
#include "../data_libs/data_io.h"

#include <stdio.h>
#include <stdlib.h>

double *input(double *data, int *n) {
    double *flag;
    if (scanf("%d", n) != 1 || *n < 1) {
        flag = NULL;
    } else {
        data = malloc(*n * sizeof(double));
        for (int i = 0; i < *n; i++) {
            if (scanf("%lf", &data[i]) != 1) {
                flag = NULL;
            }
        }
        flag = data;
    }
    return flag;
}

void output(double *data, int n) {
    for (int i = 0; i < n; i++) {
        if (i == n - 1) {
            printf("%.2lf", data[i]);
        } else {
            printf("%.2lf ", data[i]);
        }
    }
}

double *input_double(double *data, int *n) {
    double *flag;
    if (scanf("%d", n) != 1 || *n < 1) {
        flag = NULL;
    } else {
        data = malloc(*n * sizeof(double));
        for (int i = 0; i < *n; i++) {
            if (scanf("%lf", &data[i]) != 1) {
                flag = NULL;
            }
        }
        flag = data;
    }
    return flag;
}
