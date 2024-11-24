#include <stdlib.h>

#include "../s21_string.h"
char custom_toupper(char c) {
  if (c >= 'a' && c <= 'z') {
    return c - ('a' - 'A');
  }
  return c;
}

void* s21_to_upper(const char* str) {
  if (str == NULL) {
    return NULL;
  }
  size_t length = s21_strlen(str);
  char* upper_str = (char*)malloc((length + 1) * sizeof(char));
  if (upper_str == NULL) {
    return NULL;
  }
  for (size_t i = 0; i < length; ++i) {
    upper_str[i] = custom_toupper(str[i]);
  }
  upper_str[length] = '\0';
  return (void*)upper_str;
}