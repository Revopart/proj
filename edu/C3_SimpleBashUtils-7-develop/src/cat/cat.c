#include "cat.h"

#include <string.h>

void print_error_message() { printf("Error"); }
void print_without_flag(FILE *f) {
  int c = fgetc(f);
  while (c != EOF) {
    putc(c, stdout);
    c = fgetc(f);
  }
}
void print_b(FILE *f) {
  int i = 1;
  char line[256];
  while (fgets(line, sizeof(line), f) != NULL) {
    if (line[0] != '\n') {
      printf("%6d\t%s", i, line);
      i++;
    } else {
      printf("%s", line);
    }
  }
}
void print_e(FILE *f) {
  int c = fgetc(f);

  while (c != EOF) {
    putNotDisplayedSymbol(&c);
    if (c == '\n') {
      putchar('$');
    }
    putchar(c);
    c = fgetc(f);
  }
}
void print_n(FILE *f) {
  int i = 1;
  char line[256];
  while (fgets(line, sizeof(line), f) != NULL) {
    printf("%6d\t%s", i, line);
    i++;
  }
}
void print_s(FILE *f) {
  int status = 1;
  char line[256];
  while (fgets(line, sizeof(line), f) != NULL) {
    if (strcmp(line, "\n") == 0) {
      if (status) {
        printf("%s", line);
        status = 0;
      }
    } else {
      printf("%s", line);
      status = 1;
    }
  }
}
void print_t(FILE *f) {
  int c = fgetc(f);
  while (c != EOF) {
    putNotDisplayedSymbol(&c);
    if (c == '\t') {
      putc('^', stdout);
      putc('I', stdout);
    } else {
      putc(c, stdout);
    }
    c = fgetc(f);
  }
}

void print_v(FILE *f) {
  int c = fgetc(f);

  while (c != EOF) {
    putNotDisplayedSymbol(&c);
    putc(c, stdout);
    c = fgetc(f);
  }
}

void print_file(char *file_name, char flag) {
  FILE *f = fopen(file_name, "rt");
  if (f != NULL) {
    if (flag == ' ') {
      print_without_flag(f);
    } else if (flag == 'b') {
      print_b(f);
    } else if (flag == 'e') {
      print_e(f);
    } else if (flag == 'n') {
      print_n(f);
    } else if (flag == 's') {
      print_s(f);
    } else if (flag == 'v') {
      print_v(f);
    } else if (flag == 't') {
      print_t(f);
    } else {
      print_error_message();
    }
    fclose(f);
  } else {
    print_error_message();
  }
}
void putNotDisplayedSymbol(int *c) {
  if (*c == '\n' || *c == '\t') {
    ;

  } else if (*c <= 31) {
    putc('^', stdout);
    *c += 64;

  } else if (*c == 127) {
    putc('^', stdout);
    *c = '?';

  } else if (*c >= 128 && *c < 128 + 32) {
    printf("M-^");
    *c -= 64;
  }
}