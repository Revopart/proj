#include "../s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  char *found_element_pointer = NULL;
  int found_status = 0;

  const char *p1 = str1;
  const char *p2 = str2;

  for (size_t i = 0; found_status == 0 && i < s21_strlen(p1); ++i) {
    for (size_t j = 0; found_status == 0 && j < s21_strlen(p2); ++j) {
      if (p1[i] == p2[j]) {
        found_element_pointer = (char *)&(p1[i]);
        found_status = 1;
      }
    }
  }

  return found_element_pointer;
}