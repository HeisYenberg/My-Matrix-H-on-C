#include "my_matrix.h"

int sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = INCORRECT_MATRIX;
  if (A && B) {
    status = CALC_ERROR;
    if (A->rows == B->rows && A->columns == B->columns) {
      status = create_matrix(A->rows, A->columns, result);
      if (!status) {
        for (int i = 0; i < A->rows; i++)
          for (int j = 0; j < A->columns; j++)
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }
  return status;
}

int sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = INCORRECT_MATRIX;
  if (A && B) {
    status = CALC_ERROR;
    if (A->rows == B->rows && A->columns == B->columns) {
      status = create_matrix(A->rows, A->columns, result);
      if (!status) {
        for (int i = 0; i < A->rows; i++)
          for (int j = 0; j < A->columns; j++)
            result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }
  return status;
}

int mult_number(matrix_t *A, double number, matrix_t *result) {
  int status = INCORRECT_MATRIX;
  if (A) {
    status = create_matrix(A->rows, A->columns, result);
    if (!status) {
      for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < A->columns; j++)
          result->matrix[i][j] = A->matrix[i][j] * number;
    }
  }
  return status;
}

int mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = INCORRECT_MATRIX;
  if (A && B) {
    status = CALC_ERROR;
    if (A->columns == B->rows) {
      status = create_matrix(A->rows, B->columns, result);
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

int get_transpose(matrix_t *A, matrix_t *result) {
  int status = INCORRECT_MATRIX;
  if (A) {
    if (!create_matrix(A->columns, A->rows, result)) {
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

int get_minor(matrix_t *A, matrix_t *result, int row, int column) {
  int status = create_matrix(A->rows - 1, A->columns - 1, result);
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

int get_calc_complements(matrix_t *A, matrix_t *result) {
  int status = INCORRECT_MATRIX;
  if (A) {
    status = CALC_ERROR;
    if (A->rows == A->columns) {
      if (!create_matrix(A->rows, A->columns, result)) {
        for (int i = 0; i < result->rows; i++) {
          for (int j = 0; j < result->columns; j++) {
            matrix_t minor;
            if (!get_minor(A, &minor, i, j)) {
              double det = 0;
              get_determinant(&minor, &det);
              result->matrix[i][j] = det * pow(-1, (i + j));
              remove_matrix(&minor);
              status = OK;
            }
          }
        }
      }
    }
  }
  return status;
}

double recursive_determinant(matrix_t A) {
  double det = 0;
  if (A.rows == 1) {
    det = A.matrix[0][0];
  } else if (A.rows == 2) {
    det = (A.matrix[0][0] * A.matrix[1][1]) - (A.matrix[0][1] * A.matrix[1][0]);
  } else {
    for (int x = 0; x < A.columns; x++) {
      matrix_t sub_matrix;
      if (!get_minor(&A, &sub_matrix, 0, x)) {
        int sign = (x % 2) ? -1 : 1;
        det += sign * A.matrix[0][x] * recursive_determinant(sub_matrix);
        remove_matrix(&sub_matrix);
      }
    }
  }
  return det;
}

int get_determinant(matrix_t *A, double *result) {
  int status = INCORRECT_MATRIX;
  if (A) {
    status = CALC_ERROR;
    if (A->rows == A->columns) {
      status = OK;
      *result = recursive_determinant(*A);
    }
  }
  return status;
}

int inverse_matrix(matrix_t *A, matrix_t *result) {
  int status = INCORRECT_MATRIX;
  if (A) {
    status = CALC_ERROR;
    if (A->rows == A->columns) {
      double det = 0;
      get_determinant(A, &det);
      if (det) {
        matrix_t calc_complements;
        if (!get_calc_complements(A, &calc_complements)) {
          matrix_t transpose;
          get_transpose(&calc_complements, &transpose);
          remove_matrix(&calc_complements);
          mult_number(&transpose, 1 / det, result);
          remove_matrix(&transpose);
          status = OK;
        }
      }
    }
  }
  return status;
}