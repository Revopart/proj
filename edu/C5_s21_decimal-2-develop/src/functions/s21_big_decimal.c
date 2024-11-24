#include "../s21_decimal.h"

s21_big_decimal s21_decimal_to_big_decimal(s21_decimal dec) {
  s21_big_decimal tmp = {0};
  tmp.bits[7] = dec.bits[3];
  for (int i = 0; i < 3; i++) tmp.bits[i] = dec.bits[i];
  return tmp;
}

s21_decimal s21_big_decimal_to_decimal(s21_big_decimal dec) {
  s21_decimal tmp = {0};
  tmp.bits[3] = dec.bits[7];
  for (int i = 0; i < 3; i++) tmp.bits[i] = dec.bits[i];
  return tmp;
}

bool s21_get_bit_big(s21_big_decimal decimal, unsigned index) {
  int i = index / 32;
  index %= 32;
  return (decimal.bits[i]) & (1U << index);
}

void s21_set_bit_big(s21_big_decimal *decimal, unsigned index, bool bit) {
  int i = index / 32;
  index %= 32;
  if (bit == 0) {
    decimal->bits[i] &= ~(1 << index);
  } else {
    decimal->bits[i] |= (1 << index);
  }
}

bool s21_get_sign_big(s21_big_decimal decimal) {
  return s21_get_bit_big(decimal, 32 * 8 - 1);
}

void s21_set_sign_big(s21_big_decimal *decimal, bool sign) {
  int scale = s21_get_scale_big(*decimal);
  decimal->bits[7] = (sign << 31) | (scale << 16);
}

int s21_get_scale_big(s21_big_decimal decimal) {
  int res = ((decimal.bits[7] >> 16) & 0b11111111);
  return res;
}

void s21_set_scale_big(s21_big_decimal *decimal, unsigned scale) {
  bool sign = s21_get_sign_big(*decimal);
  decimal->bits[7] = (sign << 31) | (scale << 16);
}

void s21_shift_left_big(s21_big_decimal *decimal, unsigned shift) {
  unsigned buffer[7] = {0};
  for (unsigned k = 0; k < shift; k++) {
    for (int i = 0; i < 6; i++) {
      buffer[i] = s21_get_bit_big(*decimal, (i + 1) * 32 - 1);
    }
    for (int i = 0; i <= 6; i++) {
      decimal->bits[i] <<= 1;
      if (i) s21_set_bit_big(decimal, i * 32, buffer[i - 1]);
    }
  }
}

void s21_shift_right_big(s21_big_decimal *decimal, unsigned shift) {
  int buffer[7] = {0};
  for (unsigned k = 0; k < shift; k++) {
    for (int i = 0; i <= 6; i++) {
      buffer[i] = s21_get_bit_big(*decimal, (i + 1) * 32);
    }
    for (int i = 0; i <= 6; i++) {
      decimal->bits[i] >>= 1;
      s21_set_bit_big(decimal, (i + 1) * 32 - 1, buffer[i]);
    }
  }
}

void s21_mul_ten_big(s21_big_decimal *value) {
  s21_big_decimal shifted_1 = *value;
  s21_big_decimal shifted_3 = *value;
  s21_shift_left_big(&shifted_1, 1);
  s21_shift_left_big(&shifted_3, 3);
  s21_mantissa_add_big(shifted_1, shifted_3, value);
}

// -1 v1 > v2
//  0 v1 == v2
//  1 v1 < v2
int s21_mantissa_comparison(s21_big_decimal value_1, s21_big_decimal value_2) {
  int res = 0;
  for (int i = 32 * 7 - 1; i >= 0; i--) {
    bool bit1 = s21_get_bit_big(value_1, i);
    bool bit2 = s21_get_bit_big(value_2, i);
    if (bit1 > bit2) {
      res = -1;
    } else if (bit1 < bit2) {
      res = 1;
    }
    if (res) break;
  }
  return res;
}

void s21_normalization(s21_big_decimal *value_1, s21_big_decimal *value_2) {
  s21_big_decimal *max_val =
      (s21_get_scale_big(*value_1) >= s21_get_scale_big(*value_2)) ? value_1
                                                                   : value_2;
  s21_big_decimal *min_val =
      (s21_get_scale_big(*value_1) < s21_get_scale_big(*value_2)) ? value_1
                                                                  : value_2;
  int scale_max = s21_get_scale_big(*max_val);
  int scale_min = s21_get_scale_big(*min_val);
  while (scale_max > 28 || scale_min > 28) {
    if (scale_max > 28) {
      bool sign = s21_get_sign_big(*max_val);
      s21_mantissa_div_big(*max_val, BIG_DEC_TEN, max_val);
      s21_set_scale_big(max_val, --scale_max);
      s21_set_sign_big(max_val, sign);
    }
    if (scale_min > 28) {
      bool sign = s21_get_sign_big(*min_val);
      s21_mantissa_div_big(*min_val, BIG_DEC_TEN, min_val);
      s21_set_scale_big(min_val, --scale_min);
      s21_set_sign_big(min_val, sign);
    }
  }
  while (scale_max - scale_min) {
    bool sign = s21_get_sign_big(*min_val);
    s21_mul_ten_big(min_val);
    s21_set_scale_big(min_val, ++scale_min);
    s21_set_sign_big(min_val, sign);
  }
}

int s21_is_zero_big(s21_big_decimal value) {
  int res = 1;
  for (int i = 32 * 7 - 1; i >= 0; i--) {
    if (s21_get_bit_big(value, i) == 1) {
      res = 0;
      break;
    }
  }
  return res;
}

