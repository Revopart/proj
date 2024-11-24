#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int res = 0;
  if (result) {
    s21_big_decimal tmp = s21_decimal_to_big_decimal(value);
    int scale = s21_get_scale_big(tmp);
    int sign = s21_get_sign(value);
    s21_big_decimal ten = BIG_DEC_TEN;
    for (int i = 0; i < scale; i++) {
      s21_mantissa_div_big(tmp, ten, &tmp);
    }
    s21_set_scale_big(&tmp, 0);

    // s21_mantissa_div_big(tmp, ten, &tmp);
    // s21_set_sign_big(&tmp, sign);
    *result = s21_big_decimal_to_decimal(tmp);
    s21_set_sign(result, sign);
  } else {
    res = 1;
  }
  return res;
}