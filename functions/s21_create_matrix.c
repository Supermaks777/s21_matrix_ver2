#include "../s21_matrix.h"

/**
 * @brief создает матрицу заданного размера (вариант rows+1 массивами)
 * валидация данных: result на существование, размеры матрицы на корректность,
 * выделение памяти под строки
 * @param rows количество строк (int)
 * @param columns количество столбцов (int)
 * @param result ссылка на структура с матрицей
 * @return код ошибки
 * @retval 0 - OK.
 * @retval 1 - INCORRECT_MATRIX.
 * @retval 2 - CALCULATION_ERROR.
 */
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int err_code = s21_is_valid_result_ptr(result);
  if (err_code == OK)
    err_code = (rows > 0 && columns > 0) ? OK : INCORRECT_MATRIX;
  if (err_code == OK) result->matrix = NULL;
  if (err_code == OK) result->matrix = calloc(rows, sizeof(double *));
  if (err_code == OK)
    err_code = (result->matrix == NULL) ? INCORRECT_MATRIX : OK;
  if (err_code == OK) {
    result->rows = rows;
    result->columns = columns;
    for (int i = 0; i < rows && err_code == OK; i++) {
      result->matrix[i] = calloc(columns, sizeof(double));
      if (result->matrix[i] == NULL) err_code = INCORRECT_MATRIX;
    }
    if (err_code != OK) s21_remove_matrix(result);
  }
  return err_code;
}