#include <stdlib.h>

#include "../s21_string.h"

void* s21_insert(const char* src, const char* str, size_t start_index) {
  if (src == NULL || str == NULL) {
    return NULL;
  }
  size_t src_length = s21_strlen(src);
  size_t str_length = s21_strlen(str);

  if (start_index > src_length) {
    return NULL;
  }

  char* result = (char*)malloc((src_length + str_length + 1) * sizeof(char));
  if (result == NULL) {
    return NULL;
  }
  for (size_t i = 0; i < start_index; ++i) {
    result[i] = src[i];
  }
  for (size_t i = 0; i < str_length; ++i) {
    result[start_index + i] = str[i];
  }
  for (size_t i = start_index; i <= src_length; ++i) {
    result[start_index + str_length + i] = src[i];
  }

  return (void*)result;
}