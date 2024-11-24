#include "../s21_decimal.h"

int s21_get_sign(s21_decimal value) {
  return s21_get_bit(value.bits[3], 32 - 1);
}