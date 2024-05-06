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
  int result = (!A || !B || (A->rows != B->rows) || (A->columns != B->columns)) ? FAILURE : SUCCESS;
    for (int i = 0; result == SUCCESS && i < A->rows; i++) {
      for (int j = 0; result == SUCCESS && j < A->columns; j++) {
        result = fabs(A->matrix[i][j] - B->matrix[i][j]) < S21_PRECISION ? SUCCESS : FAILURE;
      }
    }
  return result;
}


// int s21_eq_matrix(matrix_t *A, matrix_t *B) {
//   int result = !s21_is_valid_matrix_midi(&A) ? SUCCESS : FAILURE;
//   if (result == SUCCESS) result = !s21_is_valid_matrix_midi(&B) ? SUCCESS : FAILURE;
//   if (result == SUCCESS) result = s21_eq_content(&A, &B) ? SUCCESS : FAILURE;
//   return result;
// }

