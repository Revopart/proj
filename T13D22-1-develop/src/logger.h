
#ifndef LOGGER_G
#define LOGGER_G
#include <stdio.h>
FILE* log_init(char* filename);
void logcat(FILE* log_file, char* message, char* level);
void log_close(FILE* log_file);

#endif
