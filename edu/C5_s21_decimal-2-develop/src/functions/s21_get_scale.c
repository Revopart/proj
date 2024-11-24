#include "../s21_decimal.h"

int s21_get_scale(s21_decimal decimal) {
  int exponent = (decimal.bits[3] >> 16) & 0xFF;
  return exponent;
}