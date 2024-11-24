#include <stdlib.h>

#include "../s21_string.h"

int is_trim_char(char c, const char *trim_chars) {
  while (*trim_chars != '\0') {
    if (*trim_chars == c) {
      return 1;
    }
    trim_chars++;
  }
  return 0;
}

void *s21_trim(const char *src, const char *trim_chars) {
  if (src == NULL || trim_chars == NULL) {
    return NULL;
  }
  size_t src_length = s21_strlen(src);
  char *result = (char *)malloc((src_length + 1) * sizeof(char));
  if (result == NULL) {
    return NULL;
  }
  size_t index = 0;
  for (size_t i = 0; i < src_length; ++i) {
    if (!is_trim_char(src[i], trim_chars)) {
      result[index++] = src[i];
    }
  }
  result[index] = '\0';

  return (void *)result;
}