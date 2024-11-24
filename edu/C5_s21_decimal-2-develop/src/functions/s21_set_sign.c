#include "../s21_decimal.h"

void s21_set_sign(s21_decimal *value, int sign) {
  int tmp = 0b11111111 & value->bits[3];
  unsigned short scale = s21_get_scale(*value);
  value->bits[3] = ((unsigned)sign << 31) | (scale << 16);
  value->bits[3] |= tmp;
}