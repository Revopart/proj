#include "../s21_string.h"

void *s21_memset(void *str, int c, size_t n) {
  if (str == NULL) {
    return NULL;
  }
  unsigned char *temp_str = (unsigned char *)str;
  for (size_t i = 0; i < n; i++) {
    temp_str[i] = (unsigned char)c;
  }
  return str;
}