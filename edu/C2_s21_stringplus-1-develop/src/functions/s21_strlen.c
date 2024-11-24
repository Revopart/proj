#include "../s21_string.h"

size_t s21_strlen(const char *str) {
  size_t counter = 0;
  while (*str != '\0') {
    counter++;
    str++;
  }
  return counter;
}