// проверка на переполнение мантиссы
int s21_over_mantissa(s21_big_decimal value) {
  int res = 0;
  for (int i = 7 * 32 - 1; i >= 3 * 32; i--) {
    if (s21_get_bit_big(value, i)) {
      res = 1;
      break;
    }
  }
  return res;
}

// сокращение мантиссы
void s21_reduction_of_the_mantissa(s21_big_decimal *value) {
  int scale = s21_get_scale_big(*value);
  bool sign = s21_get_sign_big(*value);
  while (scale > 0 && (s21_over_mantissa(*value) || scale > 28)) {
    scale--;
    s21_big_decimal remainder =
        s21_mantissa_div_big(*value, BIG_DEC_TEN, value);
    if (!s21_over_mantissa(*value) && scale <= 28) {
      if (s21_mantissa_comparison(remainder, BIG_DEC_FIVE) == 0) {
        s21_big_decimal remainder_tmp =
            s21_mantissa_div_big(*value, BIG_DEC_TEN, NULL);
        s21_big_decimal remainder_tmp_2 =
            s21_mantissa_div_big(remainder_tmp, BIG_DEC_TWO, NULL);
        if (!s21_is_zero_big(remainder_tmp_2)) {
          s21_mantissa_add_big(*value, BIG_DEC_ONE, value);
        }
      } else if (s21_mantissa_comparison(remainder, BIG_DEC_FIVE) == -1) {
        s21_mantissa_add_big(*value, BIG_DEC_ONE, value);
      }
    }
    s21_set_sign_big(value, sign);
    s21_set_scale_big(value, scale);
  }
}

// удаление коненчных нулей
void s21_delete_zero_big(s21_big_decimal *value) {
  int scale = s21_get_scale_big(*value);
  bool sign = s21_get_sign_big(*value);
  s21_big_decimal remainder = s21_mantissa_div_big(*value, BIG_DEC_TEN, NULL);
  while (s21_is_zero_big(remainder) && (scale > 0)) {
    s21_mantissa_div_big(*value, BIG_DEC_TEN, value);
    remainder = s21_mantissa_div_big(*value, BIG_DEC_TEN, NULL);
    scale--;
  }
  s21_set_scale_big(value, scale);
  s21_set_sign_big(value, sign);
}

code_error s21_checking_res(s21_big_decimal res) {
  code_error result = OK;
  bool sign = s21_get_sign_big(res);
  for (int i = 7 * 32 - 1; i >= 32 * 3; i--) {
    if (s21_get_bit_big(res, i)) {
      if (sign == 0) {
        result = PLUS_INF;
      } else {
        result = NEG_INF;
      }
    }
  }
  return result;
}

void s21_mantissa_add_big(s21_big_decimal value_1, s21_big_decimal value_2,
                          s21_big_decimal *result) {
  s21_big_decimal res = {0};
  int in_mind = 0;
  for (int i = 0; i < 32 * 7; i++) {
    int bit_val1 = s21_get_bit_big(value_1, i);
    int bit_val2 = s21_get_bit_big(value_2, i);
    s21_set_bit_big(&res, i, (bit_val1 + bit_val2 + in_mind) % 2);
    in_mind = (bit_val1 + bit_val2 + in_mind) / 2;
  }
  for (int i = 0; i <= 6; i++) {
    result->bits[i] = res.bits[i];
  }
}

void s21_mantissa_sub_big(s21_big_decimal value_1, s21_big_decimal value_2,
                          s21_big_decimal *result) {
  s21_big_decimal tmp = {0};
  for (int index = 0; index < 32 * 7; index++) {
    int bit_1 = s21_get_bit_big(value_1, index);
    int bit_2 = s21_get_bit_big(value_2, index);
    int res_bit = 0;
    if (bit_1 - bit_2 >= 0) {
      res_bit = bit_1 - bit_2;
    } else {
      res_bit = 1;
      int step = 0;
      while (!s21_get_bit_big(value_1, index + step)) {
        s21_set_bit_big(&value_1, index + step, 1);
        step++;
      }
      s21_set_bit_big(&value_1, index + step, 0);
    }
    s21_set_bit_big(&tmp, index, res_bit);
  }
  *result = tmp;
}

s21_big_decimal s21_mantissa_div_big(s21_big_decimal value_1,
                                     s21_big_decimal value_2,
                                     s21_big_decimal *result) {
  int count = 0;
  s21_big_decimal tmp = {0};
  while (s21_mantissa_comparison(value_1, value_2) < 0) {
    s21_shift_left_big(&value_2, 1);
    count++;
    int comparison = s21_mantissa_comparison(value_1, value_2);
    if (comparison >= 0) {
      if (comparison > 0) s21_shift_right_big(&value_2, 1);
      count--;
      break;
    }
  }
  if (s21_mantissa_comparison(value_1, value_2) <= 0) {
    for (int i = count; i >= 0; i--) {
      if (s21_mantissa_comparison(value_1, value_2) <= 0) {
        s21_mantissa_sub_big(value_1, value_2, &value_1);
        s21_set_bit_big(&tmp, i, 1);
      }
      s21_shift_right_big(&value_2, 1);
    }
  }
  if (result != NULL) *result = tmp;
  return value_1;
}

void s21_mantissa_mul_big(s21_big_decimal value_1, s21_big_decimal value_2,
                          s21_big_decimal *result) {
  s21_big_decimal tmp = {0};
  for (int i = 0; i < 32 * 7 - 1; i++) {
    if (s21_get_bit_big(value_2, i) == 1) {
      s21_mantissa_add_big(tmp, value_1, &tmp);
    }
    s21_shift_left_big(&value_1, 1);
  }
  *result = tmp;
}