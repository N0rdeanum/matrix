#include "s21_matrix.h"

#include <stdlib.h>

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int return_count = OK;

  if ((rows < 0) || (columns < 0) || result == NULL) {
    return INCORRECT_MATRIX;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (result->matrix != NULL) {
      for (int i = 0; i < rows; i++)
        result->matrix[i] = (double *)calloc(columns, sizeof(double));
    }
  }

  return (return_count ? INCORRECT_MATRIX : return_count);
}

void s21_remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) free(A->matrix[i]);
  free(A->matrix);
  A->matrix = NULL;
  A->rows = 0;
  A->columns = 0;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if (!s21_validate(A) || !s21_validate(B)) return FAILURE;

  if ((A->rows != B->rows || A->columns != B->columns)) return FAILURE;

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-7) {
        return FAILURE;
      }
    }
  }

  return SUCCESS;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!s21_validate(A) || !s21_validate(B)) return INCORRECT_MATRIX;

  if (A->rows != B->rows || A->columns != B->columns) return CALC_ERROR;

  if (result == NULL) return INCORRECT_MATRIX;

  s21_create_matrix(A->rows, A->columns, result);
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
    }
  }

  return OK;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!s21_validate(A) || !s21_validate(B)) return INCORRECT_MATRIX;

  if (A->rows != B->rows || A->columns != B->columns) return CALC_ERROR;

  if (result == NULL) return INCORRECT_MATRIX;

  s21_create_matrix(A->rows, A->columns, result);
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
    }
  }

  return OK;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (!s21_validate(A)) return INCORRECT_MATRIX;

  s21_create_matrix(A->rows, A->columns, result);
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] * number;
    }
  }
  return OK;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!s21_validate(A) || !s21_validate(B)) return INCORRECT_MATRIX;

  if (A->columns != B->rows) return CALC_ERROR;
  if (result == NULL) return INCORRECT_MATRIX;

  s21_create_matrix(A->rows, B->columns, result);

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < B->columns; j++) {
      for (int k = 0; k < A->columns; k++) {
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }

  return OK;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int return_code = OK;

  if (A != NULL && result != NULL && s21_validate(A) == SUCCESS) {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  } else {
    return_code = INCORRECT_MATRIX;
  }
  return return_code;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (!s21_validate(A)) return INCORRECT_MATRIX;

  if (A->rows != A->columns) return CALC_ERROR;

  s21_create_matrix(A->rows, A->columns, result);

  if (A->rows == 1) {
    result->matrix[0][0] = A->matrix[0][0];
    return SUCCESS;
  }

  int sign = 0;
  matrix_t temp;

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      s21_minor(i, j, A, &temp);
      sign = ((i + j) % 2 == 0) ? 1 : -1;
      result->matrix[i][j] = s21_det(&temp) * sign;
      s21_remove_matrix(&temp);
    }
  }

  return OK;
}

bool s21_validate(matrix_t *matrix) {
  return matrix && (matrix->rows >= 0) && (matrix->columns >= 0) &&
         matrix->matrix;
}

int s21_determinant(matrix_t *A, double *result) {
  int return_count = OK;

  if (!s21_validate(A)) return INCORRECT_MATRIX;

  if (A->rows != A->columns) {
    return_count = CALC_ERROR;
  } else {
    *result = s21_det(A);
  }

  return return_count;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (!s21_validate(A)) return INCORRECT_MATRIX;

  if (A->rows != A->columns) return CALC_ERROR;

  double determinant = s21_det(A);

  if (fabs(determinant) < 1e-7) return CALC_ERROR;

  matrix_t complements, transponse;

  s21_calc_complements(A, &complements);
  s21_transpose(&complements, &transponse);

  s21_mult_number(&transponse, 1 / determinant, result);

  s21_remove_matrix(&complements);
  s21_remove_matrix(&transponse);

  return OK;
}

double s21_det(matrix_t *A) {
  double result = 0;

  if (A->rows == 1) {
    result = A->matrix[0][0];
  } else if (A->rows == 2) {
    result = ((A->matrix[0][0] * A->matrix[1][1]) -
              (A->matrix[0][1] * A->matrix[1][0]));
  } else {
    int sign = 1;
    for (int i = 0; i < A->rows; i++) {
      matrix_t temp;
      s21_minor(0, i, A, &temp);

      result += sign * A->matrix[0][i] * s21_det(&temp);
      sign *= -1;

      s21_remove_matrix(&temp);
    }
  }
  return result;
}

