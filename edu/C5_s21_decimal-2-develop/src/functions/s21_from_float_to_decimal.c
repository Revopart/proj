//
// Created by leco100 on 05.06.2024.
//
#include <math.h>
#include <string.h>

#include "../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  if (!dst) return 1;
  for (int i = 0; i < 4; ++i) {
    dst->bits[i] = 0;
  }
  char src_string[256] = {};
  int sign = 0;
  if (src < 0.0f) {
    sign = 1;
    src = fabs(src);
  }
  sprintf(src_string, "%e", src);

  printf("str :%s\n", src_string);

  int e_scale = 0;
  int position_of_e = strchr(src_string, 'e') - src_string + 2;

  for (unsigned long i = position_of_e; i < strlen(src_string); ++i) {
    e_scale = e_scale * 10 + (src_string[i] - '0');
  }
  if (strchr(src_string, '-') != NULL) e_scale *= -1;
  src_string[position_of_e - 2] = '\0';

  printf("e_scale :%d\n", e_scale);
  printf("str :%s\n", src_string);
  while (src_string[strlen(src_string) - 1] == '0') {
    src_string[strlen(src_string) - 1] = '\0';
  }
  int position_of_dot = strchr(src_string, '.') - src_string;
  int scale = strlen(src_string) - position_of_dot - 1;
  printf("scale :%d\n", scale);
  scale -= e_scale;
  printf("scale :%d\n", scale);
  int mantissa = 0;
  for (unsigned long i = 0; i < strlen(src_string); ++i) {
    if (src_string[i] != '.') mantissa = mantissa * 10 + (src_string[i] - '0');
  }

  s21_set_sign(dst, sign);
  *dst = s21_set_scale(*dst, scale);
  dst->bits[0] = mantissa;

  return 0;
}
