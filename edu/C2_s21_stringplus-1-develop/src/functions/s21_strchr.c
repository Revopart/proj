#include "../s21_string.h"

char *s21_strchr(const char *str, int c) {
  char *found_element_pointer = NULL;

  const char *p = str;

  if (p != NULL) {
    for (size_t i = 0; found_element_pointer == NULL && i <= s21_strlen(p);
         ++i) {
      if (p[i] == c) found_element_pointer = (char *)&(p[i]);
    }
  }

  return found_element_pointer;
}