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

  if (err_code == OK) err_code = (fabs(det - 0.0) <= S21_PRECISION) ? err_code = CALCULATION_ERROR : OK;
  if (err_code == OK) {
    matrix_t complement_matrix = {0}, transponse_complement_matrix = {0};
    if (s21_calc_complements(A, &complement_matrix) == OK) {
      err_code = s21_transpose(&complement_matrix, &transponse_complement_matrix);
      s21_remove_matrix(&complement_matrix);
      if (err_code == OK) {
        err_code = s21_mult_number(&transponse_complement_matrix, 1.0 / det, result);
        s21_remove_matrix(&transponse_complement_matrix);
      }
    }
  }


  return err_code;
}










// int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
//   double determinant = 0;
//   int err_code = s21_is_valid_result_ptr(result);
//   if (err_code == OK) err_code = s21_is_valid_matrix_full(A);
//   if (err_code == OK) err_code = s21_squar_size(A);
//   if (err_code == OK) err_code = s21_determinant(A, &determinant);
//   if (err_code == OK && determinant == 0) err_code = CALCULATION_ERROR;
//   if (err_code == OK) {
//     if (A->rows == 1) {
//       err_code = s21_create_matrix(1, 1, result);
//       if (err_code == OK) result->matrix[0][0] = 1 / A->matrix[0][0];
//     } else {
//       matrix_t complements = {0};
//       matrix_t transposed_complements = {0};
//       err_code = s21_calc_complements(A, &complements);
//       if (err_code == OK) err_code = s21_transpose(&complements, &transposed_complements);
//       if (err_code == OK) err_code = s21_mult_number(&transposed_complements, 1 / determinant, result);
//       if (err_code == OK) s21_remove_matrix(&complements);
//       if (err_code == OK) s21_remove_matrix(&transposed_complements);
//     }
//   }
//   return err_code;
// }