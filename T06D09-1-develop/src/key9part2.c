#include <stdio.h>

#define LEN 100

void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);
int sub(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);
int input(int *buff1, int *len1, int *buff2, int *len2);
void output(int *buffer, int start, int length);


int main()
{
    int buff1[LEN], buff2[LEN], result[LEN+1];
    for (int i = 0; i < LEN; i++) {
        buff1[i] = 0;
        buff2[i] = 0;
        result[i] = 0;
    }
    result[LEN] = 0;
    int len1, len2, result_length;
    if (input(buff1, &len1, buff2, &len2) == -1) {
        printf("n/a");
        return -1;
    }

    sum(buff1, len1, buff2, len2, result, &result_length);
    if (sub(buff1, len1, buff2, len2, result, &result_length) == -1) {
        printf("n/a");
        return -1;
    }
    }


int input(int *buff1, int *len1, int *buff2, int *len2) {
    char del;
    for (int i = 0; i < LEN; i++) {
        int scan = scanf("%d%c", &buff1[i], &del);
        if (scan != 2 || buff1[i] > 9 || buff1[i] < 0) {
            return -1;
        }
        if (i != LEN - 1) {
            if (del == '\n') {
                *len1 = i+1;
                break;
            }
            if (del != ' ') {
                return -1;
            }
        }
        else {
            if (del != '\n') {
                return -1;
            }
        }
    }
    for (int i = 0; i < *len1; i++) {
        buff1[LEN-(*len1-i)] = buff1[i];
        buff1[i] = 0;
    }
    for (int i = 0; i < LEN; i++) {
        int scan = scanf("%d%c", &buff2[i], &del);
        if (scan != 2 || buff2[i] > 9 || buff2[i] < 0) {
            return -1;
        }
        if (i != LEN-1) {
            if (del == '\n') {
                *len2 = i+1;
                break;
            }
            if (del != ' ') {
                return -1;
            }
        }
        else {
            if (del != '\n') {
                return -1;
            }
        }
    }
    for (int i = 0; i < *len2; i++) {
        buff2[LEN-(*len2-i)] = buff2[i];
        buff2[i] = 0;
    }
    return 0;
}

void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length){
    for (int i = LEN-1; i > 0; i--) {
        result[i+1] += buff1[i] + buff2[i];
        if (result[i+1] > 9) {
            result[i]++;
            result[i+1] = result[i+1]  % 10;
        }
        if ((LEN - i ) > (len1-1) && (LEN - i) > (len2 - 1)) {
            *result_length = i;
            break;
        }
    }

        int status = 0;
    for (int i = *result_length ; i < LEN + 1; i++) {
        if (result[i] != 0 ) {
            status = 1;
        }
        if (status == 1 && i != LEN) {
            printf("%d ", result[i]);
        }
        else if (status == 1 && i == LEN) {
            printf("%d\n", result[i]);
        }
    }
}

int sub(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length) {
    if (len1 < len2) {
        return -1;
    }
    if (len1 == len2) {
        int c = 0;
        for (int i = *result_length; i < LEN; i++) {
            if (buff1[i] < buff2[i] && c == 0) {
                return -1;
            }
            else if (buff1[i] > buff2[i]) {
                c = 1;
            }
        }
    }
    for (int i = LEN-1; i > 0; i--) {
        result[i+1] = buff1[i] - buff2[i];
        if (result[i+1] < 0) {
            buff1[i-1] = buff1[i-1] - 1;
            result[i+1] = result[i+1]  + 10;
        }
        if ((LEN - i ) > (len1-1) && (LEN - i) > (len2 - 1)) {
            *result_length = i;
            break;
        }
    }

    int status = 0;
    for (int i = *result_length ; i < LEN + 1; i++) {
        if (result[i] != 0 ) {
            status = 1;
        }
        if (status == 1 && i != LEN) {
            printf("%d ", result[i]);
        }
        else if (status == 1 && i == LEN) {
            printf("%d", result[i]);
        }
    }
    return 0;
}


