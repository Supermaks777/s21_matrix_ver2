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

  if (!valid_matrix(A)) err_code = INCORRECT_MATRIX;
  else if (A->rows != A->columns) err_code = CALCULATION_ERROR;
  else {
    err_code = s21_create_matrix(A->rows, A->columns, result);
    if (err_code == OK && A->rows == 1 && A->columns == 1) result->matrix[0][0] = 1;
    else if (err_code == OK) err_code = get_calc_complements(A, result);
  }
  return err_code;
}

//alg_adds_matrix_calc
int get_calc_complements(matrix_t *A, matrix_t *result) {
  int err_code = OK;
  matrix_t minor_ij = {0};

  err_code = s21_create_matrix(A->rows - 1, A->columns - 1, &minor_ij);
  for (int i = 0; i < A->rows && err_code == OK; i++) {
    for (int j = 0; j < A->columns && err_code == OK; j++) {
      double determinant = 0.0;
      calc_minor_matrix(A, i, j, &minor_ij);
      err_code = calc_minor_determinant(&minor_ij, &determinant);

      if (err_code == OK) result->matrix[i][j] = pow(-1.0, i + j) * determinant;
    }
  }
  s21_remove_matrix(&minor_ij);
  return err_code;
}

// int s21_calc_complements(matrix_t *A, matrix_t *result) {
//   double value;
//   int err_code = s21_is_valid_result_ptr(result);
//   if (err_code == OK) err_code = s21_is_valid_matrix_full(A);
//   if (err_code == OK) err_code = s21_squar_size(A);
//   if (err_code == OK) err_code = s21_create_matrix(A->rows, A->columns, result);
//   if (err_code == OK) {
//     if (A->rows == 1) result->matrix[0][0] = 1;
//     else
//       for (int i = 0; i < A->rows && err_code == OK; i++) {
//         for (int j = 0; j < A->columns && err_code == OK; j++) {
//           err_code = s21_get_minor(A, i, j, &value);
//           if (err_code == OK) result->matrix[i][j] = value * pow(-1, i + j);
//         }
//       }
//   }
//   return err_code;
// }
