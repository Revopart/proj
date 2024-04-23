#include <stdio.h>
#include <stdlib.h>

int reg();
int **input(int **matrix, int *n, int *m);
void output(int **matrix, int n, int m);
int sum(int **matrix_first, int n_first, int m_first, int **matrix_second, int n_second, int m_second,
        int **matrix_result, int *n_result, int *m_result);
int transpose(int **matrix, int n, int m);
int mul(int **matrix_first, int n_first, int m_first, int **matrix_second, int n_second, int m_second,
        int **matrix_result, int *n_result, int *m_result);

int main() {
    int n_first, m_first, n_second, m_second, n_result, m_result;
    int **matrix_first = NULL;
    int **matrix_second = NULL;
    int **matrix_result = NULL;
    int flag = reg();
    if (flag == 1) {
        matrix_first = input(matrix_first, &n_first, &m_first);
        if (matrix_first == NULL) {
            printf("n/a");
            return -1;
        }
        matrix_second = input(matrix_second, &n_second, &m_second);
        if (matrix_second == NULL) {
            printf("n/a");
            return -1;
        }
        if (sum(matrix_first, n_first, m_first, matrix_second, n_second, m_second, matrix_result, &n_result,
                &m_result) == -1) {
            printf("n/a");
            return -1;
        }
    } else if (flag == 2) {
        matrix_first = input(matrix_first, &n_first, &m_first);
        if (matrix_first == NULL) {
            printf("n/a");
            return -1;
        }
        matrix_second = input(matrix_second, &n_second, &m_second);
        if (matrix_second == NULL) {
            printf("n/a");
            return -1;
        }
        if (mul(matrix_first, n_first, m_first, matrix_second, n_second, m_second, matrix_result, &n_result,
                &m_result) == -1) {
            printf("n/a");
            return -1;
        }
    } else if (flag == 3) {
        matrix_first = input(matrix_first, &n_first, &m_first);
        if (matrix_first == NULL) {
            printf("n/a");
            return -1;
        }
        if (transpose(matrix_first, n_first, m_first) == -1) {
            printf("n/a");
            return -1;
        }
    } else {
        printf("n/a");
        return -1;
    }
    return 0;
}

int reg() {
    int flag;
    if (scanf("%d", &flag) == 1) {
        return flag;
    } else {
        return -1;
    }
}

int **input(int **matrix, int *n, int *m) {
    if (scanf("%d%d", n, m) != 2 || *m < 1 || *n < 1) {
        return NULL;
    }
    matrix = malloc((*n) * sizeof(int *));
    for (int i = 0; i < *n; i++) {
        matrix[i] = (int *)malloc((*m) * sizeof(int));
    }
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *m; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                return NULL;
            }
        }
    }
    return matrix;
}

int sum(int **matrix_first, int n_first, int m_first, int **matrix_second, int n_second, int m_second,
        int **matrix_result, int *n_result, int *m_result) {
    if (n_first != n_second || m_first != m_second) {
        return -1;
    } else {
        *n_result = n_first;
        *m_result = m_first;
    }
    matrix_result = malloc(*n_result * sizeof(int *));
    if (matrix_result == NULL) {
        return -1;
    }
    for (int i = 0; i < *n_result; i++) {
        matrix_result[i] = malloc(*m_result * sizeof(int));
        if (matrix_result[i] == NULL) {
            return -1;
        }
    }
    for (int i = 0; i < *n_result; i++) {
        for (int j = 0; j < *m_result; j++) {
            matrix_result[i][j] = matrix_first[i][j] + matrix_second[i][j];
        }
    }
    output(matrix_result, *n_result, *m_result);
    for (int i = 0; i < *n_result; i++) {
        free(matrix_first[i]);
        free(matrix_second[i]);
        free(matrix_result[i]);
    }
    free(matrix_first);
    free(matrix_second);
    free(matrix_result);
    return 0;
}

int mul(int **matrix_first, int n_first, int m_first, int **matrix_second, int n_second, int m_second,
        int **matrix_result, int *n_result, int *m_result) {
    if (n_second != m_first) {
        return -1;
    } else {
        *n_result = n_first;
        *m_result = m_second;
    }
    matrix_result = malloc(*n_result * sizeof(int *));
    if (matrix_result == NULL) {
        return -1;
    }
    for (int i = 0; i < *n_result; i++) {
        matrix_result[i] = malloc(*m_result * sizeof(int));
        if (matrix_result[i] == NULL) {
            return -1;
        }
    }

    for (int i = 0; i < *n_result; i++) {
        for (int j = 0; j < *m_result; j++) {
            matrix_result[i][j] = 0;
            for (int k = 0; k < m_first; k++) {
                matrix_result[i][j] = matrix_result[i][j] + matrix_first[i][k] * matrix_second[k][j];
            }
        }
    }
    output(matrix_result, *n_result, *m_result);
    for (int i = 0; i < n_first; i++) {
        free(matrix_first[i]);
    }
    for (int i = 0; i < n_second; i++) {
        free(matrix_second[i]);
    }
    for (int i = 0; i < *n_result; i++) {
        free(matrix_result[i]);
    }
    free(matrix_first);
    free(matrix_second);
    free(matrix_result);
    return 0;
}

int transpose(int **matrix, int n, int m) {
    int **temp = malloc(m * sizeof(int *));
    if (temp == NULL) {
        return -1;
    }
    for (int i = 0; i < m; i++) {
        temp[i] = malloc(n * sizeof(int));
        if (temp[i] == NULL) {
            return -1;
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            temp[i][j] = matrix[j][i];
        }
    }
    output(temp, n, n);
    for (int i = 0; i < m; i++) {
        free(temp[i]);
    }
    free(temp);
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
    return 0;
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
