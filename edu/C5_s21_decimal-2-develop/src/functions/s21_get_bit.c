#include "../s21_decimal.h"

unsigned int s21_get_bit(unsigned int number, int id) {
  if (id < 0 || id > 31) {
    perror("Wrong id in get_bit");
    return -1;
  }

  int bit;
  unsigned int tester = 1;

  tester = tester << id;

  if ((number | tester) == number)
    bit = 1;
  else
    bit = 0;

  return bit;
}