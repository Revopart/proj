#include <math.h>
#include <stdio.h>

void char_to_number() {
    char ch = 'a';
    char del = 'k';
    while (del != '\n') {
        if (scanf("%c%c", &ch, &del) != 2 || ch == ' ') {
            printf("n/a\n");
            break;
        } else {
            if (del == ' ') {
                printf("%X ", ch);
            } else if (del == '\n') {
                printf("%X\n", ch);
                break;
            } else {
                printf("n/a\n");
                break;
            }
        }
    }
}

void number_to_char() {
    int a = 1;
    char del = 'k';
    while (del != '\n') {
        if (scanf("%hhX%c", &a, &del) != 2) {
            printf("n/a\n");
            break;
        } else {
            if (del == ' ') {
                printf("%c ", a);
            } else if (del == '\n') {
                printf("%c\n", a);
                break;
            } else {
                printf("n/a\n");
                break;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (*argv[1] == '0') {
        char_to_number();
    } else if (*argv[1] == '1') {
        number_to_char();
    } else {
        printf("n/a\n");
    }
}
