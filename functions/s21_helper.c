#include "../s21_matrix.h"

/**
 * @brief проверяет равенство размеров матрицы
 *
 * @param A первая матрица (matrix_t)
 * @param B вторая матрица (matrix_t)
 * @return результат проверки (int)
 * @retval 0 - OK.
 * @retval 1 - INCORRECT_MATRIX.
 * @retval 2 - CALCULATION_ERROR.
 */
int s21_eq_size(const matrix_t *A, const matrix_t *B) {
  printf("s21_eq_size.check_1: %d\n", A->rows != B->rows);
  printf("s21_eq_size.check_2: %d\n", A->columns != B->columns);
  printf("s21_eq_size.check_3: %d\n", A->rows != B->rows || A->columns != B->columns);
  return (A->rows != B->rows || A->columns != B->columns) ? CALCULATION_ERROR
                                                          : OK;
}

/**
 * @brief проверяет что матрица квадратная
 *
 * @param source указатель на проверяемую матрицу (matrix_t *)
 * @return результат проверки (int)
 * @retval 0 - OK.
 * @retval 1 - INCORRECT_MATRIX.
 * @retval 2 - CALCULATION_ERROR.
 */
int s21_squar_size(const matrix_t *source) {
  return (source->rows != source->columns) ? CALCULATION_ERROR : OK;
}

/**
 * @brief проверяет равенство двух чисел с заданной точностью
 *
 * @param val_1 первое число (double)
 * @param val_2 второе число (double)
 * @return результат проверки (int)
 * @retval 0 - числа НЕ равны.
 * @retval 1 - числа равны.
 */
int s21_eq_element(double val_1, double val_2) {
  return fabs(val_1 - val_2) < S21_PRECISION;
}

/**
 * @brief проверяет равенство содержимого матриц
 *
 * @param A первая матрица (matrix_t)
 * @param B вторая матрица (matrix_t)
 * @return результат проверки (int)
 * @retval 0 - содержимые матриц НЕ равны.
 * @retval 1 - содержимые матриц равны.
 */
int s21_eq_content(const matrix_t *A, const matrix_t *B) {
  int result = SUCCESS;
  if (s21_eq_size(A, B)) result = FAILURE;
  printf("s21_eq_content.result_before_cmp: %d\n", result);
  for (int i = 0; i < A->rows && result == SUCCESS; i++) {
    for (int j = 0; j < A->columns && result == SUCCESS; j++) {
      result = s21_eq_element(A->matrix[i][j], B->matrix[i][j]);
      printf("s21_eq_content.cpr: %f --- %f\n", A->matrix[i][j], B->matrix[i][j]);
    }
  }
  printf("s21_eq_content.result_after_cmp: %d\n", result);
  return result;
}

/**
 * @brief проверяет совместимость размеров матрицы (число столбцов одной матрицы
 * равно число строк другой и наоборот)
 *
 * @param A первая матрица (matrix_t)
 * @param B вторая матрица (matrix_t)
 * @return результат проверки (int)
 * @retval 0 - OK.
 * @retval 1 - INCORRECT_MATRIX.
 * @retval 2 - CALCULATION_ERROR.
 */
int s21_compatibility_size(const matrix_t *A, const matrix_t *B) {
  return (A->columns != B->rows) ? CALCULATION_ERROR : OK;
}

/**
 * @brief рассчитывает минор (определитель субматрицы, т.е. усеченной по
 * выбранным строке и столбцу)
 *
 * @param source структура с исходной матрицей (matrix_t *)
 * @param row выбранная строка (int)
 * @param column выбранный столбец (int)
 * @param result структура с исходной матрицей (double *)
 * @return код ошибки (int)
 * @retval 0 - OK.
 * @retval 1 - INCORRECT_MATRIX.
 * @retval 2 - CALCULATION_ERROR.
 */
int s21_get_minor(const matrix_t *source, int row, int column, double *result) {
  double determinant = 0.0;
  matrix_t sub_matrix = {0};
  int err_code =
      s21_create_sub_matrix(source, row, column, source->rows - 1, &sub_matrix);
  if (err_code == OK) err_code = s21_determinant(&sub_matrix, &determinant);
  s21_remove_matrix(&sub_matrix);
  if (err_code == OK) err_code = s21_is_valid_element(determinant);
  if (err_code == OK) *result = determinant;
  return err_code;
}

/**
 * @brief создает субматрицу, за исключением указанного столбца и строки
 *
 * @param source исходная матрица (matrix_t *)
 * @param row_del строка заданного элемента исходной матрицы (int)
 * @param column_del столбец заданного элемента исходной матрицы (int)
 * @param size разрер субматрицы матрицы (int)
 * @param result указатель результат (*result)
 * @return код ошибки (int)
 */
