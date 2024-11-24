#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int scale = s21_get_scale(value);
  int res = 0;
  if (scale > 28 || result == NULL) {
    res = 1;
  } else {
    result->bits[0] = value.bits[0];
    result->bits[1] = value.bits[1];
    result->bits[2] = value.bits[2];
    result->bits[3] = value.bits[3];
    s21_set_sign(result, 1 - s21_get_sign(*result));
  }
  return res;
}