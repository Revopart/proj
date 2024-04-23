#include "polish.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "stek.h"

int normalize(char *string) {
    int flag = 0;
    size_t j = 0;
    int count_open = 0;
    int count_close = 0;
    for (size_t i = 0; i < strlen(string); i++) {
        if (string[j] == 'x' || (string[j] >= '0' && string[j] <= '9') || string[j] == '+' ||
            string[j] == '*' || string[j] == '/' || string[j] == '(' || string[j] == ')' ||
            string[j] == '.') {
            string[i] = string[j];
            if (string[j] == '(') count_open++;
            if (string[j] == ')') count_close++;
            j++;
        } else if (string[j] == '-') {
            if (j == 0) {
                string[i] = '~';
            } else if (string[j - 1] == '*' || string[j - 1] == '/' || string[j - 1] == '(') {
                string[i] = '~';
            } else
                string[i] = '-';
            j++;
        } else if ((string[j] == 's' && string[j + 1] == 'i' && string[j + 2] == 'n') ||
                   (string[j] == 'c' && string[j + 1] == 'o' && string[j + 2] == 's') ||
                   (string[j] == 't' && string[j + 1] == 'a' && string[j + 2] == 'n')) {
            string[i] = string[j];
            j += 3;
        } else if (string[j] == 'c' && string[j + 1] == 't' && string[j + 2] == 'g') {
            string[i] = 'g';
            j += 3;
        } else if (string[j] == 's' && string[j + 1] == 'q' && string[j + 2] == 'r' && string[j + 3] == 't') {
            string[i] = 'q';
            j += 4;
        } else if (string[j] == 'l' && string[j + 1] == 'n') {
            string[i] = 'l';
            j += 2;
        } else {
            flag = 1;
        }

        if (j >= strlen(string)) {
            string[i + 1] = '\0';
            if (!((string[i] >= '0' && string[i] <= '9') || string[i] == ')' || string[i] == 'x') ||
                (count_close != count_open)) {
                flag = 1;
            }
            break;
        }
    }
    return flag;
}

int priority(char ch) {
    int pri = 0;

    switch (ch) {
        case '(':
        case ')':
            pri = 1;
            break;
        case '+':
        case '-':
            pri = 2;
            break;
        case '*':
        case '/':
            pri = 3;
            break;
        case '~':
            pri = 4;
            break;
        case 's':
        case 'c':
        case 't':
        case 'g':
        case 'q':
        case 'l':
            pri = 5;
            break;
        default:
            pri = -1;
    }

    return pri;
}

char *normal_to_pol(char *string) {
    char *stek = NULL;
    char *stek_res = NULL;
    size_t len_string = string ? strlen(string) : 0;
    stek = malloc(2 * sizeof(char));
    stek[0] = '\0';
    stek_res = malloc(2 * sizeof(char));
    stek_res[0] = '\0';

    for (size_t i = 0; i < len_string; ++i) {
        if ((string[i] >= '0' && string[i] <= '9') || string[i] == 'x' || string[i] == '.') {
            stek_res = push(string[i], stek_res);
            if (i + 1 < len_string) {
                if (!(((string[i + 1] >= '0') && (string[i + 1] <= '9')) || (string[i + 1] == '.'))) {
                    stek_res = push(' ', stek_res);
                }
            }
        } else if (strlen(stek) == 0) {
            stek = push(string[i], stek);
        } else if (string[i] == '(') {
            stek = push(string[i], stek);
        } else if (string[i] == ')') {
            while (stek[strlen(stek) - 1] != '(') {
                stek_res = push(pull(stek), stek_res);
                stek_res = push(' ', stek_res);
            }
            pull(stek);
        } else {
            while (strlen(stek) != 0 && priority(string[i]) <= priority(stek[strlen(stek) - 1])) {
                stek_res = push(pull(stek), stek_res);
                stek_res = push(' ', stek_res);
            }
            stek = push(string[i], stek);
        }
    }
    stek_res = push(' ', stek_res);
    while (strlen(stek) != 0) {
        stek_res = push(pull(stek), stek_res);
        stek_res = push(' ', stek_res);
    }
    free(stek);
    return stek_res;
}

double pol_to_res(char *string, double x) {
    double res = 0;
    double *stek = NULL;
    int size = 0;
    double num1 = 0.0;
    double num2 = 0.0;
    int len_string = string ? strlen(string) : 0;

    stek = malloc(sizeof(double));

    for (int i = 0; i < len_string; ++i) {
        if (string[i] == ' ') continue;

        if (string[i] >= '0' && string[i] <= '9') {
            double number = (double)string[i] - '0';
            i++;
            while (string[i] != '.' && string[i] != ' ') {
                number = number * 10.0 + (double)string[i] - '0';
                i++;
            }
            // 1 printf("%lf", number);
            int count = 1;
            while (string[i] != ' ') {
                if (string[i] == '.') i++;
                double kef = 1.0 / (pow(10.0, (double)count));
                number = number + (((double)string[i] - '0') * kef);
                i++;
                count++;
            }

            stek = push_double(number, stek, &size);
        } else if (string[i] == 'x') {
            res = x;
            stek = push_double(res, stek, &size);
        } else {
            num1 = pull_double(stek, &size);
            if (string[i] == '+' || string[i] == '-' || string[i] == '*' || string[i] == '/') {
                num2 = pull_double(stek, &size);
            }

            switch (string[i]) {
                case '+':
                    res = num2 + num1;
                    break;
                case '-':
                    res = num2 - num1;
                    break;
                case '*':
                    res = num2 * num1;
                    break;
                case '/':
                    res = num2 / num1;
                    break;
                case '~':
                    res = -num1;
                    break;
                case 's':
                    res = sin(num1);
                    break;
                case 'c':
                    res = cos(num1);
                    break;
                case 't':
                    res = tan(num1);
                    break;
                case 'g':
                    res = 1 / tan(num1);
                    break;
                case 'q':
                    res = sqrt(num1);
                    break;
                case 'l':
                    res = log(num1);
                    break;
                default:
                    res = NAN;
            }
            stek = push_double(res, stek, &size);
        }
    }

    res = pull_double(stek, &size);
    free(stek);
    return size == 0 ? res : NAN;
}
