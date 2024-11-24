#include "../s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res = 0;
  if (s21_is_empty(A) == 0) {
    if (A->rows == A->columns) {
      s21_create_matrix(A->columns, A->rows, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          matrix_t calc;
          double determinant = 0;
          s21_create_matrix(A->columns - 1, A->rows - 1, &calc);
          s21_get_calc(i, j, A, &calc);
          s21_determinant(&calc, &determinant);
          result->matrix[i][j] = pow(-1, (i + j)) * determinant;
          s21_remove_matrix(&calc);
        }
      }
    } else {
      res = 2;
    }
  } else {
    res = 1;
  }
  return res;
}