#include <stdio.h>
#define SIZE 10

int input(int *buffer, int *length, int *shift);
void output(int *buffer, int length);
void cycle_shift(int *buff1, int *buff2, int length, int shift);

int main() {
    int length, shift, buff1[SIZE], buff2[SIZE];
    if (input(buff1, &length, &shift) == -1) {
        printf("n/a");
        return -1;
    }
    cycle_shift(buff1, buff2, length, shift);
    output(buff2, length);
}

int input(int *buffer, int *length, int *shift) {
    char del;
    if (scanf("%d%c", &(*length), &del) != 2 || del != '\n' || *length > SIZE || *length < 1) {
        return -1;
    }
    for (int i = 0; i < *length; i++) {
        if (i == (*length - 1)) {
            if (scanf("%d%c", &buffer[i], &del) != 2 || del != '\n') {
                return -1;
            }
        } else {
            if (scanf("%d%c", &buffer[i], &del) != 2 || del != ' ') {
                return -1;
            }
        }
    }
    if (scanf("%d%c", &(*shift), &del) != 2 || del != '\n' || *length > SIZE || *length < 1) {
        return -1;
    }
    return 0;
}

void output(int *buffer, int length) {
    for (int i = 0; i < length; i++) {
        if (i == (length - 1)) {
            printf("%d", buffer[i]);
        } else {
            printf("%d ", buffer[i]);
        }
    }
}

void cycle_shift(int *buff1, int *buff2, int length, int shift) {
    shift = shift % length;
    for (int i = 0; i < length; i++) {
        if (shift > 0) {
            if (i < shift) {
                buff2[length - (shift - i)] = buff1[i];
            } else {
                buff2[i - shift] = buff1[i];
            }
        } else if (shift < 0) {
            if (i - shift - 1 < SIZE + 1) {
                buff2[(i - shift) % length] = buff1[i];
            } else {
                buff2[i - shift] = buff1[i];
            }
        }
    }
}
