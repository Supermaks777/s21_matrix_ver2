#include "../s21_matrix.h"
/**
 * @brief вычитает матрицы
 *
 * @param A первая матрица (matrix_t)
 * @param B вторая матрица (matrix_t)
 * @param result результирующая матрица (matrix_t)
 * @return код ошибки (int)
 * @retval 0 - OK.
 * @retval 1 - INCORRECT_MATRIX.
 * @retval 2 - CALCULATION_ERROR.
 */
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  double sub = 0.0;
  int err_code = s21_is_valid_result_ptr(result);
  if (err_code == OK) err_code = s21_is_valid_matrix_full(A);
  if (err_code == OK) err_code = s21_is_valid_matrix_full(B);
  if (err_code == OK) err_code = s21_eq_size(A, B);
  if (err_code == OK) err_code = s21_create_matrix(A->rows, A->columns, result);
  if (err_code == OK) {
    for (int i = 0; err_code == OK && i < A->rows; i++) {
      for (int j = 0; err_code == OK && j < A->columns; j++) {
        sub = A->matrix[i][j] - B->matrix[i][j];
        err_code = s21_is_valid_element(sub);
        if (err_code == 0) result->matrix[i][j] = sub;
      }
    }
  }
  return err_code;
}