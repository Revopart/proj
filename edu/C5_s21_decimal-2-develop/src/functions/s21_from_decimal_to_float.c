//
// Created by leco100 on 05.06.2024.
//

#include <math.h>

#include "../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  if (dst == NULL) return 1;
  *dst = 1.0f;
  int sign = s21_get_sign(src);

  unsigned int scale = s21_get_scale(src);

  unsigned int value = src.bits[0];

  float result = (float)value;
  if (scale > 0) {
    result /= pow(10, scale);
  }

  if (src.bits[1] != 0 || src.bits[2] != 0) {
    return 1;
  }

  if (sign == 1) {
    result *= -1;
  }
  *dst = result;
  return 0;
}