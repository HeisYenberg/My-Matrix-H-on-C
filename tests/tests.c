#include "tests.h"

int main() {
  int failed = 0;
  SRunner *sr = srunner_create(test_matrix());
  srunner_run_all(sr, CK_NORMAL);
  failed += srunner_ntests_failed(sr);
  srunner_free(sr);
  printf("Failed %d", failed);
  return 0;
}

void static_to_dinamic(double temp[][3], matrix_t *test) {
  for (int i = 0; i < test->rows; i++) {
    for (int j = 0; j < test->columns; j++) {
      test->matrix[i][j] = temp[i][j];
    }
  }
}

void compare_matrix(matrix_t test, double result[][3]) {
  for (int i = 0; i < test.rows; i++) {
    for (int j = 0; j < test.columns; j++) {
      ck_assert_double_eq_tol(test.matrix[i][j], result[i][j], 1e-5);
    }
  }
}

START_TEST(test_create) {
  matrix_t create;
  int status =
      s21_create_matrix(create_matrix[_i][0], create_matrix[_i][1], &create);
  ck_assert_int_eq(create_return[_i], status);
  if (!status) s21_remove_matrix(&create);
}

START_TEST(test_eq) {
  matrix_t value_1, value_2;
  int status_1 = s21_create_matrix(3, 3, &value_1);
  int status_2 = s21_create_matrix(3, 3, &value_2);
  static_to_dinamic(val_1[_i], &value_1);
  static_to_dinamic(val_2[_i], &value_2);
  ck_assert_int_eq(compare_results[_i], s21_eq_matrix(&value_1, &value_2));
  if (!status_1) s21_remove_matrix(&value_1);
  if (!status_2) s21_remove_matrix(&value_2);
}
END_TEST

START_TEST(test_sum) {
  matrix_t value_1, value_2, result;
  int status_1 = s21_create_matrix(3, 3, &value_1);
  int status_2 = s21_create_matrix(3, 3, &value_2);
  static_to_dinamic(val_1[_i], &value_1);
  static_to_dinamic(val_2[_i], &value_2);
  int status_result = s21_sum_matrix(&value_1, &value_2, &result);
  compare_matrix(result, sum_result[_i]);
  ck_assert_int_eq(0, status_result);
  if (!status_1) s21_remove_matrix(&value_1);
  if (!status_2) s21_remove_matrix(&value_2);
  if (!status_result) s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sub) {
  matrix_t value_1, value_2, result;
  int status_1 = s21_create_matrix(3, 3, &value_1);
  int status_2 = s21_create_matrix(3, 3, &value_2);
  static_to_dinamic(val_1[_i], &value_1);
  static_to_dinamic(val_2[_i], &value_2);
  int status_result = s21_sub_matrix(&value_1, &value_2, &result);
  compare_matrix(result, sub_result[_i]);
  ck_assert_int_eq(0, status_result);
  if (!status_1) s21_remove_matrix(&value_1);
  if (!status_2) s21_remove_matrix(&value_2);
  if (!status_result) s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_number) {
  matrix_t value_1, result;
  int status_1 = s21_create_matrix(3, 3, &value_1);
  static_to_dinamic(val_1[_i], &value_1);
  int status_result = s21_mult_number(&value_1, number_to_mult_by[_i], &result);
  compare_matrix(result, mult_number_result[_i]);
  ck_assert_int_eq(0, status_result);
  if (!status_1) s21_remove_matrix(&value_1);
  if (!status_result) s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_matrix) {
  matrix_t value_1, value_2, result;
  int status_1 = s21_create_matrix(3, 3, &value_1);
  int status_2 = s21_create_matrix(3, 3, &value_2);
  static_to_dinamic(val_1[_i], &value_1);
  static_to_dinamic(val_2[_i], &value_2);
  int status_result = s21_mult_matrix(&value_1, &value_2, &result);
  compare_matrix(result, mult_matrix_result[_i]);
  ck_assert_int_eq(0, status_result);
  if (!status_1) s21_remove_matrix(&value_1);
  if (!status_2) s21_remove_matrix(&value_2);
  if (!status_result) s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_transpose) {
  matrix_t value_1, result;
  int status_1 = s21_create_matrix(3, 3, &value_1);
  static_to_dinamic(val_1[_i], &value_1);
  int status_result = s21_transpose(&value_1, &result);
  compare_matrix(result, transpose_results[_i]);
  ck_assert_int_eq(0, status_result);
  if (!status_1) s21_remove_matrix(&value_1);
  if (!status_result) s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_calc_complements) {
  matrix_t value_1, result;
  int status_1 = s21_create_matrix(3, 3, &value_1);
  static_to_dinamic(val_1[_i], &value_1);
  int status_result = s21_calc_complements(&value_1, &result);
  compare_matrix(result, calc_comlements_results[_i]);
  ck_assert_int_eq(0, status_result);
  if (!status_1) s21_remove_matrix(&value_1);
  if (!status_result) s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_determinant) {
  matrix_t value_1;
  int status_1 = s21_create_matrix(3, 3, &value_1);
  static_to_dinamic(val_1[_i], &value_1);
  double det = 0;
  int status_result = s21_determinant(&value_1, &det);
  ck_assert_double_eq_tol(det, determinant_result[_i], 1e-05);
  ck_assert_int_eq(0, status_result);
  if (!status_1) s21_remove_matrix(&value_1);
}
END_TEST

START_TEST(test_inverse) {
  matrix_t value_1, result;
  int status_1 = s21_create_matrix(3, 3, &value_1);
  static_to_dinamic(val_1[_i], &value_1);
  int status_result = s21_inverse_matrix(&value_1, &result);
  if (!status_result) {
    compare_matrix(result, inverse_results[_i]);
    s21_remove_matrix(&result);
  }
  ck_assert_int_eq(inverse_return[_i], status_result);
  if (!status_1) s21_remove_matrix(&value_1);
}
END_TEST

Suite *test_matrix() {
  Suite *s = suite_create("\033[42m-=S21_MATRIX_TESTS=-\033[0m");
  TCase *tc = tcase_create("S21_MATRIX_TESTS");
  suite_add_tcase(s, tc);
  tcase_add_loop_test(tc, test_eq, 0, 5);
  tcase_add_loop_test(tc, test_create, 0, 5);
  tcase_add_loop_test(tc, test_sum, 0, 5);
  tcase_add_loop_test(tc, test_sub, 0, 5);
  tcase_add_loop_test(tc, test_mult_number, 0, 5);
  tcase_add_loop_test(tc, test_mult_matrix, 0, 5);
  tcase_add_loop_test(tc, test_transpose, 0, 5);
  tcase_add_loop_test(tc, test_calc_complements, 0, 5);
  tcase_add_loop_test(tc, test_determinant, 0, 5);
  tcase_add_loop_test(tc, test_inverse, 0, 5);
  return s;
}