int s21_create_sub_matrix(const matrix_t *source, int row_del, int column_del,
                          int size, matrix_t *result) {
  int err_code = s21_create_matrix(size, size, result);
  if (err_code == OK) {
    for (int row_src = 0, row_res = 0; row_src <= size; row_src++) {
      if (row_src == row_del) continue;
      for (int column_src = 0, column_res = 0; column_src <= size;
           column_src++) {
        if (column_src == column_del) continue;
        result->matrix[row_res][column_res] =
            source->matrix[row_src][column_src];
        column_res++;
      }
      row_res++;
    }
  }
  return err_code;
}

/**
 * @brief заполняет матрицу арифметической последовательностью, заданной началом
 * и шагом
 *
 * @param source исходная матрица
 * @param start значение первого элемента матрицы (double)
 * @param step шаг арифметической последовательности (double)
 */
void s21_initialize_matrix(matrix_t *source, double start, double step) {
  if (!s21_is_valid_matrix_full(source)) {
    double current_value = start;
    for (int i = 0; i < source->rows; i++) {
      for (int j = 0; j < source->columns; j++) {
        source->matrix[i][j] = current_value;
        current_value += step;
      }
    }
  }
}

/**
 * @brief проверяет валидность матрицы.
 * проверяемые признаки: указатель на структуру, размеры матрицы, указатель на
 * матрицу, указатели строк
 * @param source структура с матрицей (matrix_t)
 * @return результат проверки (int)
 * @retval 0 - OK.
 * @retval 1 - INCORRECT_MATRIX.
 * @retval 2 - CALCULATION_ERROR.
 */
int s21_is_valid_matrix_mini(const matrix_t *source) {
  int err_code = (!source) ? INCORRECT_MATRIX : OK;
  if (err_code == OK) err_code = (!source->rows) ? INCORRECT_MATRIX : OK;
  // if (err_code == OK) err_code = (source->rows != source->rows) ? INCORRECT_MATRIX : OK;
  if (err_code == OK) err_code = (source->rows < 1) ? INCORRECT_MATRIX : OK;
  if (err_code == OK) err_code = (!source->matrix) ? INCORRECT_MATRIX : OK;
  for (int i = 0; err_code == OK && i < source->rows; i++)
    err_code = (!source->matrix[i]) ? INCORRECT_MATRIX : OK;
  return err_code;
}

/**
 * @brief проверяет валидность матрицы.
 * проверяемые признаки: указатель на структуру, размеры матрицы, указатель на
 * матрицу, указатели строк
 * @param source структура с матрицей (matrix_t)
 * @return результат проверки (int)
 * @retval 0 - OK.
 * @retval 1 - INCORRECT_MATRIX.
 * @retval 2 - CALCULATION_ERROR.
 */
int s21_is_valid_matrix_midi(const matrix_t *source) {
  int err_code = s21_is_valid_matrix_mini(source);
  if (err_code == OK) err_code = (!source->columns) ? INCORRECT_MATRIX : OK;
    err_code = (source->columns != source->columns) ? INCORRECT_MATRIX : OK;
  if (err_code == OK)
  if (err_code == OK) err_code = (source->columns < 1) ? INCORRECT_MATRIX : OK;
  return err_code;
}

/**
 * @brief проверяет валидность матрицы.
 * дополнительные признаки: содержимое матрицы (элементы)
 * @param source структура с матрицей (matrix_t)
 * @return результат проверки (int)
 * @retval 0 - OK.
 * @retval 1 - INCORRECT_MATRIX.
 * @retval 2 - CALCULATION_ERROR.
 */
int s21_is_valid_matrix_full(const matrix_t *source) {
  int err_code = s21_is_valid_matrix_midi(source);
  if (err_code == OK) {
    for (int i = 0; err_code == OK && i < source->rows; i++) {
      for (int j = 0; err_code == OK && j < source->columns; j++) {
        err_code = s21_is_valid_element(source->matrix[i][j]);
      }
    }
  }
  return err_code;
}

/**
 * @brief проверяет валидность числа
 * проверяемые признаки: число не является бесконечностью и не является НЕ_ЧИСЛО
 * @param val исходное число (double)
 * @return результат проверки (int)
 * @retval 0 - OK.
 * @retval 1 - INCORRECT_MATRIX.
 * @retval 2 - CALCULATION_ERROR.
 */
int s21_is_valid_element(double val) {
  return (isnan(val) || isinf(val)) ? CALCULATION_ERROR : OK;
}

/**
 * @brief проверяет валидность указателя на результат
 * проверяемые признаки: не является NULL
 * @param source проверяемый указатель (source)
 * @return результат проверки (int)
 * @retval 0 - OK.
 * @retval 1 - INCORRECT_MATRIX.
 * @retval 2 - CALCULATION_ERROR.
 */
int s21_is_valid_result_ptr(const matrix_t *source) {
  return (!source) ? INCORRECT_MATRIX : OK;
}

/**
 * @brief создает копию матрицы
 *
 * @param source структура с исходной матрицей (matrix_t *)
 * @param result структура с исходной матрицей (matrix_t *)
 * @return код ошибки (int)
 * @retval 0 - OK.
 * @retval 1 - INCORRECT_MATRIX.
 * @retval 2 - CALCULATION_ERROR.
 */
