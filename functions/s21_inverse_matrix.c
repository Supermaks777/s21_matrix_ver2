#include "../s21_matrix.h"
/**
 * @brief инвертирует матрицу
 *
 * @param A первая матрица (matrix_t)
 * @param result результирующая матрица (matrix_t)
 * @return код ошибки (int)
 * @retval 0 - OK.
 * @retval 1 - INCORRECT_MATRIX.
 * @retval 2 - CALCULATION_ERROR.
 */
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int err_code = OK;
  double det = 0.0;
  err_code = s21_determinant(A, &det);

  if (err_code == OK)
    err_code = (fabs(det - 0.0) <= S21_PRECISION) ? CALCULATION_ERROR : OK;
  if (err_code == OK) {
    matrix_t complement_matrix = {0}, transponse_complement_matrix = {0};
    if (s21_calc_complements(A, &complement_matrix) == OK) {
      err_code =
          s21_transpose(&complement_matrix, &transponse_complement_matrix);
      s21_remove_matrix(&complement_matrix);
      if (err_code == OK) {
        err_code =
            s21_mult_number(&transponse_complement_matrix, 1.0 / det, result);
        s21_remove_matrix(&transponse_complement_matrix);
      }
    }
  }

  return err_code;
}
