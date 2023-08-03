#include "my_matrix.h"

int create_matrix(int rows, int columns, matrix_t *result) {
  int status = INCORRECT_MATRIX;
  if (rows > 0 && columns > 0) {
    result->matrix = calloc(rows, sizeof(double *));
    if (result->matrix) {
      int memory = 1;
      for (int i = 0; i < rows && memory; i++) {
        result->matrix[i] = calloc(columns, sizeof(double));
        if (!result->matrix[i]) {
          memory = 0;
          for (int m = 0; m < i; m++) free(result->matrix[m]);
        }
      }
      if (memory) {
        result->rows = rows;
        result->columns = columns;
        status = OK;
      } else {
        free(result->matrix);
      }
    }
  }
  return status;
}

void remove_matrix(matrix_t *A) {
  if (A) {
    if (A->matrix) {
      for (int i = 0; i < A->rows; i++) free(A->matrix[i]);
      free(A->matrix);
      A->matrix = NULL;
    }
    A->rows = 0;
    A->columns = 0;
  }
}

int is_eq_matrix(matrix_t *A, matrix_t *B) {
  int status = FAILURE;
  if (A && B) {
    if (A->rows == B->rows && A->columns == B->columns && A->rows > 0 &&
        B->rows > 0) {
      status = SUCCESS;
      for (int i = 0; i < A->rows && status; i++) {
        for (int j = 0; j < A->columns && status; j++) {
          if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1E-06) status = FAILURE;
        }
      }
    }
  }
  return status;
}