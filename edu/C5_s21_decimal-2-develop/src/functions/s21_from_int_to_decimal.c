//
// Created by leco100 on 05.06.2024.
//
#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  if (dst == NULL) return 1;

  for (int i = 0; i < 4; ++i) {
    dst->bits[i] = 0;
  }
  if (src < 0) {
    src *= -1;
    dst->bits[3] = s21_set_bit(dst->bits[3], 31, 1);
  }
  dst->bits[0] = (unsigned int)src;
  return 0;
}