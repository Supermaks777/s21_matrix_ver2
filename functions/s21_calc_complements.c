#include "../s21_matrix.h"

/**
 * @brief формирует матрицу алгебраических дополнений
 *
 * @param A исходная матрица (matrix_t)
 * @param result результирующая матрица (matrix_t)
 * @return код ошибки (int)
 * @retval 0 - OK.
 * @retval 1 - INCORRECT_MATRIX.
 * @retval 2 - CALCULATION_ERROR.
 */
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int err_code = OK;

  if (!valid_matrix(A))
    err_code = INCORRECT_MATRIX;
  else if (A->rows != A->columns)
    err_code = CALCULATION_ERROR;
  else {
    err_code = s21_create_matrix(A->rows, A->columns, result);
    if (err_code == OK && A->rows == 1 && A->columns == 1)
      result->matrix[0][0] = 1;
    else if (err_code == OK)
      err_code = get_calc_complements(A, result);
  }
  return err_code;
}