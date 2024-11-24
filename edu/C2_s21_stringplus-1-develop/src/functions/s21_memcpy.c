#include "../s21_string.h"

void *s21_memcpy(void *dest, const void *src, size_t n) {
  char *d = dest;
  const char *s = src;
  for (size_t i = 0; i < n; i++) {
    d[i] = s[i];
  }
  return dest;
}