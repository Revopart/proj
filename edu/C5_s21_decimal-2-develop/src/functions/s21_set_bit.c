#include "../s21_decimal.h"

unsigned int s21_set_bit(unsigned int number, int id, int bit) {
  if (id < 0 || id > 31) {
    perror("Wrong id in set_bit");
    return -1;
  }

  if (bit != 0 && bit != 1) {
    perror("Wrong bit in set_bit");
    return -1;
  }

  int setter = 1;
  setter = setter << id;

  if (bit == 1) number |= setter;
  if (bit == 0) number &= ~setter;

  return number;
}