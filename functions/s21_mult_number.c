#include "../s21_matrix.h"
/**
 * @brief умножение матрицы на число
 *
 * @param A матрица (matrix_t)
 * @param number число (double)
 * @param result результирующая матрица (matrix_t)
 * @return код ошибки (int)
 * @retval 0 - OK.
 * @retval 1 - INCORRECT_MATRIX.
 * @retval 2 - CALCULATION_ERROR.
 */
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  double mult = 0.0;
  int err_code = s21_is_valid_result_ptr(result);
  if (err_code == OK) err_code = s21_is_valid_matrix_full(A);
  if (err_code == OK) err_code = s21_is_valid_element(number);
  if (err_code == OK) err_code = s21_create_matrix(A->rows, A->columns, result);
  if (err_code == OK) {
    for (int i = 0; err_code == OK && i < A->rows; i++) {
      for (int j = 0; err_code == OK && j < A->columns; j++) {
        mult = A->matrix[i][j] * number;
        err_code = s21_is_valid_element(mult);
        if (err_code == 0) result->matrix[i][j] = mult;
      }
    }
  }
  return err_code;
}
