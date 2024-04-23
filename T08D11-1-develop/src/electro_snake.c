#include <stdio.h>
#include <stdlib.h>

void sort_vertical(int **matrix, int n, int m);
void sort_horizontal(int **matrix, int n, int m);
int *sort_array(int **matrix, int n, int m);

int **input(int **matrix, int *n, int *m);
void output(int **matrix, int n, int m);

int main() {
    int **matrix = NULL;
    int n, m;
    matrix = input(matrix, &n, &m);
    if (matrix == NULL) {
        printf("n/a");
        return -1;
    }
    sort_vertical(matrix, n, m);

    sort_horizontal(matrix, n, m);
    return 0;
}

int **input(int **matrix, int *n, int *m) {
    if (scanf("%d %d", n, m) != 2 || *n < 1 || *m < 1) {
        return NULL;
    } else {
        matrix = malloc(*n * sizeof(int *));
        for (int i = 0; i < *n; i++) {
            matrix[i] = malloc(*m * sizeof(int));
        }
        for (int i = 0; i < *n; i++) {
            for (int j = 0; j < *m; j++) {
                if (scanf("%d", &matrix[i][j]) != 1) {
                    return NULL;
                }
            }
        }
    }
    return matrix;
}

void output(int **matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j == m - 1) {
                printf("%d", matrix[i][j]);
            } else {
                printf("%d ", matrix[i][j]);
            }
        }
        if (i != n - 1) {
            printf("\n");
        }
    }
}

void sort_vertical(int **matrix, int n, int m) {
    int length = n * m;
    int *a = malloc(length * sizeof(int));
    int ind = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            a[ind] = matrix[i][j];
            ind++;
        }
    }

    for (int i = 0; i < (length - 1); i++) {
        for (int j = 0; j < (length - 1); j++) {
            if (a[j + 1] < a[j]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    int step = 0;
    int dir = 0;
    int i = 0;
    int j = 0;
    while (step != n * m - 1) {
        matrix[i][j] = a[step];
        if (dir == 0) {
            if (i == n - 1) {
                dir = 1;
                j++;
            } else {
                i++;
            }
        } else {
            if (i == 0) {
                dir = 0;
                j++;
            } else {
                i--;
            }
        }
        step++;
    }
    output(matrix, n, m);
    printf("\n\n");
    free(a);
}

void sort_horizontal(int **matrix, int n, int m) {
    int length = n * m;
    int *a = malloc(length * sizeof(int));
    int ind = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            a[ind] = matrix[i][j];
            ind++;
        }
    }

    for (int i = 0; i < (length - 1); i++) {
        for (int j = 0; j < (length - 1); j++) {
            if (a[j + 1] < a[j]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    int step = 0;
    int dir = 0;
    int i = 0;
    int j = 0;
    while (step != n * m - 1) {
        matrix[i][j] = a[step];
        if (dir == 0) {
            if (j == m - 1) {
                dir = 1;
                i++;
            } else {
                j++;
            }
        } else {
            if (j == 0) {
                dir = 0;
                i++;
            } else {
                j--;
            }
        }
        step++;
    }
    output(matrix, n, m);
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(a);
}
