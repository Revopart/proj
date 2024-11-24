#include "../s21_string.h"

void *s21_memchr(const void *str, int c, size_t n) {
  const unsigned char *address_first_occurrence = NULL;

  for (const unsigned char *i = (const unsigned char *)str;
       address_first_occurrence == NULL && i < (const unsigned char *)str + n;
       ++i) {
    if (*i == c) address_first_occurrence = i;
  }

  return (void *)address_first_occurrence;
}