#include "../s21_matrix.h"

double s21_get_determinant(matrix_t *A) {
  double res = 0;
  if (A->rows == 1) {
    res = A->matrix[0][0];
  } else {
    matrix_t tmp;
    s21_create_matrix(A->rows - 1, A->columns - 1, &tmp);
    for (int i = 0; i < A->columns; i++) {
      s21_get_calc(0, i, A, &tmp);
      if (i % 2) {
        res -= A->matrix[0][i] * s21_get_determinant(&tmp);
      } else {
        res += A->matrix[0][i] * s21_get_determinant(&tmp);
      }
    }
    s21_remove_matrix(&tmp);
  }

  return res;
}

void s21_get_calc(int row, int col, matrix_t *A, matrix_t *result) {
  int a_row = 0;
  int a_col;
  for (int i = 0; i < A->rows; i++) {
    if (i == row) {
      continue;
    }
    a_col = 0;
    for (int j = 0; j < A->columns; j++) {
      if (j == col) {
        continue;
      }
      result->matrix[a_row][a_col] = A->matrix[i][j];
      a_col++;
    }
    a_row++;
  }
}