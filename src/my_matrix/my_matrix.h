#ifndef MY_MATRIX_H
#define MY_MATRIX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

enum matrix_status { OK, INCORRECT_MATRIX, CALC_ERROR };

enum matrix_comparison { FAILURE, SUCCESS };

typedef struct matrix_struct {
  double** matrix;
  int rows;
  int columns;
} matrix_t;

int create_matrix(int rows, int columns, matrix_t* result);
void remove_matrix(matrix_t* A);
int is_eq_matrix(matrix_t* A, matrix_t* B);

int sum_matrix(matrix_t* A, matrix_t* B, matrix_t* result);
int sub_matrix(matrix_t* A, matrix_t* B, matrix_t* result);
int mult_number(matrix_t* A, double number, matrix_t* result);
int mult_matrix(matrix_t* A, matrix_t* B, matrix_t* result);

int get_transpose(matrix_t* A, matrix_t* result);
int get_minor(matrix_t* A, matrix_t* result, int i, int j);
int get_calc_complements(matrix_t* A, matrix_t* result);
int get_determinant(matrix_t* A, double* result);
double recursive_determinant(matrix_t A);
int inverse_matrix(matrix_t* A, matrix_t* result);

#endif  // MY_MATRIX_H