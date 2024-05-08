#include "../s21_matrix.h"

/**
 * @brief сравнивает две матрицы
 *
 * @param A первая матрица (matrix_t)
 * @param B вторая матрица (matrix_t)
 * @param result результат (double)
 * @return результат сравнения (int)
 * @retval 0 - FAILURE.
 * @retval 1 - SUCCESS.
 */
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = (valid_matrix(A) && valid_matrix(B) && valid_eq_matrixes(A, B))
                   ? SUCCESS
                   : FAILURE;
  for (int i = 0; result == SUCCESS && i < A->rows; i++) {
    for (int j = 0; result == SUCCESS && j < A->columns; j++) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) >= S21_PRECISION)
        result = FAILURE;
    }
  }
  return result;
}
