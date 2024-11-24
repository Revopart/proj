#include "../s21_decimal.h"

int base_compare(s21_decimal first, s21_decimal second) {
  int res = 0;
  s21_big_decimal first_big = s21_decimal_to_big_decimal(first);
  s21_big_decimal second_big = s21_decimal_to_big_decimal(second);
  s21_normalization(&first_big, &second_big);
  bool sign1 = s21_get_sign_big(first_big);
  bool sign2 = s21_get_sign_big(second_big);
  if (s21_is_zero_big(first_big) && s21_is_zero_big(second_big)) {
    res = 0;
  } else if (sign1 != sign2) {
    if (sign1 == 0) {
      res = 1;
    } else {
      res = -1;
    }
  } else {
    int temp_res = s21_mantissa_comparison(first_big, second_big);
    if (sign1 == 0) {
      if (temp_res == 0) {
        res = 0;
      } else if (temp_res < 0) {
        res = 1;
      } else {
        res = -1;
      }
    } else {
      if (temp_res == 0) {
        res = 0;
      } else if (temp_res < 0) {
        res = -1;
      } else {
        res = 1;
      }
    }
  }
  return res;
}

int s21_is_less(s21_decimal first, s21_decimal second) {
  int res = 0;
  int temp_res = base_compare(first, second);
  if (temp_res == -1) {
    res = 1;
  } else {
    res = 0;
  }
  return res;
}

int s21_is_less_or_equal(s21_decimal first, s21_decimal second) {
  int res = 0;
  int temp_res = base_compare(first, second);
  if (temp_res != 1) {
    res = 1;
  } else {
    res = 0;
  }
  return res;
}
int s21_is_greater(s21_decimal first, s21_decimal second) {
  int res = 0;
  int temp_res = base_compare(first, second);
  if (temp_res == 1) {
    res = 1;
  } else {
    res = 0;
  }
  return res;
}
int s21_is_greater_or_equal(s21_decimal first, s21_decimal second) {
  int res = 0;
  int temp_res = base_compare(first, second);
  if (temp_res != -1) {
    res = 1;
  } else {
    res = 0;
  }
  return res;
}
int s21_is_equal(s21_decimal first, s21_decimal second) {
  int res = 0;
  int temp_res = base_compare(first, second);
  if (temp_res == 0) {
    res = 1;
  } else {
    res = 0;
  }
  return res;
}
int s21_is_not_equal(s21_decimal first, s21_decimal second) {
  return !s21_is_equal(first, second);
}
