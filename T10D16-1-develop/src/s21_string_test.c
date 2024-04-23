#include "s21_string.h"

#include <stdio.h>

void s21_strlen_test();
void s21_strcmp_test();
void s21_strcpy_test();
void s21_strcat_test();
void s21_strchr_test();
void s21_strstr_test();
void s21_strtok_test();

int main() {
#ifdef S21_STRLEN_TEST
    s21_strlen_test();
#endif
#ifdef S21_STRCMP_TEST
    s21_strcmp_test();
#endif
#ifdef S21_STRCPY_TEST
    s21_strcpy_test();
#endif
#ifdef S21_STRCAT_TEST
    s21_strcat_test();
#endif
#ifdef S21_STRCHR_TEST
    s21_strchr_test();
#endif
#ifdef S21_STRSTR_TEST
    s21_strstr_test();
#endif
#ifdef S21_STRTOK_TEST
    s21_strtok_test();
#endif
}

void s21_strlen_test() {
    const char *a[3] = {NULL, "", "asd"};
    if (s21_strlen(a[0]) == -1) {
        printf("NULL %d SUCCESS\n", s21_strlen(a[0]));
    } else {
        printf("NULL %d FAIL\n", s21_strlen(a[0]));
    }
    if (s21_strlen(a[1]) == 0) {
        printf(
            ""
            " %d SUCCESS\n",
            s21_strlen(a[1]));
    } else {
        printf(
            ""
            " %d FAIL\n",
            s21_strlen(a[1]));
    }
    if (s21_strlen(a[2]) == 3) {
        printf("asd %d SUCCESS", s21_strlen(a[2]));
    } else {
        printf("asd %d FAIL", s21_strlen(a[3]));
    }
}

void s21_strcmp_test() {
    if (s21_strcmp("abc", "abc") == 0) {
        printf("abc, abc %d SUCCESS\n", s21_strcmp("abc", "abc"));
    } else {
        printf("abc, abc %d FAIL\n", s21_strcmp("abc", "abc"));
    }
    if (s21_strcmp("a", "") == 1) {
        printf("a,  %d SUCCESS\n", s21_strcmp("a", ""));
    } else {
        printf("a,  %d FAIL\n", s21_strcmp("abc", "ab"));
    }
    if (s21_strcmp(NULL, "abc") == -1) {
        printf("NULL, abc %d SUCCESS", s21_strcmp(NULL, "abc"));
    } else {
        printf("NULL, abc %d FAIL", s21_strcmp(NULL, "abc"));
    }
}

void s21_strcpy_test() {
    const char *a[3] = {"", "1", "asd"};
    char b[1024];
    for (int i = 0; i < 3; i++) {
        s21_strcpy(a[i], b);
        if (i != 2) {
            if (s21_strcmp(a[i], b) == 0) {
                printf("%s %s SUCCESS\n", a[i], b);
            } else {
                printf("%s %s FAIL\n", a[i], b);
            }
        } else {
            if (s21_strcmp(a[i], b) == 0) {
                printf("%s %s SUCCESS", a[i], b);
            } else {
                printf("%s %s FAIL", a[i], b);
            }
        }
    }
}

void s21_strcat_test() {
    char a[1024] = "123";
    const char *b[3] = {"456", "543", ""};
    s21_strcat(a, b[0]);
    if (s21_strcmp(a, "123456") == 0) {
        printf("123, 456 %s SUCCESS\n", a);
    } else {
        printf("123, 456 %s FAIL\n", a);
    }
    s21_strcat(a, b[1]);
    if (s21_strcmp(a, "123456543") == 0) {
        printf("123, 543 %s SUCCESS\n", a);
    } else {
        printf("123, 543 %s FAIL\n", a);
    }
    s21_strcat(a, b[2]);
    if (s21_strcmp(a, "123456543") == 0) {
        printf("123, 321 %s SUCCESS", a);
    } else {
        printf("123, 321 %s FAIL", a);
    }
}

void s21_strchr_test() {
    char a[1024] = "123";
    int b[3] = {'1', '2', '4'};
    if (s21_strchr(a, b[0]) == &a[0]) {
        printf("%s %d %c SUCCESS\n", a, b[0], a[0]);
    } else {
        printf("%s %d %c FAIL\n", a, b[0], a[0]);
    }
    if (s21_strchr(a, b[1]) == &a[1]) {
        printf("%s %d %c SUCCESS\n", a, b[1], a[1]);
    } else {
        printf("%s %d %c FAIL\n", a, b[1], a[1]);
    }
    if (s21_strchr(a, b[2]) == NULL) {
        printf("%s %d NULL SUCCESS", a, b[2]);
    } else {
        printf("%s %c NULL FAIL", a, b[2]);
    }
}

void s21_strstr_test() {
    char a[1024] = "12345678";
    char b[10] = "23";
    char d[10] = "456";
    char c[10] = "4789";
    if (s21_strstr(a, b)) {
        printf("%s %s %c SUCCESS\n", a, b, a[1]);
    } else {
        printf("%s %s %c FAIL\n", a, b, a[1]);
    }
    if (s21_strstr(a, d) == &a[3]) {
        printf("%s %s %c SUCCESS\n", a, d, a[3]);
    } else {
        printf("%s %s %c FAIL\n", a, d, a[3]);
    }
    if (s21_strstr(a, c) == NULL) {
        printf("%s %s NULL SUCCESS", a, c);
    } else {
        printf("%s %s NULL FAIL", a, c);
    }
}

void s21_strtok_test() {
    char a[1024] = "12,34.56 78";
    char b[10] = ",";
    s21_strtok(a, b);
    if (s21_strcmp(a, "12") == 0) {
        printf("12,34.56 78 %s %s SUCCESS\n", b, a);
    } else {
        printf("12,34.56 78 %s %s FAIL\n", b, a);
    }
    char a2[1024] = "12,34.56 78";
    char b2[10] = " ";
    s21_strtok(a2, b2);
    printf("%s\n", a2);
    if (s21_strcmp(a2, "12,34.56") == 0) {
        printf("12,34.56 78  %s SUCCESS\n", a2);
    } else {
        printf("12,34.56 78  %s FAIL\n", a2);
    }
    char a3[1024] = "";
    char b3[10] = ",";
    s21_strtok(a3, b3);
    if (s21_strcmp(a3, "") == 0) {
        printf("   %s SUCCESS", a3);
    } else {
        printf("   %s FAIL", a3);
    }
}
