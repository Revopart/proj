#include "logger.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

#include "log_levels.h"

FILE* log_init(char* filename) {
    FILE* log_file;
    log_file = fopen(filename, "a");
    return log_file;
}
void logcat(FILE* log_file, char* message, char* level) {
    time_t mytime = time(NULL);
    struct tm* now = localtime(&mytime);
    char str[10];
    strftime(str, sizeof(str), "%T", now);
    char result[256] = "";
    strcat(result, level);
    strcat(result, " ");
    strcat(result, str);
    strcat(result, " ");
    strcat(result, message);
    strcat(result, "\n");
    fputs(result, log_file);
}
void log_close(FILE* log_file) { fclose(log_file); }
