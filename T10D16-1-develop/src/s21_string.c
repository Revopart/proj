#include "s21_string.h"

#include <stdio.h>
#include <stdlib.h>

int s21_strlen(const char *a) {
    int lenght;
    int step = 0;
    if (a == NULL) {
        lenght = -1;
    } else {
        while (a[step] != '\0') {
            step++;
        }
        lenght = step;
    }
    return lenght;
}

int s21_strcmp(const char *a, const char *b) {
    int result = 0;
    if (s21_strlen(a) > s21_strlen(b)) {
        result = 1;
    } else if (s21_strlen(a) < s21_strlen(b)) {
        result = -1;
    } else {
        for (int i = 0; i < s21_strlen(a); i++) {
            if (a[i] > b[i]) {
                result = 1;
                break;
            } else if (a[i] > b[i]) {
                result = -1;
                break;
            }
        }
    }
    return result;
}

char *s21_strcpy(const char *a, char *b) {
    char *result;
    if (a == NULL) {
        result = NULL;
        b = NULL;
    } else {
        int lenght = s21_strlen(a);
        for (int i = 0; i < lenght; i++) {
            b[i] = a[i];
        }
        b[lenght] = '\0';
        result = b;
    }
    return result;
}

char *s21_strcat(char *a, const char *b) {
    int size = s21_strlen(a);
    for (int i = 0; i < s21_strlen(b); i++) {
        a[size + i] = b[i];
    }
    return a;
}

char *s21_strchr(char *a, int b) {
    int size = s21_strlen(a);
    char *result = NULL;
    for (int i = 0; i < size; i++) {
        if (a[i] == b) {
            result = &(a[i]);
            break;
        }
    }
    return result;
}

char *s21_strstr(char *a, char *b) {
    char *result = NULL;
    int size_a = s21_strlen(a);
    int size_b = s21_strlen(b);
    if (a == NULL || b == NULL) {
        result = NULL;
    } else if (size_b > size_a || size_b == 0) {
        result = NULL;
    } else {
        int flag = 0;
        for (int i = 0; i < size_a; i++) {
            for (int j = 0; j < size_b; j++) {
                if (a[i] == b[j]) {
                    flag++;
                    for (int k = 1; k < size_b + 1; k++) {
                        if (flag == size_b) {
                            result = &(a[i]);
                        } else if (i + k == size_a || j + k == size_b) {
                            flag = 0;
                            break;
                        } else {
                            if (a[i + k] == b[j + k]) {
                                flag++;
                            } else {
                                flag = 0;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    return result;
}

char *s21_strtok(char *a, char *b) {
    int size_a = s21_strlen(a);
    int size_b = s21_strlen(b);
    char *result = NULL;

    if (a != NULL || b != NULL) {
        for (int i = 0; i < size_a; i++) {
            for (int j = 0; j < size_b; i++) {
                if (a[i] == b[j]) {
                    a[i] = '\0';
                    break;
                }
            }
        }
        result = a;
    }
    return result;
}
