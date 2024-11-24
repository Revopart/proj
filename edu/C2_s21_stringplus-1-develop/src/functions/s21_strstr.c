#include "../s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  char *found_element_pointer = NULL;
  int found_status = 0;

  const char *p1 = haystack;
  const char *p2 = needle;

  for (size_t i = 0; found_status == 0 && i < s21_strlen(p1); ++i) {
    if (p1[i] == p2[0]) found_status = 1;
    for (size_t j = 0; found_status == 1 && j < s21_strlen(p2); ++j) {
      if (p1[i + j] != p2[j]) {
        found_status = 0;
      }
    }
    if (found_status == 1) found_element_pointer = (char *)&(p1[i]);
  }

  return s21_strlen(p2) == 0 ? (char *)p1 : found_element_pointer;
}