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
  int err_code = OK;
  if (valid_matrix(A)) {
    if (A->rows == A->columns) {
      *result = 0.0;
      err_code = get_determinant(A, result);
    } else {
      err_code = CALCULATION_ERROR;
    }
  } else {
    err_code = INCORRECT_MATRIX;
  }

  return err_code;
}

