#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "polish.h"

#define PI 3.141593
#define ROWS 25
#define COLS 80

char *input();

char *push(char ch, char *string);
char pull(char *string);

double *push_double(double num, double *array, int *size);
double pull_double(double *array, int *size);

int output(char *string);

int main() {
    int flag = 0;

    char *string = input();

    flag = normalize(string);
    if (flag == 0) {
        char *polish = normal_to_pol(string);
        flag = output(polish);
        free(polish);
    }

    if (flag != 0) printf("n/a");
    free(string);

    return 0;
}

int output(char *string) {
    int flag = 0;

    char tab[ROWS][COLS] = {};
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            tab[i][j] = '.';
        }
    }

    double x = 0;
    for (int j = 0; j < COLS; j++) {
        double res = pol_to_res(string, x);

        if (res != NAN) {
            res = round((res + 1.0) * (ROWS - 1.0) / 2.0);
            int res_i = (int)res;

            if (res_i >= 0 && res_i < ROWS) {
                tab[res_i][j] = '*';
            }

            x += (4 * PI) / (double)COLS;
        } else
            flag = 1;
    }

    if (flag == 0) {
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                if (j + 1 >= COLS) {
                    printf("%c\n", tab[i][j]);
                } else
                    printf("%c", tab[i][j]);
            }
        }
    }
    return flag;
}
