#include "../s21_string.h"

char *s21_strncat(char *dest, const char *src, size_t n) {
  char *d = dest;
  const char *s = src;
  if (d != NULL) {
    size_t length = s21_strlen(d);
    for (size_t i = length; i < length + n; ++i) {
      d[i] = s[i - length];
    }
  }
  return dest;
}
