#include "stek.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *input() {
    char *string = (char *)malloc(sizeof(char));
    string[0] = '\0';
    char ch;
    size_t count = 0;

    while (scanf("%c", &ch) == 1 && ch != '\n' && ch != EOF) {
        char *tmp = realloc(string, (count + 2) * sizeof(char));

        string = tmp;
        string[count] = ch;
        string[count + 1] = '\0';
        count++;
    }

    return string;
}

char *push(char ch, char *string) {
    if (string == NULL) {
        string = malloc(2 * sizeof(char));
    }

    size_t len = string ? strlen(string) : 0;
    char *tmp = realloc(string, (len + 2) * sizeof(char));
    if (tmp == NULL) {
        printf("error realloc input");
    }
    string = tmp;
    string[len] = ch;
    string[len + 1] = '\0';
    return string;
}

char pull(char *string) {
    size_t len = string ? strlen(string) : 0;

    char ch = string[len - 1];
    string[len - 1] = '\0';
    return ch;
}

double *push_double(double num, double *array, int *size) {
    *size = *size + 1;
    double *tmp = realloc(array, *size * sizeof(double));
    if (tmp == NULL) {
        printf("erroe realloc push double\n");
        return array;
    }
    tmp[*size - 1] = num;

    return tmp;
}

double pull_double(double *array, int *size) {
    double num = 0;
    if (*size > 0) {
        num = array[*size - 1];
        *size = *size - 1;
    }
    return num;
}
