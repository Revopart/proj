#include <stdio.h>
#include <stdlib.h>

int select_mode(int* n, int* m);
int first_mode(int arr[][100], int m, int n);
int second_mode(int** arr, int m, int n);
int third_mode(int** arr, int m, int n);
int fourth_mode(int** arr, int m, int n);
void output_static(int arr[][100], int m, int n);
void output_dinamic(int** arr, int m, int n);
void min_collumns(int** arr, int m, int n);
void max_rows(int** arr, int m, int n);

int main() {
    int n, m;
    int mode = select_mode(&m, &n);
    if (mode == 1) {
        int arr[100][100];
        int flag = first_mode(arr, m, n);
        if (flag == -1) {
            printf("n/a");
            return -1;
        }
        output_static(arr, m, n);
    } else if (mode == 2) {
        int** arr = malloc(m * n * sizeof(int) + m * sizeof(int*));
        second_mode(arr, m, n);
        output_dinamic(arr, m, n);
        free(arr);

    } else if (mode == 3) {
        int** arr = malloc(m * sizeof(int*));
        third_mode(arr, m, n);
        output_dinamic(arr, m, n);
        for (int i = 0; i < n; i++) {
            free(arr[i]);
        }
        free(arr);
    } else if (mode == 4) {
        int** arr = malloc(m * sizeof(int*));
        fourth_mode(arr, m, n);
        output_dinamic(arr, m, n);
        free(arr);
    } else {
        printf("n/a");
        return -1;
    }
    return 0;
}

int select_mode(int* m, int* n) {
    int mode;
    if (scanf("%d", &mode) != 1) {
        return -1;
    }
    if (scanf("%d%d", m, n) != 2 || *n < 1 || *m < 1) {
        return -1;
    }
    return mode;
}

int first_mode(int arr[][100], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (scanf("%d", &arr[i][j]) != 1) {
                return -1;
            }
        }
    }
    return 0;
}

void output_static(int arr[][100], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (j != m - 1) {
                printf("%d ", arr[i][j]);
            } else {
                printf("%d", arr[i][j]);
            }
        }
        printf("\n");
    }
}

void output_dinamic(int** arr, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (j != m - 1) {
                printf("%d ", arr[i][j]);
            } else {
                printf("%d", arr[i][j]);
            }
        }
        printf("\n");
    }
    max_rows(arr, m, n);
    min_collumns(arr, m, n);
}

int second_mode(int** arr, int m, int n) {
    int* ptr = (int*)(arr + m);
    for (int i = 0; i < m; i++) {
        arr[i] = ptr + n * i;
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (scanf("%d", &arr[i][j]) != 1) {
                return -1;
            }
        }
    }
    return 0;
}

int third_mode(int** arr, int m, int n) {
    for (int i = 0; i < m; i++) {
        arr[i] = malloc(n * sizeof(int));
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (scanf("%d", &arr[i][j]) != 1) {
                return -1;
            }
        }
    }
    return 0;
}

int fourth_mode(int** arr, int m, int n) {
    int* ptr = malloc(m * n * sizeof(int));
    for (int i = 0; i < m; i++) {
        arr[i] = ptr + n * i;
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (scanf("%d", &arr[i][j]) != 1) {
                return -1;
            }
        }
    }
    free(ptr);
    return 0;
}
void max_rows(int** arr, int m, int n) {
    int ma;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (j == 0) {
                ma = arr[i][0];
            } else if (arr[i][j] > ma) {
                ma = arr[i][j];
            }
            if (j == n - 1) {
                if (i != m - 1) {
                    printf("%d ", ma);
                } else {
                    printf("%d\n", ma);
                }
            }
        }
    }
}
void min_collumns(int** arr, int m, int n) {
    int min;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j == 0) {
                min = arr[0][i];
            } else if (arr[j][i] < min) {
                min = arr[j][i];
            }
            if (j == m - 1) {
                if (i != n - 1) {
                    printf("%d ", min);
                } else {
                    printf("%d", min);
                }
            }
        }
    }
}
