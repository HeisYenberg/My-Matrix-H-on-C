#include "s21_matrix.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = INCORRECT_MATRIX;
  if (A && B) {
    status = CALC_ERROR;
    if (A->rows == B->rows && A->columns == B->columns) {
      status = s21_create_matrix(A->rows, A->columns, result);
      if (!status) {
        for (int i = 0; i < A->rows; i++)
          for (int j = 0; j < A->columns; j++)
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }
  return status;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = INCORRECT_MATRIX;
  if (A && B) {
    status = CALC_ERROR;
    if (A->rows == B->rows && A->columns == B->columns) {
      status = s21_create_matrix(A->rows, A->columns, result);
      if (!status) {
        for (int i = 0; i < A->rows; i++)
          for (int j = 0; j < A->columns; j++)
            result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }
  return status;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int status = INCORRECT_MATRIX;
  if (A) {
    status = s21_create_matrix(A->rows, A->columns, result);
    if (!status) {
      for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < A->columns; j++)
          result->matrix[i][j] = A->matrix[i][j] * number;
    }
  }
  return status;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = INCORRECT_MATRIX;
  if (A && B) {
    status = CALC_ERROR;
    if (A->columns == B->rows) {
      status = s21_create_matrix(A->rows, B->columns, result);
      if (!status) {
        for (int i = 0; i < A->rows; i++)
          for (int j = 0; j < B->columns; j++)
            for (int k = 0; k < A->columns; k++)
              result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }
  return status;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int status = INCORRECT_MATRIX;
  if (A) {
    if (!s21_create_matrix(A->columns, A->rows, result)) {
      for (int i = 0; i < A->columns; i++) {
        for (int j = 0; j < A->rows; j++) {
          result->matrix[i][j] = A->matrix[j][i];
        }
      }
      status = OK;
    }
  }
  return status;
}

int s21_minor(matrix_t *A, matrix_t *result, int row, int column) {
  int status = s21_create_matrix(A->rows - 1, A->columns - 1, result);
  if (!status) {
    for (int i = 0, res_i = 0; i < A->rows; i++) {
      if (i == row) continue;
      for (int j = 0, res_j = 0; j < A->columns; j++) {
        if (j == column) continue;
        result->matrix[res_i][res_j] = A->matrix[i][j];
        res_j++;
      }
      res_i++;
    }
  }
  return status;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int status = INCORRECT_MATRIX;
  if (A) {
    status = CALC_ERROR;
    if (A->rows == A->columns) {
      if (!s21_create_matrix(A->rows, A->columns, result)) {
        for (int i = 0; i < result->rows; i++) {
          for (int j = 0; j < result->columns; j++) {
            matrix_t minor;
            if (!s21_minor(A, &minor, i, j)) {
              double det = 0;
              s21_determinant(&minor, &det);
              result->matrix[i][j] = det * pow(-1, (i + j));
              s21_remove_matrix(&minor);
              status = OK;
            }
          }
        }
      }
    }
  }
  return status;
}

double s21_recursive_determinant(matrix_t A) {
  double det = 0;
  if (A.rows == 1) {
    det = A.matrix[0][0];
  } else if (A.rows == 2) {
    det = (A.matrix[0][0] * A.matrix[1][1]) - (A.matrix[0][1] * A.matrix[1][0]);
  } else {
    for (int x = 0; x < A.columns; x++) {
      matrix_t sub_matrix;
      if (!s21_minor(&A, &sub_matrix, 0, x)) {
        int sign = (x % 2) ? -1 : 1;
        det += sign * A.matrix[0][x] * s21_recursive_determinant(sub_matrix);
        s21_remove_matrix(&sub_matrix);
      }
    }
  }
  return det;
}

int s21_determinant(matrix_t *A, double *result) {
  int status = INCORRECT_MATRIX;
  if (A) {
    status = CALC_ERROR;
    if (A->rows == A->columns) {
      status = OK;
      *result = s21_recursive_determinant(*A);
    }
  }
  return status;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int status = INCORRECT_MATRIX;
  if (A) {
    status = CALC_ERROR;
    if (A->rows == A->columns) {
      double det = 0;
      s21_determinant(A, &det);
      if (det) {
        matrix_t calc_complements;
        if (!s21_calc_complements(A, &calc_complements)) {
          matrix_t transpose;
          s21_transpose(&calc_complements, &transpose);
          s21_remove_matrix(&calc_complements);
          s21_mult_number(&transpose, 1 / det, result);
          s21_remove_matrix(&transpose);
          status = OK;
        }
      }
    }
  }
  return status;
}