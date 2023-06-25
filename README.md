# S21-Matrix

## My version of the matrix.h library in the C programming language.

## Usage :

- To build a library run `make s21_matrix.a`
- To see tests run `make test`, might need to install `check`
- To see tests code coverage run `make gcov_report`, might need to install `lcov`

### Overview of "s21_matrix.h" functions

| No. | Function                                                           | Description                                         |
|-----|--------------------------------------------------------------------|-----------------------------------------------------|
| 1   | int s21_create_matrix(int rows, int columns, matrix_t *result);    | Creating matrix                                     |
| 2   | void s21_remove_matrix(matrix_t *A);                               | Cleaning matrix                                     |
| 3   | int s21_eq_matrix(matrix_t *A, matrix_t *B);                       | Matrix comparison                                   |
| 4   | int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);    | Adding matrices                                     |
| 5   | int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);    | Substracting matrices                               |
| 6   | int s21_mult_number(matrix_t *A, double number, matrix_t *result); | Matrix multiplication by scalar                     |
| 7   | int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);   | Multiplication of two matrices                      |
| 8   | int s21_transpose(matrix_t *A, matrix_t *result);                  | Matrix transpose                                    |
| 9   | int s21_calc_complements(matrix_t *A, matrix_t *result);           | Minor of matrix and matrix of algebraic complements |
| 10  | int s21_determinant(matrix_t *A, double *result);                  | Matrix determinant                                  |
| 11  | int s21_inverse_matrix(matrix_t *A, matrix_t *result);             | Inverse of the matrix                               |