void s21_minor(int row, int column, matrix_t *A, matrix_t *result) {
  int di = 0, dj = 0;
  s21_create_matrix(A->rows - 1, A->columns - 1, result);

  for (int i = 0; i < result->rows; i++) {
    if (i == row) di = 1;
    dj = 0;

    for (int j = 0; j < result->columns; j++) {
      if (j == column) dj = 1;
      result->matrix[i][j] = A->matrix[i + di][j + dj];
    }
  }
}

// void print_matrix(matrix_t *A) {
//   for (int i = 0; i < A->rows; i++) {
//     for (int j = 0; j < A->columns; j++) {
//       printf("%.lf ", A->matrix[i][j]);
//     }
//     printf("\n");
//   }
//   printf("\n");
// }

// int main() {
//   int rows = 3, columns = 3;
//   matrix_t A, B, result, mult_number;
//   s21_create_matrix(rows, columns, &A);
//   A.matrix[0][0] = 1.23;
//   A.matrix[0][1] = 22;
//   A.matrix[0][2] = -3;
//   A.matrix[1][0] = 4;
//   A.matrix[1][1] = -4;
//   A.matrix[1][2] = -33;
//   A.matrix[2][0] = 4;
//   A.matrix[2][1] = -4;
//   A.matrix[2][2] = -33;
//   //   }
//   // }

//   s21_create_matrix(rows, columns, &B);
//   B.matrix[0][0] = 13;
//   B.matrix[0][1] = 5;
//   B.matrix[0][2] = 2;
//   B.matrix[1][0] = 3;
//   B.matrix[1][1] = 7;
//   B.matrix[1][2] = 17;
//   B.matrix[2][0] = 3;
//   B.matrix[2][1] = 7;
//   B.matrix[2][2] = 17;
//   //   }
//   // }

//   s21_create_matrix(rows, columns, &result);
//   s21_sum_matrix(&A, &B, &result);
//   for (int i = 0; i < result.rows; i++) {
//     for (int j = 0; j < result.columns; j++) {
//     }
//   }

//   s21_create_matrix(rows, columns, &mult_number);
//   s21_mult_number(&A, 5, &mult_number);
//   for (int i = 0; i < mult_number.rows; i++) {
//     for (int j = 0; j < mult_number.columns; j++) {
//     }
//   }

//   s21_create_matrix(rows, columns, &mult_number);
//   s21_mult_matrix(&A, &B, &result);
//   for (int i = 0; i < result.rows; i++) {
//     for (int j = 0; j < result.columns; j++) {
//     }
//   }

//   printf("\033[41m-=Код eq matrix %d=-\033[0m \n\n", s21_eq_matrix(&A,
//   &B)); printf("\033[43m-=matrix A=-\033[0m\n"); printf("\033[41m-=Код
//   %d=-\033[0m \n",
//          s21_create_matrix(rows, columns, &result));
//   print_matrix(&A);
//   printf("\033[43m-=matrix В=-\033[0m\n");
//   printf("\033[41m-=Код %d=-\033[0m \n",
//          s21_create_matrix(rows, columns, &result));
//   print_matrix(&B);
//   printf("\033[43m-=matrix Result sum && sub =-\033[0m\n");
//   printf("\033[41m-=Код %d=-\033[0m \n", s21_sum_matrix(&A, &B, &result));
//   print_matrix(&result);
//   printf("\033[43m-=matrix mult_number A * N =-\033[0m\n");
//   printf("\033[41m-=Код %d=-\033[0m \n", s21_mult_number(&A, 5,
//   &mult_number)); print_matrix(&mult_number); printf("\033[43m-=matrix
//   mult_matrix A * B =-\033[0m\n"); printf("\033[41m-=Код %d=-\033[0m \n",
//   s21_mult_matrix(&A, &B, &result)); print_matrix(&result);
//   s21_remove_matrix(&A);
//   s21_remove_matrix(&B);
//   s21_remove_matrix(&result);
//   s21_remove_matrix(&mult_number);
//   return 0;
// }
