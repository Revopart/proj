#include "../s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = 1;
  if (A->columns == B->columns && A->rows == B->rows && s21_is_empty(A) == 0 &&
      s21_is_empty(B) == 0) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) {
          res = 0;
          break;
        }
      }
    }
  } else {
    res = 0;
  }
  return res;
}