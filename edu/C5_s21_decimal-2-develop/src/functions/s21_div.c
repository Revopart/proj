#include "../s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  code_error res = OK;
  for (int i = 0; i < 4; i++) result->bits[i] = 0;
  s21_big_decimal tmp_res = {0};
  s21_big_decimal v1 = s21_decimal_to_big_decimal(value_1);
  s21_big_decimal v2 = s21_decimal_to_big_decimal(value_2);
  if (s21_is_zero_big(v2)) {
    res = ZERO;
  } else {
    bool sign_1 = s21_get_sign_big(v1);
    bool sign_2 = s21_get_sign_big(v2);
    bool sign_res = (sign_1 ^ sign_2) ? 1 : 0;
    int scale_1 = s21_get_scale_big(v1);
    int scale_2 = s21_get_scale_big(v2);
    int scale_res = scale_1 - scale_2;
    v1 = s21_mantissa_div_big(v1, v2, &tmp_res);
    while (!s21_is_zero_big(v1) && !s21_over_mantissa(tmp_res) &&
           scale_res <= 28) {
      s21_mul_ten_big(&v1);
      s21_mul_ten_big(&tmp_res);
      s21_big_decimal tmp_div = {0};
      v1 = s21_mantissa_div_big(v1, v2, &tmp_div);
      s21_mantissa_add_big(tmp_res, tmp_div, &tmp_res);
      scale_res++;
    }
    while (scale_res < 0) {
      s21_mul_ten_big(&tmp_res);
      scale_res++;
    }
    s21_set_scale_big(&tmp_res, scale_res);
    s21_set_sign_big(&tmp_res, sign_res);
    s21_reduction_of_the_mantissa(&tmp_res);
    s21_delete_zero_big(&tmp_res);
    res = s21_checking_res(tmp_res);
    if (res == OK) *result = s21_big_decimal_to_decimal(tmp_res);
  }
  return res;
}