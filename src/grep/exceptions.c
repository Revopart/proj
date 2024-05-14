#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void reportFileError(char* filename, bool shouldExit) {
  fprintf(stderr, "%s: ", "./s21_grep");
  perror(filename);
  if (shouldExit) exit(1);
}

void reportRegexError(void) {
  fprintf(stderr, "failed to compile regex\n");
  exit(1);
}