int s21_copy_matrix(const matrix_t *source, matrix_t *result) {
  int err_code = s21_create_matrix(source->rows, source->rows, result);
  if (err_code == OK)
    for (int i = 0; i < source->rows; i++) {
      for (int j = 0; j < source->rows; j++) {
        result->matrix[i][j] = source->matrix[i][j];
      }
    }
  return err_code;
}

/**
 * @brief преобразует матрицу методом гауса в треугольную
 *
 * @param source структура с исходной матрицей (matrix_t *)
 * @return код ошибки (int)
 * @retval 0 - OK.
 * @retval 1 - INCORRECT_MATRIX.
 * @retval 2 - CALCULATION_ERROR.
 */
int s21_gauss_elimination(const matrix_t *source) {
  for (int k = 0; k < source->rows - 1; k++) {
    for (int i = k + 1; i < source->rows; i++) {
      // double factor = source->matrix[k][k] == 0.0 ? 0.0 :
      // source->matrix[i][k] / source->matrix[k][k];
      double factor = source->matrix[i][k] / source->matrix[k][k];
      for (int j = k; j < source->rows; j++) {
        source->matrix[i][j] -= factor * source->matrix[k][j];
      }
    }
  }
  return OK;
}

/**
 * @brief находит произведение элементов главной диагонали матрицы
 *
 * @param source структура с исходной матрицей (matrix_t *)
 * @return результат вычисления (double)
 */
double s21_main_diagonal_multiple(const matrix_t *source) {
  double result = 1.0;
  for (int i = 0; i < source->rows && result != 0.0; i++)
    if (source->matrix[i][i] == 0.0) result = 0.0;
  for (int i = 0; i < source->rows && result != 0.0; i++)
    result *= source->matrix[i][i];
  return result;
}

//////////////////функции для отладки///////////////////////////
/**
 * @brief вывод на экран матрицы
 *
 * @param source исходная матрица
 */
void s21_print_matrix(const matrix_t *source) {
  if (!s21_is_valid_matrix_midi(source)) {
    for (int i = 0; i < source->rows; i++) {
      for (int j = 0; j < source->columns; j++)
        printf("%-10f\t", source->matrix[i][j]);
      printf("\n");
    }
  }
}

// /**
//  * @brief корректирует индекс (концепция бесконечной склейки)
//  *
//  * @param index исходный индекс (int)
//  * @param size размер матрицы (int)
//  * @return итоговый индекс (int)
//  */
// int s21_correct_index(int index, int size) { return (index + size) % size; }

// /**
//  * @brief находит определитель матрицы 2 порядка
//  *
//  * @param source исходная матрица (matrix_t)
//  * @param size размер матрицы (int)
//  * @return итоговый индекс (int)
//  */
// int s21_determinant_2x2(const matrix_t source) {
//   return source.matrix[0][0] * source.matrix[1][1] -
//          source.matrix[0][1] * source.matrix[1][0];
// }

// /**
//  * @brief расчитывает определитель квадратной матрицы
//  *
//  * @param A исходная матрица (matrix_t)
//  * @param result результат (double)
//  * @return код ошибки (int)
//  * @retval 0 - OK.
//  * @retval 1 - INCORRECT_MATRIX.
//  * @retval 2 - CALCULATION_ERROR.
//  */
// int s21_determinant_old(matrix_t *A, double *result) {
//   long double res = 0.0;
//   long double term_1, term_2;
//   int err_code = OK;
//   if (err_code == OK) err_code = s21_is_valid_matrix_full(A);
//   if (err_code == OK) err_code = s21_squar_size(A);
//   if (err_code == OK) {
//     if (A->rows == 1)
//       res = A->matrix[0][0];
//     else if (A->rows == 2)
//       res =
//           A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] *
//           A->matrix[0][1];
//     else
//       for (int i = 0; err_code == OK && i < A->rows; i++) {
//         term_1 = 1.0;
//         term_2 = 1.0;
//         for (int j = 0; err_code == OK && j < A->rows; j++) {
//           term_1 *= A->matrix[j][s21_correct_index(i + j, A->rows)];
//           term_2 *= A->matrix[j][s21_correct_index(i - j, A->rows)];
//         }
//         res += term_1 - term_2;
//       }
//   }
//   if (err_code == OK) err_code = s21_is_valid_element((double)res);
//   if (err_code == OK) *result = (double)res;
//   return err_code;
// }

/**
 * @brief заполняет матрицу псевдослучайными числами
 *
 * @param source исходная матрица
 */
void s21_initialize_matrix_random(matrix_t *source, int shift) {
  srand(shift);
  if (!s21_is_valid_matrix_full(source)) {
    for (int i = 0; i < source->rows; i++) {
      for (int j = 0; j < source->columns; j++) {
        source->matrix[i][j] = rand() % 10000 / 100.0;
      }
    }
  }
}