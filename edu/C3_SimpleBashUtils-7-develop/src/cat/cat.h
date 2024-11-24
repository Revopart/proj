#ifndef CAT_H

#define CAT_H
#include <stdio.h>
void print_error_message();
void print_file(char *file_name, char flag);
void print_without_flag(FILE *f);
void print_b(FILE *f);
void print_e(FILE *f);
void print_n(FILE *f);
void print_s(FILE *f);
void print_t(FILE *f);
void print_v(FILE *f);
void putNotDisplayedSymbol(int *c);

#endif