#include "../s21_matrix.h"
/**
 * @brief удаляет матрицу
 *
 * @param A матрица для удаления (matrix_t *)
 */
void s21_remove_matrix(matrix_t *A) {
  if (A != NULL) {
    if (A->matrix != NULL) {
      for (int i = 0; i < A->rows; i++)
        if (A->matrix[i]) free(A->matrix[i]);
      free(A->matrix);
      A->matrix = NULL;
    }
    A->rows = 0;
    A->columns = 0;
  }
}