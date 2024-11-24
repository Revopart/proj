#include "../s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {  // вычисление определителя
  int res = 0;
  if (s21_is_empty(A) == 0) {
    if (A->rows == A->columns) {
      *result = s21_get_determinant(A);
    } else {
      res = 2;
    }
  } else {
    res = 1;
  }
  return res;
}