#include "../s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *last = NULL;
  if (str) last = str;
  if (last == NULL || *last == '\0') return NULL;
  char *c = last;

  while (*c && s21_strchr(delim, *c)) c++;
  if (*c == '\0') {
    last = NULL;
    return NULL;
  }

  char *start = c;

  while (*c && !s21_strchr(delim, *c)) c++;
  if (*c == '\0') {
    last = c;
  } else {
    *c = '\0';
    last = c + 1;
  }

  return start;
}