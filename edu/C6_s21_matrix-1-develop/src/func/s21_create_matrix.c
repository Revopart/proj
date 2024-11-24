#include "../s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res = 0;
  if ((!result) || (rows < 1) || (columns < 1))
    res = 1;
  else {
    result->matrix = (double **)malloc(sizeof(double *) * rows);
    result->rows = rows;
    result->columns = columns;
    for (int i = 0; i < rows; i++)
      result->matrix[i] = malloc(sizeof(double) * columns);
  }
  return res;
}