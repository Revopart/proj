#include "../s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int res = 0;
  if (s21_is_empty(A) == 0) {
    if (A->rows == A->columns) {
      double det = 0;
      s21_determinant(A, &det);
      if (fabs(det) > 1e-7) {
        matrix_t tempM1, tempM2;
        s21_calc_complements(A, &tempM1);
        s21_transpose(&tempM1, &tempM2);
        s21_remove_matrix(&tempM1);
        s21_mult_number(&tempM2, 1.0 / det, result);
        s21_remove_matrix(&tempM2);
      } else {
        res = 2;
      }
    } else {
      res = 2;
    }
  } else {
    res = 1;
  }

  return res;
}
