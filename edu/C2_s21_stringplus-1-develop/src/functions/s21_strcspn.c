#include "../s21_string.h"

size_t s21_strcspn(const char *str1, const char *str2) {
  size_t found_element_index = 0;
  size_t found_status = 0;

  const char *p1 = str1;
  const char *p2 = str2;

  for (size_t i = 0; found_status == 0 && i < s21_strlen(p1); ++i) {
    for (size_t j = 0; found_status == 0 && j < s21_strlen(p2); ++j) {
      if (p1[i] == p2[j]) {
        found_element_index = i;
        found_status = 1;
      }
    }
  }

  if (found_status == 0) found_element_index = s21_strlen(p1);

  return found_element_index;
}