#include "../s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char *result = NULL;
  while (*str != '\0') {
    if (*str == (unsigned char)c) {
      result = (char *)str;
    }
    str++;
  }
  if (*str == (unsigned char)c) {
    result = (char *)str;
  }
  return result;
}
