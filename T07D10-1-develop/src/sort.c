#include <stdio.h>
#include <stdlib.h>

int read_array(int **a, int *length);
void print_array(int *a, int length);
void sort_array(int *a, int length);

int main() {
    int *array;
    int length;
    if (read_array(&array, &length) == -1) {
        printf("n/a");
        return -1;
    }
    sort_array(array, length);
    print_array(array, length);

    return 0;
}

int read_array(int **a, int *length) {
    char del;
    if (scanf("%d%c", &(*length), &del) != 2 || del != '\n' || *length < 1) {
        return -1;
    }
    *a = (int *)calloc(*length, sizeof(int));
    if (a != NULL) {
        for (int i = 0; i < *length; i++) {
            if (i == (*length - 1)) {
                if (scanf("%d%c", &((*a)[i]), &del) != 2 || del != '\n') {
                    return -1;
                }
            } else {
                if (scanf("%d%c", &((*a)[i]), &del) != 2 || del != ' ') {
                    return -1;
                }
            }
        }
    } else {
        return -1;
    }
    return 0;
}

void print_array(int *a, int length) {
    for (int i = 0; i < length; i++) {
        if (i == (length - 1)) {
            printf("%d", a[i]);
        } else {
            printf("%d ", a[i]);
        }
    }
    free(a);
}

void sort_array(int *a, int length) {
    for (int i = 0; i < (length - 1); i++) {
        for (int j = 0; j < (length - 1); j++) {
            if (a[j + 1] < a[j]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}
