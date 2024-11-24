#include "../s21_string.h"

char *s21_strncpy(char *dest, const char *src, size_t n) {
  char *dest_start = dest;
  while (n && *src != '\0') {
    *dest = *src;
    dest++;
    src++;
    n--;
  }
  while (n--) {
    *dest = '\0';
    dest++;
  }
  return dest_start;
}