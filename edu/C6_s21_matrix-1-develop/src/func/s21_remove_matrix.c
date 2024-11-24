#include "../s21_matrix.h"

void s21_remove_matrix(matrix_t *A) {
  if (s21_is_empty(A) == 0) {
    for (int i = 0; i < A->rows; i++) {
      free((A->matrix)[i]);
    }
    free(A->matrix);
  }
  if (A != NULL) {
    A->matrix = NULL;
    A->rows = 0;
    A->columns = 0;
  }
}