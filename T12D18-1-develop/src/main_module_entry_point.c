#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "documentation_module.h"
#include "print_module.h"

int main() {
#ifdef FIRST
    time_t mytime = time(NULL);
    struct tm *now = localtime(&mytime);
    char str[10];
    strftime(str, sizeof(str), "%T", now);
    char result[100] = "";
    strcat(result, Log_prefix);
    strcat(result, " ");
    strcat(result, str);
    strcat(result, " ");

    strcat(result, Module_load_success_message);
    print_log(print_char, result);
#endif
#ifdef SECOND
    char *Documents[15] = {"Linked lists", "Queues", "Maps", "Binary Trees"};
    int *availability_mask = check_available_documentation_module(validate, Documents_count, Documents);
    for (int i = 0; i < Documents_count; i++) {
        if (i != Documents_count - 1) {
            if (availability_mask[i] == 1) {
                printf("%s: available\n", Documents[i]);
            } else {
                printf("%s: unavailable\n", Documents[i]);
            }
        } else {
            if (availability_mask[i] == 1) {
                printf("%s: available", Documents[i]);
            } else {
                printf("%s: unavailable", Documents[i]);
            }
        }
    }
    free(availability_mask);
#endif
    return 0;
}
