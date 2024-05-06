#include "../s21_matrix.h"
/**
 * @brief расчитывает определитель квадратной матрицы
 *
 * @param A исходная матрица (matrix_t)
 * @param result результат (double)
 * @return код ошибки (int)
 * @retval 0 - OK.
 * @retval 1 - INCORRECT_MATRIX.
 * @retval 2 - CALCULATION_ERROR.
 */
int s21_determinant(matrix_t *A, double *result) {
  double res = 0.0;
  *result = 0.0;
  matrix_t temp = {0};
  int err_code = s21_is_valid_matrix_full(A);
  if (err_code == OK) err_code = s21_squar_size(A);
  if (err_code == OK) {
    if (A->rows == 1) res = A->matrix[0][0];
    else if (A->rows == 2) res = A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] * A->matrix[0][1];
    else {
      err_code = s21_copy_matrix(A, &temp);
      s21_gauss_elimination(&temp);
      res = s21_main_diagonal_multiple(&temp);
      if (err_code == OK) s21_remove_matrix(&temp);
    }
  }
  if (err_code == OK) err_code = s21_is_valid_element(res);
  if (err_code == OK) *result = res;
  return err_code;
}