#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int res = 0;
  if (result) {
    s21_big_decimal tmp = s21_decimal_to_big_decimal(value);
    int scale = s21_get_scale_big(tmp);
    bool sign = s21_get_sign_big(tmp);
    s21_big_decimal ten = BIG_DEC_TEN;
    if (scale > 0) {
      for (int i = 1; i < scale; i++) s21_mul_ten_big(&ten);
      s21_big_decimal remainder = s21_mantissa_div_big(tmp, ten, &tmp);
      s21_shift_right_big(&ten, 1);
      int comparison = s21_mantissa_comparison(remainder, ten);
      if (comparison == 0) {  // остаток == 5
        // банковское округление
        s21_big_decimal remainder_2 =
            s21_mantissa_div_big(tmp, BIG_DEC_TEN, NULL);
        int digit = remainder_2.bits[0];
        if (digit % 2 != 0) {
          s21_mantissa_add_big(tmp, BIG_DEC_ONE, &tmp);
        }
      } else if (comparison == -1) {  // остаток > 5
        s21_mantissa_add_big(tmp, BIG_DEC_ONE, &tmp);
      }
      s21_set_sign_big(&tmp, sign);
      *result = s21_big_decimal_to_decimal(tmp);
    } else {
      *result = value;
    }
  } else {
    res = 1;
  }
  return res;
}