#include <stdio.h>
#include <stdlib.h>

int select_mode(int* n, int* m);
int first_mode(int** arr, int m, int n);
int second_mode(int** arr, int m, int n);
int third_mode(int** arr, int m, int n);
void sort(int** arr, int n, int m);

int main() {
    int n, m;
    int mode = select_mode(&m, &n);
    if (mode == 1) {
        int** arr = malloc(m * n * sizeof(int) + m * sizeof(int*));
        first_mode(arr, m, n);
    } else if (mode == 2) {
        int** arr = malloc(m * sizeof(int*));
        second_mode(arr, m, n);

    } else if (mode == 3) {
        int** arr = malloc(m * sizeof(int*));
        third_mode(arr, m, n);
    } else {
        printf("n/a");
        return -1;
    }
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

int first_mode(int** arr, int m, int n) {
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

    sort(arr, m, n);
    free(arr);
    return 0;
}

int second_mode(int** arr, int m, int n) {
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

    sort(arr, m, n);
    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);
    return 0;
}

int third_mode(int** arr, int m, int n) {
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
    sort(arr, m, n);
    free(arr);
    free(ptr);
    return 0;
}
void sort(int** arr, int n, int m) {
    int result[n][2];
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = 0; j < m; j++) {
            sum += arr[i][j];
        }
        result[i][0] = i;
        result[i][1] = sum;
    }
    for (int i = 0; i < (n - 1); i++) {
        for (int j = 0; j < (n - 1); j++) {
            if (result[j + 1][1] < result[j][1]) {
                int temp1 = result[j][1];
                int temp2 = result[j][0];

                result[j][1] = result[j + 1][1];
                result[j][0] = result[j + 1][0];
                result[j + 1][1] = temp1;
                result[j + 1][0] = temp2;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        int row = result[i][0];
        for (int j = 0; j < m; j++) {
            if (j != m - 1) {
                printf("%d ", arr[row][j]);
            } else {
                printf("%d", arr[row][j]);
            }
        }
        if (i != m - 1) {
            printf("\n");
        }
    }
}
