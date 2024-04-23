#include <stdio.h>
#define SIZE 10

int read_array(int *a);
void print_array(int *a);
void sort_array(int *a);

int main() {
    int array[SIZE];
    if (read_array(array) == -1) {
        printf("n/a");
        return -1;
    }
    sort_array(array);
    print_array(array);

    return 0;
}

int read_array(int *a) {
    char del;
    for (int i = 0; i < SIZE; i++) {
        if (i == (SIZE - 1)) {
            if (scanf("%d%c", &a[i], &del) != 2 || del != '\n') {
                return -1;
            }
        } else {
            if (scanf("%d%c", &a[i], &del) != 2 || del != ' ') {
                return -1;
            }
        }
    }
    return 0;
}

void print_array(int *a) {
    for (int i = 0; i < SIZE; i++) {
        if (i == (SIZE - 1)) {
            printf("%d", a[i]);
        } else {
            printf("%d ", a[i]);
        }
    }
}

void sort_array(int *a) {
    for (int i = 0; i < (SIZE - 1); i++) {
        for (int j = 0; j < (SIZE - 1); j++) {
            if (a[j + 1] < a[j]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}
