#include "../s21_decimal.h"

s21_decimal s21_set_scale(s21_decimal decimal, int scale) {
  int scale_cleaner = 255 << 16;

  decimal.bits[3] &= ~(scale_cleaner);
  decimal.bits[3] |= (scale << 16);

  return decimal;
}