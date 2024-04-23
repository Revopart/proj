#include <stdio.h>
#include <stdlib.h>

void sle(double **matrix, int n, int m, double *roots);
double det(double **matrix, int n);
double **input(double **matrix, int *n, int *m);
void del_col(double **matrix, int size, int n, int m, double **new_matrix);
void output_roots(double *roots, int n);

int main() {
    double **matrix = NULL;
    double *roots = NULL;
    int n, m;
    matrix = input(matrix, &n, &m);
    if (matrix == NULL) {
        printf("n/a");
        return -1;
    }
    sle(matrix, n, m, roots);
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}

double **input(double **matrix, int *n, int *m) {
    if (scanf("%d %d", n, m) != 2 || *n < 1 || *m < 1) {
        return NULL;
    } else {
        matrix = malloc(*n * sizeof(double *));
        for (int i = 0; i < *n; i++) {
            matrix[i] = malloc(*m * sizeof(double));
        }
        for (int i = 0; i < *n; i++) {
            for (int j = 0; j < *m; j++) {
                if (scanf("%lf", &matrix[i][j]) != 1) {
                    return NULL;
                }
            }
        }
    }
    return matrix;
}

double det(double **matrix, int n) {
    double **nmatrix = NULL;
    double dets = 0;
    double sign = 1;
    if (n == 1) {
        return matrix[0][0];
    }
    if (n == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    } else {
        nmatrix = malloc((n - 1) * sizeof(double *));
        for (int i = 0; i < n - 1; i++) {
            nmatrix[i] = malloc((n - 1) * sizeof(double));
        }
    }
    for (int i = 0; i < n; i++) {
        del_col(matrix, n, 0, i, nmatrix);
        dets += (sign * (matrix[0][i]) * det(nmatrix, n - 1));
        sign = -sign;
    }
    for (int i = 0; i < n - 1; i++) {
        free(nmatrix[i]);
    }
    free(nmatrix);
    return dets;
}

void output(double **matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j == m - 1) {
                printf("%lf", matrix[i][j]);
            } else {
                printf("%lf ", matrix[i][j]);
            }
        }
        if (i != n - 1) {
            printf("\n");
        }
    }
}

void del_col(double **matrix, int size, int n, int m, double **nmatrix) {
    int o_n = 0;
    int o_m = 0;
    for (int i = 0; i < size - 1; i++) {
        if (i == n) {
            o_n = 1;
        }
        o_m = 0;
        for (int j = 0; j < size - 1; j++) {
            if (j == m) {
                o_m = 1;
            }
            nmatrix[i][j] = matrix[i + o_n][j + o_m];
        }
    }
}

void sle(double **matrix, int n, int m, double *roots) {
    roots = malloc(n * sizeof(double));
    double **nmatrix = malloc((n) * sizeof(double *));
    for (int i = 0; i < n; i++) {
        nmatrix[i] = malloc((n) * sizeof(double));
    }
    int step = 0;
    double d;
    d = det(matrix, n);
    while (step < n - 1) {
        int o_m = 0;
        for (int i = 0; i < n; i++) {
            o_m = 0;
            for (int j = 0; j < n; j++) {
                if (j == m) {
                    o_m = 1;
                }
                nmatrix[i][j] = matrix[i][j + o_m];
            }
        }
        double n_d = det(nmatrix, n);
        step++;
        roots[step] = n_d / d;
    }
    output_roots(roots, n);
    free(roots);
    for (int i = 0; i < n; i++) {
        free(nmatrix[i]);
    }
    free(nmatrix);
}
void output_roots(double *roots, int n) {
    for (int i = 0; i < n; i++) {
        if (i != n - 1) {
            printf("%lf ", roots[i]);
        } else {
            printf("%lf", roots[i]);
        }
    }
}
