#include "print_module.h"

#include <stdio.h>
#include <string.h>

char print_char(char ch) { return putchar(ch); }

void print_log(char (*print)(char), char *message) {
    for (size_t i = 0; i < strlen(message); i++) {
        print(message[i]);
    }
}
