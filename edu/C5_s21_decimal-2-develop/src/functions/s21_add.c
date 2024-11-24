#include "../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  for (int i = 0; i < 4; i++) result->bits[i] = 0;
  s21_big_decimal tmp_res = {0};
  s21_big_decimal v1 = s21_decimal_to_big_decimal(value_1);
  s21_big_decimal v2 = s21_decimal_to_big_decimal(value_2);
  s21_normalization(&v1, &v2);
  bool sign_v1 = s21_get_sign_big(v1);
  bool sign_v2 = s21_get_sign_big(v2);
  bool sign_res = 0;
  int scale_res = 0;
  if (sign_v1 != sign_v2) {  // + -, - +
    const s21_big_decimal *max_mantissa =
        (s21_mantissa_comparison(v1, v2) <= 0) ? &v1 : &v2;
    const s21_big_decimal *min_mantissa =
        (s21_mantissa_comparison(v1, v2) <= 0) ? &v2 : &v1;
    bool max_sign = s21_get_sign_big(*max_mantissa);
    scale_res = s21_get_scale_big(*max_mantissa);
    if (s21_mantissa_comparison(*max_mantissa, *min_mantissa) == 0) {
      sign_res = 0;
      scale_res = 0;
    } else if (max_sign == 0) {
      sign_res = (max_mantissa == &v1) ? 0 : 1;
    } else {
      sign_res = (max_mantissa == &v1) ? 1 : 0;
    }
    s21_mantissa_sub_big(*max_mantissa, *min_mantissa, &tmp_res);
  } else {  // + +, - -
    scale_res = s21_get_scale_big(v1);
    if (sign_v1 == 1) sign_res = 1;
    s21_mantissa_add_big(v1, v2, &tmp_res);
  }
  s21_set_sign_big(&tmp_res, sign_res);
  s21_set_scale_big(&tmp_res, scale_res);
  s21_reduction_of_the_mantissa(&tmp_res);
  s21_delete_zero_big(&tmp_res);
  code_error res = s21_checking_res(tmp_res);
  if (res == OK) *result = s21_big_decimal_to_decimal(tmp_res);
  return res;
}