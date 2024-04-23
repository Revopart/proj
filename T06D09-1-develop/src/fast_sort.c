#include <stdio.h>
#define SIZE 10

int read_array(int *buff1, int *buff2);
void print_array(int *buff);
void heap_sort_help(int *buff, int n, int i);
void quick_sort(int *buff, int left, int right);
void swap(int *a, int *b);
void heap_sort(int *buff, int n);

int main() {
    int buff1[SIZE], buff2[SIZE];
    read_array(buff1, buff2);
    quick_sort(buff1, 0, SIZE - 1);
    heap_sort(buff2, SIZE);
    print_array(buff1);
    print_array(buff2);
    return 0;
}

int read_array(int *buff1, int *buff2) {
    char del;
    for (int i = 0; i < SIZE; i++) {
        if (i == (SIZE - 1)) {
            if (scanf("%d%c", &buff1[i], &del) != 2 || del != '\n') {
                return -1;
            }
        } else {
            if (scanf("%d%c", &buff1[i], &del) != 2 || del != ' ') {
                return -1;
            }
        }
        buff2[i] = buff1[i];
    }
    return 0;
}

void print_array(int *a) {
    for (int i = 0; i < SIZE; i++) {
        if (i == (SIZE - 1)) {
            printf("%d\n", a[i]);
        } else {
            printf("%d ", a[i]);
        }
    }
}
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heap_sort_help(int *buff, int n, int i) {
    int larg = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && buff[left] > buff[larg]) {
        larg = left;
    }
    if (right < n && buff[right] > buff[larg]) {
        larg = right;
    }
    if (larg != i) {
        swap(&buff[i], &buff[larg]);

        heap_sort_help(buff, n, larg);
    }
}
void heap_sort(int *buff, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) heap_sort_help(buff, n, i);
    for (int i = n - 1; i >= 0; i--) {
        swap(&buff[0], &buff[i]);
        heap_sort_help(buff, i, 0);
    }
}
void quick_sort(int *buff, int left, int right) {
    int pivot;
    int index;
    int l_hold = left;
    int r_hold = right;
    pivot = buff[left];
    while (left < right) {
        while ((buff[right] > pivot) && (left < right)) right--;
        if (left != right) {
            buff[left] = buff[right];
            left++;
        }
        while ((buff[left] < pivot) && (left < right)) left++;
        if (left != right) {
            buff[right] = buff[left];
            right--;
        }
    }
    buff[left] = pivot;
    index = left;
    left = l_hold;
    right = r_hold;
    if (left < index) {
        quick_sort(buff, left, index - 1);
    }
    if (right > index) quick_sort(buff, index + 1, right);
}
