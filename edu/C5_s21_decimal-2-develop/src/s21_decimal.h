#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H
#include <stdbool.h>
#include <stdio.h>

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[8];
} s21_big_decimal;

#define DECIMAL_MAX                           \
  (s21_decimal) {                             \
    { 0xffffffff, 0xffffffff, 0xffffffff, 0 } \
  }
#define DECIMAL_MIN                                   \
  (s21_decimal) {                                     \
    { 0xffffffff, 0xffffffff, 0xffffffff, 0b1 << 31 } \
  }
#define DECIMAL_ZERO \
  (s21_decimal) {    \
    { 0, 0, 0, 0 }   \
  }
#define BIG_DEC_TEN             \
  (s21_big_decimal) {           \
    { 10, 0, 0, 0, 0, 0, 0, 0 } \
  }
#define BIG_DEC_FIVE           \
  (s21_big_decimal) {          \
    { 5, 0, 0, 0, 0, 0, 0, 0 } \
  }
#define BIG_DEC_TWO            \
  (s21_big_decimal) {          \
    { 2, 0, 0, 0, 0, 0, 0, 0 } \
  }
#define BIG_DEC_ONE            \
  (s21_big_decimal) {          \
    { 1, 0, 0, 0, 0, 0, 0, 0 } \
  }

#define MAX_FLOAT 79228162514264337593543950335.f
#define MIN_FLOAT 1.e-28

typedef enum { OK, PLUS_INF, NEG_INF, ZERO } code_error;

// support functions
unsigned int s21_get_bit(unsigned int number, int id);
unsigned int s21_set_bit(unsigned int number, int id, int bit);
int s21_get_sign(s21_decimal value);
void s21_set_sign(s21_decimal *value, int sign);

// big dec support
s21_big_decimal s21_decimal_to_big_decimal(s21_decimal dec);
s21_decimal s21_big_decimal_to_decimal(s21_big_decimal dec);
void s21_shift_left_big(s21_big_decimal *decimal, unsigned shift);
void s21_shift_right_big(s21_big_decimal *decimal, unsigned shift);
bool s21_get_bit_big(s21_big_decimal decimal, unsigned index);
void s21_set_bit_big(s21_big_decimal *decimal, unsigned index, bool bit);
bool s21_get_sign_big(s21_big_decimal decimal);
void s21_set_sign_big(s21_big_decimal *decimal, bool sign);
int s21_get_scale_big(s21_big_decimal decimal);
void s21_set_scale_big(s21_big_decimal *decimal, unsigned scale);
int s21_mantissa_comparison(s21_big_decimal value_1, s21_big_decimal value_2);
void s21_normalization(s21_big_decimal *value_1, s21_big_decimal *value_2);
int s21_is_zero_big(s21_big_decimal value);
int s21_over_mantissa(s21_big_decimal value);
void s21_reduction_of_the_mantissa(s21_big_decimal *value);
int s21_over_mantissa(s21_big_decimal value);
void s21_reduction_of_the_mantissa(s21_big_decimal *value);
void s21_delete_zero_big(s21_big_decimal *value);
void s21_mul_ten_big(s21_big_decimal *value);
void s21_mantissa_add_big(s21_big_decimal value_1, s21_big_decimal value_2,
                          s21_big_decimal *result);
s21_big_decimal s21_mantissa_div_big(s21_big_decimal value_1,
                                     s21_big_decimal value_2,
                                     s21_big_decimal *result);
void s21_mantissa_sub_big(s21_big_decimal value_1, s21_big_decimal value_2,
                          s21_big_decimal *result);
void s21_mantissa_mul_big(s21_big_decimal value_1, s21_big_decimal value_2,
                          s21_big_decimal *result);
code_error s21_checking_res(s21_big_decimal res);

int s21_get_scale(s21_decimal decimal);
s21_decimal s21_set_scale(s21_decimal decimal, int scale);
s21_decimal s21_scale_by_ten(s21_decimal decimal, char scale_type, int scale,
                             int *error_status);

s21_decimal s21_bit_shift(s21_decimal decimal, int shift, char direction,
                          int *error_status);

// Arithmetic operators
s21_decimal s21_base_add(s21_decimal value_1, s21_decimal value_2,
                         int *error_status);
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

s21_decimal s21_base_sub(s21_decimal value_1, s21_decimal value_2,
                         int *error_status);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Comparison operators
int base_compare(s21_decimal first, s21_decimal second);
int s21_is_less(s21_decimal first, s21_decimal second);
int s21_is_less_or_equal(s21_decimal first, s21_decimal second);
int s21_is_greater(s21_decimal first, s21_decimal second);
int s21_is_greater_or_equal(s21_decimal first, s21_decimal second);
int s21_is_equal(s21_decimal first, s21_decimal second);
int s21_is_not_equal(s21_decimal first, s21_decimal second);

// Converters
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// Other functions
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

void print_decimal(s21_decimal *decimal);

#endif