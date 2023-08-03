# My-Matrix-H-on-C

## My version of the matrix.h library in the C programming language.

## Usage :

- To build a library run `make my_matrix.a`
- To see tests run `make test`, might need to install `check`
- To see tests code coverage run `make gcov_report`, might need to install `lcov`

### Overview of "my_matrix.h" functions

| No. | Function                                                       | Description                                         |
|-----|----------------------------------------------------------------|-----------------------------------------------------|
| 1   | int create_matrix(int rows, int columns, matrix_t *result);    | Creating matrix                                     |
| 2   | void remove_matrix(matrix_t *A);                               | Cleaning matrix                                     |
| 3   | int is_eq_matrix(matrix_t *A, matrix_t *B);                    | Matrix comparison                                   |
| 4   | int sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);    | Adding matrices                                     |
| 5   | int sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);    | Subtracting matrices                                |
| 6   | int mult_number(matrix_t *A, double number, matrix_t *result); | Matrix multiplication by scalar                     |
| 7   | int mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);   | Multiplication of two matrices                      |
| 8   | int get_transpose(matrix_t *A, matrix_t *result);              | Matrix transpose                                    |
| 9   | int get_calc_complements(matrix_t *A, matrix_t *result);       | Minor of matrix and matrix of algebraic complements |
| 10  | int get_determinant(matrix_t *A, double *result);              | Matrix determinant                                  |
| 11  | int inverse_matrix(matrix_t *A, matrix_t *result);             | Inverse of the matrix                               |