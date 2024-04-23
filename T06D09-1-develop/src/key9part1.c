
#include <stdio.h>
#define SIZE 10

int input(int *buffer, int *length);
void output(int *buffer, int length);
int sum_numbers(int *buffer, int length);
int find_numbers(int *buffer, int length, int *number, int *numbers);
int is_even(int a);

int main() {
    int length, buffer[SIZE];
    if (input(buffer, &length) == -1) {
        printf("n/a");
        return -1;
    }
    int number = 0, numbers[length];
    if (find_numbers(buffer, length, &number, numbers) == -1) {
        printf("n/a");
        return -1;
    } else if (number == 0) {
        printf("n/a");
        return -1;
    } else {
        output(numbers, number);
        return 0;
    }
}

int find_numbers(int *buffer, int length, int *number, int *numbers) {
    int sum = sum_numbers(buffer, length);
    if (sum == 0) {
        return -1;
    }
    for (int i = 0; i < length; i++) {
        if (buffer[i] != 0 && sum % buffer[i] == 0) {
            numbers[*number] = buffer[i];
            *number = *number + 1;
        }
    }
    printf("%d\n", sum);
    return 0;
}

int is_even(int a) {
    if (a != 0 && (a % 2 == 1 || a % 2 == -1)) {
        return 0;
    } else {
        return 1;
    }
}

int input(int *buffer, int *length) {
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
int sum_numbers(int *buffer, int length) {
    int status = 0;
    int sum = 0;
    for (int i = 0; i < length; i++) {
        if (is_even(buffer[i]) == 1) {
            sum += buffer[i];
            status = 1;
        }
    }
    if (status == 1) {
        return sum;
    } else {
        return 0;
    }
}
