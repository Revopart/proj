//
// Created by leco100 on 05.06.2024.
//
#include <math.h>

#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (dst == NULL) return 1;

  *dst = 0;

  int is_negative = (src.bits[3] >> 31) & 1;
  unsigned int scale = s21_get_scale(src);
  unsigned int value = src.bits[0];

  if (scale > 0) {
    if (scale >= 10) {
      value /= pow(10, scale);
    } else {
      value /= (unsigned int)pow(10, scale);
    }
  }

  if (src.bits[1] != 0 || src.bits[2] != 0) {
    return 1;
  }

  if (is_negative) {
    *dst = -(int)value;
  } else {
    *dst = (int)value;
  }

  return 0;
}