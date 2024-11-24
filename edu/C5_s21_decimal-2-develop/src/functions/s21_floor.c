#include "../s21_decimal.h"
int s21_floor(s21_decimal value, s21_decimal *result) {
  int res = 0;
  if (result) {
    s21_truncate(value, result);
    if (s21_get_sign(value) && !s21_is_equal(*result, value)) {
      s21_sub(*result, (s21_decimal){{1, 0, 0, 0}}, result);
    }
  } else {
    res = 1;
  }
  return res;
}