#include <check.h>

#include "s21_matrix.h"

START_TEST(compliment_test_1) {
  matrix_t A, B, R;
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &A);
  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[0][2] = 3;
  B.matrix[1][0] = 0;
  B.matrix[1][1] = 4;
  B.matrix[1][2] = 2;
  B.matrix[2][0] = 5;
  B.matrix[2][1] = 2;
  B.matrix[2][2] = 1;

  A.matrix[0][0] = 0;
  A.matrix[0][1] = 10;
  A.matrix[0][2] = -20;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = -14;
  A.matrix[1][2] = 8;
  A.matrix[2][0] = -8;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = 4;

  int code = s21_calc_complements(&B, &R);
  ck_assert_int_eq(s21_eq_matrix(&R, &A), SUCCESS);
  ck_assert_int_eq(code, OK);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&A);
}

END_TEST

START_TEST(compliment_test_2) {
  matrix_t A, B, R;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  A.matrix[0][0] = 5;
  A.matrix[0][1] = -1;
  A.matrix[0][2] = 1;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 1;
  A.matrix[2][1] = 0;
  A.matrix[2][2] = 3;

  s21_calc_complements(&A, &R);

  B.matrix[0][0] = 9;
  B.matrix[0][1] = -2;
  B.matrix[0][2] = -3;
  B.matrix[1][0] = 3;
  B.matrix[1][1] = 14;
  B.matrix[1][2] = -1;
  B.matrix[2][0] = -7;
  B.matrix[2][1] = -18;
  B.matrix[2][2] = 17;

  ck_assert_int_eq(s21_eq_matrix(&R, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}

END_TEST

START_TEST(compliment_test_not_square) {
  matrix_t B, R;
  s21_create_matrix(2, 3, &B);

  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[0][2] = 3;
  B.matrix[1][0] = 0;
  B.matrix[1][1] = 4;
  B.matrix[1][2] = 2;

  int code = s21_calc_complements(&B, &R);

  ck_assert_int_eq(code, CALC_ERROR);
  s21_remove_matrix(&B);
  // s21_remove_matrix(&R);
}

END_TEST

START_TEST(compliment_test_1x1) {
  matrix_t A, B, R;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);

  A.matrix[0][0] = 5;

  s21_calc_complements(&A, &R);

  B.matrix[0][0] = 5;

  ck_assert_int_eq(s21_eq_matrix(&R, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}

END_TEST

START_TEST(null_compliments) {
  matrix_t *B = NULL;
  matrix_t *R = NULL;
  int res = s21_calc_complements(B, R);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
}

END_TEST

START_TEST(create_test) {
  int rows = 10;
  int columns = 10;
  matrix_t matrix = {0};
  int code = s21_create_matrix(rows, columns, &matrix);

  if (matrix.matrix) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        ck_assert(fabs(matrix.matrix[i][j]) < 1e-7);
      }
    }
    ck_assert_int_eq(matrix.rows, rows);
    ck_assert_int_eq(matrix.columns, columns);
    ck_assert_int_eq(code, OK);
    // } else {
    //   ck_assert_int_eq(code, CALC_ERROR);
  }

  if (code == OK) s21_remove_matrix(&matrix);
}

END_TEST

START_TEST(create_test_incorrect) {
  int rows = -10;
  int columns = 10;
  matrix_t matrix = {0};
  int code = s21_create_matrix(rows, columns, &matrix);

  ck_assert_int_eq(code, INCORRECT_MATRIX);

  if (code == OK) s21_remove_matrix(&matrix);
}

END_TEST

START_TEST(determinant_test_1) {
  matrix_t A;
  double B, R = 1.25;
  s21_create_matrix(1, 1, &A);

  A.matrix[0][0] = 1.25;

  s21_determinant(&A, &B);

  ck_assert(fabs(B - R) < 1e-7);

  s21_remove_matrix(&A);
}

END_TEST

START_TEST(determinant_test_2) {
  matrix_t A;
  double B, R = -69;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 0.25;
  A.matrix[0][1] = 1.25;
  A.matrix[0][2] = 2.25;
  A.matrix[1][0] = 3.25;
  A.matrix[1][1] = 10;
  A.matrix[1][2] = 5.25;
  A.matrix[2][0] = 6.25;
  A.matrix[2][1] = 7.25;
  A.matrix[2][2] = 8.25;

  s21_determinant(&A, &B);

  ck_assert(fabs(B - R) < 1e-7);

  s21_remove_matrix(&A);
}

END_TEST

START_TEST(determinant_test_3x3_1) {
  matrix_t A;
  double B, R = -2;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 2;
  A.matrix[0][1] = 4;
  A.matrix[0][2] = -6;
  A.matrix[1][0] = -5;
  A.matrix[1][1] = -7;
  A.matrix[1][2] = 5;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 5;
  A.matrix[2][2] = -6;

  s21_determinant(&A, &B);

  ck_assert(fabs(B - R) < 1e-7);

  s21_remove_matrix(&A);
}

END_TEST

START_TEST(determinant_test_3x3_2) {
  matrix_t A;
  double B, R = 25;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = -3;
  A.matrix[0][1] = 4;
  A.matrix[0][2] = -6;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = -7;
  A.matrix[1][2] = 5;
  A.matrix[2][0] = -4;
  A.matrix[2][1] = 5;
  A.matrix[2][2] = -6;

  s21_determinant(&A, &B);

  ck_assert(fabs(B - R) < 1e-7);

  s21_remove_matrix(&A);
}

END_TEST

START_TEST(determinant_test_3x3_3) {
  matrix_t A;
  double B, R = 23;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = -3;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = -6;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = -5;
  A.matrix[1][2] = 5;
  A.matrix[2][0] = -4;
  A.matrix[2][1] = 3;
  A.matrix[2][2] = -6;

  s21_determinant(&A, &B);

  ck_assert(fabs(B - R) < 1e-7);

  s21_remove_matrix(&A);
}

END_TEST

START_TEST(determinant_test_3x3_4) {
  matrix_t A;
  double B, R = -8;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = -3;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 4;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = -5;
  A.matrix[1][2] = -7;
  A.matrix[2][0] = -4;
  A.matrix[2][1] = 3;
  A.matrix[2][2] = 5;

  s21_determinant(&A, &B);

  ck_assert(fabs(B - R) < 1e-7);

  s21_remove_matrix(&A);
}

END_TEST

START_TEST(determinant_test_4x4) {
  matrix_t A;
  double B, R = 18;
  s21_create_matrix(4, 4, &A);

  A.matrix[0][0] = 3;
  A.matrix[0][1] = -3;
  A.matrix[0][2] = -5;
  A.matrix[0][3] = 8;
  A.matrix[1][0] = -3;
  A.matrix[1][1] = 2;
  A.matrix[1][2] = 4;
  A.matrix[1][3] = -6;
  A.matrix[2][0] = 2;
  A.matrix[2][1] = -5;
  A.matrix[2][2] = -7;
  A.matrix[2][3] = 5;
  A.matrix[3][0] = -4;
  A.matrix[3][1] = 3;
  A.matrix[3][2] = 5;
  A.matrix[3][3] = -6;

  s21_determinant(&A, &B);

  ck_assert(fabs(B - R) < 1e-7);

  s21_remove_matrix(&A);
}

END_TEST

START_TEST(determinant_test_5x5) {
  matrix_t A;
  double B, R = -69.0 / 4.0;
  s21_create_matrix(5, 5, &A);

  A.matrix[0][0] = 0.25;
  A.matrix[0][1] = 1.25;
  A.matrix[0][2] = 2.25;
  A.matrix[0][3] = 3.25;
  A.matrix[0][4] = 2.25;
  A.matrix[1][0] = 3.25;
  A.matrix[1][1] = 10;
  A.matrix[1][2] = 5.25;
  A.matrix[1][3] = 5.25;
  A.matrix[1][4] = 5.25;
  A.matrix[2][0] = 6.25;
  A.matrix[2][1] = 7.25;
  A.matrix[2][2] = 8.25;
  A.matrix[2][3] = 6.25;
  A.matrix[2][4] = 6.25;
  A.matrix[3][0] = 6.25;
  A.matrix[3][1] = 7.25;
  A.matrix[3][2] = 8.25;
  A.matrix[3][3] = 6.25;
  A.matrix[3][4] = 7.25;
  A.matrix[4][0] = 6.25;
  A.matrix[4][1] = 7.25;
  A.matrix[4][2] = 8.25;
  A.matrix[4][3] = 6;
  A.matrix[4][4] = 8.25;

  s21_determinant(&A, &B);

  ck_assert(fabs(B - R) < 1e-7);

  s21_remove_matrix(&A);
}

END_TEST

START_TEST(determinant_not_square) {
  matrix_t A;
  double B;
  s21_create_matrix(4, 5, &A);
  int res = s21_determinant(&A, &B);
  ck_assert_int_eq(res, CALC_ERROR);
  s21_remove_matrix(&A);
}

END_TEST

START_TEST(determinant_test_4x4_2) {
  matrix_t a;
  double number;
  s21_create_matrix(4, 4, &a);
  a.matrix[0][0] = 1;
  a.matrix[0][1] = 2;
  a.matrix[0][2] = 3;
  a.matrix[0][3] = 13;
  a.matrix[1][0] = 4;
  a.matrix[1][1] = 5;
  a.matrix[1][2] = 6;
  a.matrix[1][3] = 16;
  a.matrix[2][0] = 7;
  a.matrix[2][1] = 8;
  a.matrix[2][2] = 90;
  a.matrix[2][3] = 19;
  a.matrix[3][0] = 1;
  a.matrix[3][1] = 7;
  a.matrix[3][2] = 7;
  a.matrix[3][3] = 17;

  s21_determinant(&a, &number);
  ck_assert_int_eq(number, 13608);
  s21_remove_matrix(&a);
}

END_TEST

START_TEST(null_determinate) {
  matrix_t *B = NULL;
  double re = 0;
  int res = s21_determinant(B, &re);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
}

END_TEST

START_TEST(eq_test_1) {
  matrix_t A, B;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);

  A.matrix[0][0] = 5;
  B.matrix[0][0] = 8.8;

  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

END_TEST

START_TEST(eq_test_2) {
  matrix_t A, B;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  A.matrix[0][0] = 0.25;
  A.matrix[0][1] = 1.25;
  A.matrix[0][2] = 2.25;
  A.matrix[1][0] = 3.25;
  A.matrix[1][1] = 4.25;
  A.matrix[1][2] = 5.25;
  A.matrix[2][0] = 6.25;
  A.matrix[2][1] = 7.25;
  A.matrix[2][2] = 8.25;

  B.matrix[0][0] = 0.25;
  B.matrix[0][1] = 1.25;
  B.matrix[0][2] = 2.25;
  B.matrix[1][0] = 3.25;
  B.matrix[1][1] = 4.25;
  B.matrix[1][2] = 5.25;
  B.matrix[2][0] = 6.25;
  B.matrix[2][1] = 7.25;
  B.matrix[2][2] = 8.25;

  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

END_TEST

START_TEST(eq_test_diff_size) {
  matrix_t A, B;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 3, &B);

  A.matrix[0][0] = 0.25;
  A.matrix[0][1] = 1.25;
  A.matrix[0][2] = 2.25;
  A.matrix[1][0] = 3.25;
  A.matrix[1][1] = 4.25;
  A.matrix[1][2] = 5.25;

  B.matrix[0][0] = 0.25;
  B.matrix[0][1] = 1.25;
  B.matrix[0][2] = 2.25;
  B.matrix[1][0] = 3.25;
  B.matrix[1][1] = 4.25;
  B.matrix[1][2] = 5.25;
  B.matrix[2][0] = 6.25;
  B.matrix[2][1] = 7.25;
  B.matrix[2][2] = 8.25;

  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

END_TEST

START_TEST(test_normal) {
  matrix_t m, B, R;
  s21_create_matrix(3, 3, &m);
  s21_create_matrix(3, 3, &B);

  m.matrix[0][0] = 2;
  m.matrix[0][1] = 5;
  m.matrix[0][2] = 7;
  m.matrix[1][0] = 6;
  m.matrix[1][1] = 3;
  m.matrix[1][2] = 4;
  m.matrix[2][0] = 5;
  m.matrix[2][1] = -2;
  m.matrix[2][2] = -3;

  B.matrix[0][0] = 1;
  B.matrix[0][1] = -1;
  B.matrix[0][2] = 1;
  B.matrix[1][0] = -38;
  B.matrix[1][1] = 41;
  B.matrix[1][2] = -34;
  B.matrix[2][0] = 27;
  B.matrix[2][1] = -29;
  B.matrix[2][2] = 24;

  int code = s21_inverse_matrix(&m, &R);

  ck_assert_int_eq(s21_eq_matrix(&R, &B), SUCCESS);
  ck_assert_int_eq(code, OK);
  s21_remove_matrix(&m);
  s21_remove_matrix(&R);
  s21_remove_matrix(&B);
}

END_TEST

START_TEST(test_not_sqare) {
  matrix_t m = {0};
  matrix_t result = {0};
  s21_create_matrix(1, 4, &m);
  int code = s21_inverse_matrix(&m, &result);
  ck_assert_int_eq(code, CALC_ERROR);
  s21_remove_matrix(&m);
  s21_remove_matrix(&result);
}

END_TEST

START_TEST(null_inverse) {
  matrix_t *B = NULL;
  matrix_t *R = NULL;
  int res = s21_inverse_matrix(B, R);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
}

END_TEST

START_TEST(zero_det) {
  matrix_t m = {0};
  matrix_t result = {0};
  s21_create_matrix(3, 3, &m);

  int code = s21_inverse_matrix(&m, &result);
  ck_assert_int_eq(code, CALC_ERROR);
  s21_remove_matrix(&m);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(incorrect_matrix_1) {
  matrix_t m1 = {0};
  matrix_t m2 = {0};
  s21_create_matrix(5, 5, &m1);
  s21_create_matrix(6, 6, &m2);

  matrix_t result = {0};
  int mul_code = s21_mult_matrix(&m1, &m2, &result);
  ck_assert_int_eq(mul_code, CALC_ERROR);

  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&result);
}

END_TEST

START_TEST(incorrect_matrix_2) {
  matrix_t m1 = {0};
  matrix_t m2 = {0};
  s21_create_matrix(5, 5, &m1);
  s21_create_matrix(6, 6, &m2);
  m1.columns = -100;

  matrix_t result = {0};
  int mul_code = s21_mult_matrix(&m1, &m2, &result);
  ck_assert_int_eq(mul_code, INCORRECT_MATRIX);

  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&result);
}

END_TEST

START_TEST(mult_matrix_test_1) {
  matrix_t A, B, R, R2;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  s21_create_matrix(1, 1, &R2);

  A.matrix[0][0] = -1;
  B.matrix[0][0] = 2;

  R2.matrix[0][0] = -2;

  s21_mult_matrix(&A, &B, &R);

  ck_assert(fabs(R.matrix[0][0] - R2.matrix[0][0]) < 1e-7);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&R2);
}

END_TEST

START_TEST(mult_matrix_test_2) {
  matrix_t A, B, R, R2;
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 3, &B);
  s21_create_matrix(3, 3, &R2);

  A.matrix[0][0] = 0;
  A.matrix[0][1] = 1;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;
  A.matrix[2][0] = 6;
  A.matrix[2][1] = 7;

  B.matrix[0][0] = 9;
  B.matrix[0][1] = 8;
  B.matrix[0][2] = 7;
  B.matrix[1][0] = 6;
  B.matrix[1][1] = 5;
  B.matrix[1][2] = 4;

  R2.matrix[0][0] = 6;
  R2.matrix[0][1] = 5;
  R2.matrix[0][2] = 4;
  R2.matrix[1][0] = 51;
  R2.matrix[1][1] = 44;
  R2.matrix[1][2] = 37;
  R2.matrix[2][0] = 96;
  R2.matrix[2][1] = 83;
  R2.matrix[2][2] = 70;

  s21_mult_matrix(&A, &B, &R);

  ck_assert_int_eq(s21_eq_matrix(&R, &R2), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&R2);
}

END_TEST

START_TEST(mult_matrix_test_3) {
  matrix_t A, B, R, R2;
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 4, &B);
  s21_create_matrix(3, 4, &R2);

  A.matrix[0][0] = 0;
  A.matrix[0][1] = 1;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;
  A.matrix[2][0] = 6;
  A.matrix[2][1] = 7;

  B.matrix[0][0] = 9;
  B.matrix[0][1] = 8;
  B.matrix[0][2] = 7;
  B.matrix[0][3] = 7;
  B.matrix[1][0] = 6;
  B.matrix[1][1] = 5;
  B.matrix[1][2] = 4;
  B.matrix[1][3] = 7;

  R2.matrix[0][0] = 6;
  R2.matrix[0][1] = 5;
  R2.matrix[0][2] = 4;
  R2.matrix[0][3] = 7;
  R2.matrix[1][0] = 51;
  R2.matrix[1][1] = 44;
  R2.matrix[1][2] = 37;
  R2.matrix[1][3] = 49;
  R2.matrix[2][0] = 96;
  R2.matrix[2][1] = 83;
  R2.matrix[2][2] = 70;
  R2.matrix[2][3] = 91;

  s21_mult_matrix(&A, &B, &R);

  ck_assert_int_eq(s21_eq_matrix(&R, &R2), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&R2);
}

END_TEST

START_TEST(null_mult_mat) {
  matrix_t *A = NULL;
  matrix_t *B = NULL;
  matrix_t *R = NULL;
  int res = s21_mult_matrix(A, B, R);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
}

END_TEST

START_TEST(mult_number_test_1) {
  matrix_t A, R, R2;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &R2);

  A.matrix[0][0] = 1.25;

  R2.matrix[0][0] = -5;

  s21_mult_number(&A, -4, &R);

  ck_assert(fabs(R.matrix[0][0] - R2.matrix[0][0]) < 1e-7);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&R2);
}

END_TEST

START_TEST(mult_number_test_2) {
  matrix_t A, R, R2;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &R2);

  A.matrix[0][0] = 0.25;
  A.matrix[0][1] = 1.25;
  A.matrix[0][2] = 2.25;
  A.matrix[1][0] = 3.25;
  A.matrix[1][1] = 4.25;
  A.matrix[1][2] = 5.25;
  A.matrix[2][0] = 6.25;
  A.matrix[2][1] = 7.25;
  A.matrix[2][2] = 8.25;

  R2.matrix[0][0] = 1;
  R2.matrix[0][1] = 5;
  R2.matrix[0][2] = 9;
  R2.matrix[1][0] = 13;
  R2.matrix[1][1] = 17;
  R2.matrix[1][2] = 21;
  R2.matrix[2][0] = 25;
  R2.matrix[2][1] = 29;
  R2.matrix[2][2] = 33;

  s21_mult_number(&A, 4, &R);

  ck_assert_int_eq(s21_eq_matrix(&R, &R2), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&R2);
}

END_TEST

START_TEST(mult_number_test_3) {
  matrix_t A, R, R2;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &R2);

  A.matrix[0][0] = 0.25;
  A.matrix[0][1] = 1.25;
  A.matrix[0][2] = 2.25;
  A.matrix[1][0] = 3.25;
  A.matrix[1][1] = 4.25;
  A.matrix[1][2] = 5.25;

  R2.matrix[0][0] = 1;
  R2.matrix[0][1] = 5;
  R2.matrix[0][2] = 9;
  R2.matrix[1][0] = 13;
  R2.matrix[1][1] = 17;
  R2.matrix[1][2] = 21;

  s21_mult_number(&A, 4, &R);

  ck_assert_int_eq(s21_eq_matrix(&R, &R2), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&R2);
}
END_TEST

START_TEST(null_mult_num) {
  matrix_t *B = NULL;
  double num = 0;
  matrix_t *R = NULL;
  int res = s21_mult_number(B, num, R);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
}

END_TEST

START_TEST(remove_test) {
  int rows = 100;
  int columns = 100;
  matrix_t matrix = {0};
  int code = s21_create_matrix(rows, columns, &matrix);
  if (code == OK) {
    s21_remove_matrix(&matrix);
    ck_assert_ptr_eq(matrix.matrix, NULL);
    ck_assert_int_eq(matrix.rows, 0);
    ck_assert_int_eq(matrix.columns, 0);
  }
}

END_TEST

START_TEST(sub_test_1) {
  matrix_t A, B, R, R2;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  s21_create_matrix(1, 1, &R2);

  A.matrix[0][0] = 1.25;
  B.matrix[0][0] = 2.25;

  R2.matrix[0][0] = -1;

  s21_sub_matrix(&A, &B, &R);

  ck_assert(fabs(R.matrix[0][0] - R2.matrix[0][0]) < 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&R2);
}

END_TEST

START_TEST(sub_test_2) {
  matrix_t A, B, R, R2;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &R2);

  A.matrix[0][0] = 0.25;
  A.matrix[0][1] = 1.25;
  A.matrix[0][2] = 2.25;
  A.matrix[1][0] = 3.25;
  A.matrix[1][1] = 4.25;
  A.matrix[1][2] = 5.25;
  A.matrix[2][0] = 6.25;
  A.matrix[2][1] = 7.25;
  A.matrix[2][2] = 8.25;

  B.matrix[0][0] = 9.25;
  B.matrix[0][1] = 8.25;
  B.matrix[0][2] = 7.25;
  B.matrix[1][0] = 6.25;
  B.matrix[1][1] = 5.25;
  B.matrix[1][2] = 4.25;
  B.matrix[2][0] = 3.25;
  B.matrix[2][1] = 2.25;
  B.matrix[2][2] = 1.25;

  R2.matrix[0][0] = -9.0;
  R2.matrix[0][1] = -7.0;
  R2.matrix[0][2] = -5.0;
  R2.matrix[1][0] = -3.0;
  R2.matrix[1][1] = -1.0;
  R2.matrix[1][2] = 1.0;
  R2.matrix[2][0] = 3.0;
  R2.matrix[2][1] = 5.0;
  R2.matrix[2][2] = 7.0;

  s21_sub_matrix(&A, &B, &R);

  ck_assert_int_eq(s21_eq_matrix(&R, &R2), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&R2);
}

END_TEST

START_TEST(sub_test_incorrect_matrix) {
  matrix_t A, B, R;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(2, 1, &B);

  A.matrix[0][0] = 1.25;
  B.matrix[0][0] = 2.25;

  int res = s21_sub_matrix(&A, &B, &R);

  ck_assert_int_eq(res, CALC_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  // s21_remove_matrix(&R);
}

END_TEST

START_TEST(null_sub) {
  matrix_t *A = NULL;
  matrix_t *B = NULL;
  matrix_t *R = NULL;
  int res = s21_sub_matrix(A, B, R);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
}

END_TEST

START_TEST(sum_test_1) {
  matrix_t A, B, R, R2;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  s21_create_matrix(1, 1, &R2);

  A.matrix[0][0] = 1.25;
  B.matrix[0][0] = 2.25;

  R2.matrix[0][0] = 3.5;

  s21_sum_matrix(&A, &B, &R);

  ck_assert(fabs(R.matrix[0][0] - R2.matrix[0][0]) < 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&R2);
}

END_TEST

START_TEST(sum_test_2) {
  matrix_t A, B, R, R2;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &R2);

  A.matrix[0][0] = 0.25;
  A.matrix[0][1] = 1.25;
  A.matrix[0][2] = 2.25;
  A.matrix[1][0] = 3.25;
  A.matrix[1][1] = 4.25;
  A.matrix[1][2] = 5.25;
  A.matrix[2][0] = 6.25;
  A.matrix[2][1] = 7.25;
  A.matrix[2][2] = 8.25;

  B.matrix[0][0] = 9.65;
  B.matrix[0][1] = 8.65;
  B.matrix[0][2] = 7.65;
  B.matrix[1][0] = 6.65;
  B.matrix[1][1] = 5.65;
  B.matrix[1][2] = 4.65;
  B.matrix[2][0] = 3.65;
  B.matrix[2][1] = 2.65;
  B.matrix[2][2] = 1.65;

  R2.matrix[0][0] = 9.9;
  R2.matrix[0][1] = 9.9;
  R2.matrix[0][2] = 9.9;
  R2.matrix[1][0] = 9.9;
  R2.matrix[1][1] = 9.9;
  R2.matrix[1][2] = 9.9;
  R2.matrix[2][0] = 9.9;
  R2.matrix[2][1] = 9.9;
  R2.matrix[2][2] = 9.9;

  s21_sum_matrix(&A, &B, &R);

  ck_assert_int_eq(s21_eq_matrix(&R, &R2), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&R2);
}

END_TEST

START_TEST(sum_test_incorrect_matrix) {
  matrix_t A, B, R;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(2, 1, &B);

  A.matrix[0][0] = 1.25;
  B.matrix[0][0] = 2.25;

  int res = s21_sum_matrix(&A, &B, &R);

  ck_assert_int_eq(res, CALC_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  // s21_remove_matrix(&R);
}

END_TEST

START_TEST(null_sum) {
  matrix_t *A = NULL;
  matrix_t *B = NULL;
  matrix_t *R = NULL;
  int res = s21_sum_matrix(A, B, R);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
}

END_TEST

START_TEST(transpose_test_1) {
  matrix_t A, B, R;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);

  A.matrix[0][0] = 1.25;
  B.matrix[0][0] = 1.25;

  s21_transpose(&A, &R);
  ck_assert_int_eq(s21_eq_matrix(&R, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}

END_TEST

START_TEST(transpose_test_2) {
  matrix_t A, B, R;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  A.matrix[0][0] = 0.25;
  A.matrix[0][1] = 1.25;
  A.matrix[0][2] = 2.25;
  A.matrix[1][0] = 3.25;
  A.matrix[1][1] = 4.25;
  A.matrix[1][2] = 5.25;
  A.matrix[2][0] = 6.25;
  A.matrix[2][1] = 7.25;
  A.matrix[2][2] = 8.25;

  s21_transpose(&A, &R);

  B.matrix[0][0] = 0.25;
  B.matrix[1][0] = 1.25;
  B.matrix[2][0] = 2.25;
  B.matrix[0][1] = 3.25;
  B.matrix[1][1] = 4.25;
  B.matrix[2][1] = 5.25;
  B.matrix[0][2] = 6.25;
  B.matrix[1][2] = 7.25;
  B.matrix[2][2] = 8.25;

  ck_assert_int_eq(s21_eq_matrix(&R, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}

END_TEST

START_TEST(transpose_incorrect) {
  matrix_t A, B;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  A.columns = -1;

  int ret = s21_transpose(&A, &B);
  ck_assert_int_eq(ret, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

END_TEST

START_TEST(null_transpose) {
  matrix_t *B = NULL;
  matrix_t *R = NULL;
  int res = s21_transpose(B, R);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
}

END_TEST

//? test s21_create_matrix

START_TEST(test1_create) {
  matrix_t a;
  int code = s21_create_matrix(2, 2, &a);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(a.columns, 2);
  ck_assert_int_eq(a.rows, 2);
  ck_assert_ptr_nonnull(a.matrix);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test2_create) {
  matrix_t a;
  int code = s21_create_matrix(3, 3, &a);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(a.columns, 3);
  ck_assert_int_eq(a.rows, 3);
  ck_assert_ptr_nonnull(a.matrix);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test3_create) {
  matrix_t a;
  int code = s21_create_matrix(4, 4, &a);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(a.columns, 4);
  ck_assert_int_eq(a.rows, 4);
  ck_assert_ptr_nonnull(a.matrix);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test4_create) {
  matrix_t a;
  int code = s21_create_matrix(5, 5, &a);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(a.columns, 5);
  ck_assert_int_eq(a.rows, 5);
  ck_assert_ptr_nonnull(a.matrix);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test5_create) {
  matrix_t a;
  int code = s21_create_matrix(0, 0, &a);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(a.columns, 0);
  ck_assert_int_eq(a.rows, 0);
  ck_assert_ptr_nonnull(a.matrix);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test6_create) {
  matrix_t a;
  int code = s21_create_matrix(-3, 3, &a);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test7_create) {
  matrix_t a;
  int code = s21_create_matrix(3, -3, &a);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test8_create) {
  matrix_t a;
  int code = s21_create_matrix(-3, -3, &a);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test9_create) {
  ck_assert_int_eq(s21_create_matrix(3, 3, NULL), INCORRECT_MATRIX);
}
END_TEST

//? test s21_eq_matrix

START_TEST(test1_eq) {
  matrix_t a, b;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &b);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{
                                1.,
                                2.,
                                3.,
                            },
                            {3., 2., 1.},
                            {7., 5., 2.}};
  double content_b[3][3] = {{
                                1.,
                                2.,
                                3.,
                            },
                            {3., 1., 1.},
                            {7., 5., 2.}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];

  ck_assert_int_eq(s21_eq_matrix(&a, &b), 0);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST
START_TEST(test2_eq) {
  matrix_t a, b;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &b);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{0.13807, 4.10035, 7.04436},
                            {5.32393, 1.70957, 5.99774},
                            {3.47567, 6.88200, 0.32512}};
  double content_b[3][3] = {{7.02544, 3.70872, 2.13794},
                            {7.02544, 3.70872, 2.13794},
                            {7.02544, 3.70872, 2.13794}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];

  ck_assert_int_eq(s21_eq_matrix(&a, &b), 0);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST
START_TEST(test3_eq) {
  matrix_t a, b;
  int code = s21_create_matrix(4, 4, &a);
  code += s21_create_matrix(4, 4, &b);
  ck_assert_int_eq(code, 0);
  double content_a[4][4] = {{1.80377, 3.93870, 3.13429, 2.28155},
                            {1.39307, 1.05586, 2.21357, 2.20440},
                            {2.74323, 2.41325, 3.86805, 2.73013},
                            {2.74323, 2.41325, 3.86805, 2.73013}};
  double content_b[4][4] = {{1.26273, 1.04840, 3.52904, 2.43282},
                            {3.77110, 3.91306, 2.02829, 2.98469},
                            {1.57829, 1.88621, 1.51431, 2.45186},
                            {3.68725, 2.39301, 1.84984, 2.48786}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];

  ck_assert_int_eq(s21_eq_matrix(&a, &b), 0);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST
START_TEST(test4_eq) {
  matrix_t a, b;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &b);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{
                                1.,
                                2.,
                                3.,
                            },
                            {2., 4., 6.},
                            {7., 5., 2.}};
  double content_b[3][3] = {{
                                1.,
                                2.,
                                3.,
                            },
                            {2., 4., 6.},
                            {7., 5., 2.}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];

  ck_assert_int_eq(s21_eq_matrix(&a, &b), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST
START_TEST(test5_eq) {
  matrix_t a, b;
  int code = s21_create_matrix(4, 4, &a);
  code += s21_create_matrix(4, 4, &b);
  ck_assert_int_eq(code, 0);
  double content_a[4][4] = {{1.80377, 3.93870, 3.13429, 2.28155},
                            {1.39307, 1.05586, 2.21357, 2.20440},
                            {2.74323, 2.41325, 3.86805, 2.73013},
                            {2.74323, 2.41325, 3.86805, 2.73013}};
  double content_b[4][4] = {{1.80377, 3.93870, 3.13429, 2.28155},
                            {1.39307, 1.05586, 2.21357, 2.20440},
                            {2.74323, 2.41325, 3.86805, 2.73013},
                            {2.74323, 2.41325, 3.86805, 2.73013}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];

  ck_assert_int_eq(s21_eq_matrix(&a, &b), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST
START_TEST(test6_eq) {
  matrix_t a, b;
  int code = s21_create_matrix(3, 4, &a);
  code += s21_create_matrix(3, 4, &b);
  ck_assert_int_eq(code, 0);
  double content_a[3][4] = {{2.87301, 2.61453, 2.29238, 3.50759},
                            {2.40913, 3.85765, 3.61554, 1.32832},
                            {1.29258, 1.91210, 2.73817, 3.27839}};
  double content_b[3][4] = {{2.33717, 1.05745, 1.54393, 3.49827},
                            {3.77880, 3.53064, 2.34638, 1.33020},
                            {1.06036, 2.70443, 2.43779, 2.89379}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) *(a.matrix[y] + x) = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];

  ck_assert_int_eq(s21_eq_matrix(&a, &b), 0);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST
START_TEST(test7_eq) {
  matrix_t a, b;
  int code = s21_create_matrix(3, 4, &a);
  code += s21_create_matrix(3, 4, &b);
  ck_assert_int_eq(code, 0);
  double content_a[3][4] = {{2.87301, 2.61453, 2.29238, 3.50759},
                            {2.40913, 3.85765, 3.61554, 1.32832},
                            {1.29258, 1.91210, 2.73817, 3.27839}};
  double content_b[3][4] = {{2.87301, 2.61453, 2.29238, 3.50759},
                            {2.40913, 3.85765, 3.61554, 1.32832},
                            {1.29258, 1.91210, 2.73817, 3.27839}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) *(a.matrix[y] + x) = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];

  ck_assert_int_eq(s21_eq_matrix(&a, &b), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST
START_TEST(test8_eq) {
  matrix_t a, b;
  int code = s21_create_matrix(3, 4, &a);
  code += s21_create_matrix(4, 3, &b);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&a, &b), 0);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST
END_TEST
START_TEST(test9_eq) {
  matrix_t a, b;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &b);
  a.rows = -1;
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&a, &b), 0);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST
START_TEST(test10_eq) {
  matrix_t a, b;
  int code = s21_create_matrix(3, 3, &a);
  b.matrix = NULL;
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&a, &b), 0);
  s21_remove_matrix(&a);
}
END_TEST
START_TEST(test11_eq) { ck_assert_int_eq(s21_eq_matrix(NULL, NULL), 0); }
END_TEST

START_TEST(test12_eq) {
  matrix_t a, b;
  int code = s21_create_matrix(0, 0, &a);
  code += s21_create_matrix(0, 0, &b);
  ck_assert_int_eq(code, 0);

  ck_assert_int_eq(s21_eq_matrix(&a, &b), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(test13_eq) {
  matrix_t a, b;
  int code = s21_create_matrix(0, 0, &a);
  code += s21_create_matrix(1, 0, &b);
  ck_assert_int_eq(code, 0);

  ck_assert_int_eq(s21_eq_matrix(&a, &b), 0);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

//! test s21_sum_matrix

START_TEST(test1_sum) {
  matrix_t a, b, r, e;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &b);
  code += s21_create_matrix(3, 3, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{
                                1.,
                                2.,
                                3.,
                            },
                            {3., 2., 1.},
                            {7., 5., 2.}};
  double content_b[3][3] = {{
                                1.,
                                2.,
                                3.,
                            },
                            {3., 2., 1.},
                            {7., 5., 2.}};
  double content_e[3][3] = {{
                                2.,
                                4.,
                                6.,
                            },
                            {6., 4., 2.},
                            {14., 10., 4.}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_sum_matrix(&a, &b, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test2_sum) {
  matrix_t a, b, r, e;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &b);
  code += s21_create_matrix(3, 3, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{0.13807, 4.10035, 7.04436},
                            {5.32393, 1.70957, 5.99774},
                            {3.47567, 6.88200, 0.32512}};
  double content_b[3][3] = {{7.02544, 3.70872, 2.13794},
                            {7.02544, 3.70872, 2.13794},
                            {7.02544, 3.70872, 2.13794}};
  double content_e[3][3] = {{7.16351, 7.80907, 9.1823},
                            {12.34937, 5.41829, 8.13568},
                            {10.50111, 10.59072, 2.46306}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_sum_matrix(&a, &b, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&r, &e), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test3_sum) {
  matrix_t a, b, r, e;
  int code = s21_create_matrix(4, 4, &a);
  code += s21_create_matrix(4, 4, &b);
  code += s21_create_matrix(4, 4, &e);
  ck_assert_int_eq(code, 0);
  double content_a[4][4] = {{1.80377, 3.93870, 3.13429, 2.28155},
                            {1.39307, 1.05586, 2.21357, 2.20440},
                            {2.74323, 2.41325, 3.86805, 2.73013},
                            {2.74323, 2.41325, 3.86805, 2.73013}};
  double content_b[4][4] = {{1.26273, 1.04840, 3.52904, 2.43282},
                            {3.77110, 3.91306, 2.02829, 2.98469},
                            {1.57829, 1.88621, 1.51431, 2.45186},
                            {3.68725, 2.39301, 1.84984, 2.48786}};
  double content_e[4][4] = {{3.0665, 4.9871, 6.66333, 4.71437},
                            {5.16417, 4.96892, 4.24186, 5.18909},
                            {4.32152, 4.29946, 5.38236, 5.18199},
                            {6.43048, 4.80626, 5.71789, 5.21799}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_sum_matrix(&a, &b, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&r, &e), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test4_sum) {
  matrix_t a, b, r, e;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &b);
  code += s21_create_matrix(3, 3, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{
                                1.,
                                2.,
                                3.,
                            },
                            {2., 4., 6.},
                            {7., 5., 2.}};
  double content_b[3][3] = {{
                                1.,
                                2.,
                                3.,
                            },
                            {4., 5., 6.},
                            {7., 8., 9.}};
  double content_e[3][3] = {{
                                2.,
                                4.,
                                6.,
                            },
                            {6., 9., 12.},
                            {14., 13., 11.}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_sum_matrix(&a, &b, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&r, &e), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test5_sum) {
  matrix_t a, b, r, e;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &b);
  code += s21_create_matrix(3, 3, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{
                                1.,
                                2.,
                                3.,
                            },
                            {4., 5., 6.},
                            {7., 8., 9.}};
  double content_b[3][3] = {{
                                1.,
                                2.,
                                3.,
                            },
                            {3., 2., 1.},
                            {7., 5., 2.}};
  double content_e[3][3] = {{
                                2.,
                                4.,
                                6.,
                            },
                            {7., 7., 7.},
                            {14., 13., 11.}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_sum_matrix(&a, &b, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&r, &e), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test6_sum) {
  matrix_t a, b, r, e;
  int code = s21_create_matrix(3, 4, &a);
  code += s21_create_matrix(3, 4, &b);
  code += s21_create_matrix(3, 4, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][4] = {{2.87301, 2.61453, 2.29238, 3.50759},
                            {2.40913, 3.85765, 3.61554, 1.32832},
                            {1.29258, 1.91210, 2.73817, 3.27839}};
  double content_b[3][4] = {{2.33717, 1.05745, 1.54393, 3.49827},
                            {3.77880, 3.53064, 2.34638, 1.33020},
                            {1.06036, 2.70443, 2.43779, 2.89379}};
  double content_e[3][4] = {{5.21018, 3.67198, 3.83631, 7.00586},
                            {6.18793, 7.38829, 5.96192, 2.65852},
                            {2.35294, 4.61653, 5.17596, 6.17218}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) *(a.matrix[y] + x) = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_sum_matrix(&a, &b, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test7_sum) {
  matrix_t a, b, r;
  int code = s21_create_matrix(3, 4, &a);
  code += s21_create_matrix(4, 3, &b);
  ck_assert_int_eq(code, 0);
  code = s21_sum_matrix(&a, &b, &r);
  ck_assert_int_eq(code, CALC_ERROR);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(test8_sum) {
  matrix_t a, b;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &b);
  ck_assert_int_eq(code, 0);
  code = s21_sum_matrix(&a, &b, NULL);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(test9_sum) {
  matrix_t a, b, r;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &b);
  a.rows = -1;
  ck_assert_int_eq(code, 0);
  code = s21_sum_matrix(&a, &b, &r);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(test10_sum) {
  matrix_t a, b, r;
  int code = s21_create_matrix(3, 3, &a);
  b.matrix = NULL;
  ck_assert_int_eq(code, 0);
  code = s21_sum_matrix(&a, &b, &r);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
  s21_remove_matrix(&a);
}
END_TEST

//! test s21_sub_matrix

START_TEST(test1_sub) {
  matrix_t a, b, r, e;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &b);
  code += s21_create_matrix(3, 3, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{
                                1.,
                                2.,
                                3.,
                            },
                            {3., 2., 1.},
                            {7., 5., 2.}};
  double content_b[3][3] = {{
                                1.,
                                2.,
                                3.,
                            },
                            {3., 2., 1.},
                            {7., 5., 2.}};
  double content_e[3][3] = {{0}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_sub_matrix(&a, &b, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test2_sub) {
  matrix_t a, b, r, e;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &b);
  code += s21_create_matrix(3, 3, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{0.13807, 4.10035, 7.04436},
                            {5.32393, 1.70957, 5.99774},
                            {3.47567, 6.88200, 0.32512}};
  double content_b[3][3] = {{7.02544, 3.70872, 2.13794},
                            {7.02544, 3.70872, 2.13794},
                            {7.02544, 3.70872, 2.13794}};
  double content_e[3][3] = {{-6.88737, 0.39163, 4.90642},
                            {-1.70151, -1.99915, 3.8598},
                            {-3.54977, 3.17328, -1.81282}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_sub_matrix(&a, &b, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&r, &e), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test3_sub) {
  matrix_t a, b, r, e;
  int code = s21_create_matrix(4, 4, &a);
  code += s21_create_matrix(4, 4, &b);
  code += s21_create_matrix(4, 4, &e);
  ck_assert_int_eq(code, 0);
  double content_a[4][4] = {{1.80377, 3.93870, 3.13429, 2.28155},
                            {1.39307, 1.05586, 2.21357, 2.20440},
                            {2.74323, 2.41325, 3.86805, 2.73013},
                            {2.74323, 2.41325, 3.86805, 2.73013}};
  double content_b[4][4] = {{1.26273, 1.04840, 3.52904, 2.43282},
                            {3.77110, 3.91306, 2.02829, 2.98469},
                            {1.57829, 1.88621, 1.51431, 2.45186},
                            {3.68725, 2.39301, 1.84984, 2.48786}};
  double content_e[4][4] = {{0.54104, 2.8903, -0.39475, -0.15127},
                            {-2.37803, -2.8572, 0.18528, -0.78029},
                            {1.16494, 0.52704, 2.35374, 0.27827},
                            {-0.94402, 0.02024, 2.01821, 0.24227}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_sub_matrix(&a, &b, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&r, &e), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test4_sub) {
  matrix_t a, b, r, e;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &b);
  code += s21_create_matrix(3, 3, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{
                                1.,
                                2.,
                                3.,
                            },
                            {2., 4., 6.},
                            {7., 5., 2.}};
  double content_b[3][3] = {{
                                1.,
                                2.,
                                3.,
                            },
                            {4., 5., 6.},
                            {7., 8., 9.}};
  double content_e[3][3] = {{
                                0.,
                                0.,
                                0.,
                            },
                            {-2., -1., 0.},
                            {0., -3., -7.}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_sub_matrix(&a, &b, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&r, &e), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test5_sub) {
  matrix_t a, b, r, e;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &b);
  code += s21_create_matrix(3, 3, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{
                                1.,
                                2.,
                                3.,
                            },
                            {4., 5., 6.},
                            {7., 8., 9.}};
  double content_b[3][3] = {{
                                1.,
                                2.,
                                3.,
                            },
                            {3., 2., 1.},
                            {7., 5., 2.}};
  double content_e[3][3] = {{
                                0.,
                                0.,
                                0.,
                            },
                            {1., 3., 5.},
                            {0., 3., 7.}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_sub_matrix(&a, &b, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&r, &e), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test6_sub) {
  matrix_t a, b, r, e;
  int code = s21_create_matrix(3, 4, &a);
  code += s21_create_matrix(3, 4, &b);
  code += s21_create_matrix(3, 4, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][4] = {{2.87301, 2.61453, 2.29238, 3.50759},
                            {2.40913, 3.85765, 3.61554, 1.32832},
                            {1.29258, 1.91210, 2.73817, 3.27839}};
  double content_b[3][4] = {{2.33717, 1.05745, 1.54393, 3.49827},
                            {3.77880, 3.53064, 2.34638, 1.33020},
                            {1.06036, 2.70443, 2.43779, 2.89379}};
  double content_e[3][4] = {{0.53584, 1.55708, 0.74845, 0.00932},
                            {-1.36967, 0.32701, 1.26916, -0.00188},
                            {0.23222, -0.79233, 0.30038, 0.3846}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) *(a.matrix[y] + x) = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_sub_matrix(&a, &b, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test7_sub) {
  matrix_t a, b, r;
  int code = s21_create_matrix(3, 4, &a);
  code += s21_create_matrix(4, 3, &b);
  ck_assert_int_eq(code, 0);
  code = s21_sub_matrix(&a, &b, &r);
  ck_assert_int_eq(code, CALC_ERROR);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(test8_sub) {
  matrix_t a, b;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &b);
  ck_assert_int_eq(code, 0);
  code = s21_sub_matrix(&a, &b, NULL);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(test9_sub) {
  matrix_t a, b, r;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &b);
  a.rows = -1;
  ck_assert_int_eq(code, 0);
  code = s21_sub_matrix(&a, &b, &r);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(test10_sub) {
  matrix_t a, b, r;
  int code = s21_create_matrix(3, 3, &a);
  b.matrix = NULL;
  ck_assert_int_eq(code, 0);
  code = s21_sub_matrix(&a, &b, &r);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
  s21_remove_matrix(&a);
}
END_TEST

//! test s21_mult_number

START_TEST(test1_mul_num) {
  matrix_t a, r, e;
  double m = 2.;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{
                                1.,
                                2.,
                                3.,
                            },
                            {3., 2., 1.},
                            {7., 5., 2.}};
  double content_e[3][3] = {{
                                2.,
                                4.,
                                6.,
                            },
                            {6., 4., 2.},
                            {14., 10., 4.}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_mult_number(&a, m, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test2_mul_num) {
  matrix_t a, r, e;
  double m = 0.7;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{0.13807, 4.10035, 7.04436},
                            {5.32393, 1.70957, 5.99774},
                            {3.47567, 6.88200, 0.32512}};
  double content_e[3][3] = {{0.0966490000, 2.8702450000, 4.9310520000},
                            {3.7267510000, 1.1966990000, 4.1984180000},
                            {2.4329690000, 4.8174000000, 0.2275840000}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_mult_number(&a, m, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test3_mul_num) {
  matrix_t a, r, e;
  double m = 0.7;
  int code = s21_create_matrix(4, 4, &a);
  code += s21_create_matrix(4, 4, &e);
  ck_assert_int_eq(code, 0);
  double content_a[4][4] = {{1.80377, 3.93870, 3.13429, 2.28155},
                            {1.39307, 1.05586, 2.21357, 2.20440},
                            {2.74323, 2.41325, 3.86805, 2.73013},
                            {2.74323, 2.41325, 3.86805, 2.73013}};
  double content_e[4][4] = {
      {1.2626390000, 2.7570900000, 2.1940030000, 1.5970850000},
      {0.9751490000, 0.7391020000, 1.5494990000, 1.5430800000},
      {1.9202610000, 1.6892750000, 2.7076350000, 1.9110910000},
      {1.9202610000, 1.6892750000, 2.7076350000, 1.9110910000}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_mult_number(&a, m, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test4_mul_num) {
  matrix_t a, r, e;
  double m = 0.7;
  int code = s21_create_matrix(3, 4, &a);
  code += s21_create_matrix(3, 4, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][4] = {{1.80377, 3.93870, 3.13429, 2.28155},
                            {1.39307, 1.05586, 2.21357, 2.20440},
                            {2.74323, 2.41325, 3.86805, 2.73013}};
  double content_e[3][4] = {
      {1.2626390000, 2.7570900000, 2.1940030000, 1.5970850000},
      {0.9751490000, 0.7391020000, 1.5494990000, 1.5430800000},
      {1.9202610000, 1.6892750000, 2.7076350000, 1.9110910000}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_mult_number(&a, m, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test5_mul_num) {
  matrix_t a, r, e;
  double m = 0;
  int code = s21_create_matrix(3, 4, &a);
  code += s21_create_matrix(3, 4, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][4] = {{1.80377, 3.93870, 3.13429, 2.28155},
                            {1.39307, 1.05586, 2.21357, 2.20440},
                            {2.74323, 2.41325, 3.86805, 2.73013}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];

  code = s21_mult_number(&a, m, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test6_mul_num) {
  matrix_t a, r;
  double m = 0;
  int code = s21_create_matrix(3, 4, &a);
  ck_assert_int_eq(code, 0);
  a.columns = -1;

  code = s21_mult_number(&a, m, &r);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
  s21_remove_matrix(&a);
}
END_TEST
START_TEST(test7_mul_num) {
  ck_assert_int_eq(s21_mult_number(NULL, 1.3, NULL), INCORRECT_MATRIX);
}
END_TEST

//! test s21_mult_matrix

START_TEST(test1_mult_matr) {
  matrix_t a, b, r, e;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &b);
  code += s21_create_matrix(3, 3, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{1., 2., 3.}, {3., 2., 1.}, {7., 5., 2.}};
  double content_b[3][3] = {{1., 2., 3.}, {3., 2., 1.}, {7., 5., 2.}};
  double content_e[3][3] = {{28, 21, 11}, {16, 15, 13}, {36, 34, 30}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_mult_matrix(&a, &b, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test2_mult_matr) {
  matrix_t a, b, r, e;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &b);
  code += s21_create_matrix(3, 3, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{0.13807, 4.10035, 7.04436},
                            {5.32393, 1.70957, 5.99774},
                            {3.47567, 6.88200, 0.32512}};
  double content_b[3][3] = {{7.02544, 3.70872, 2.13794},
                            {7.02544, 3.70872, 2.13794},
                            {7.02544, 3.70872, 2.13794}};
  double content_e[3][3] = {{79.2664939, 41.8446718, 24.1219067},
                            {91.5501947, 48.3292204, 27.8600092},
                            {75.0513002, 39.6194769, 22.8391641}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_mult_matrix(&a, &b, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&r, &e), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test3_mult_matr) {
  matrix_t a, b, r, e;
  int code = s21_create_matrix(4, 4, &a);
  code += s21_create_matrix(4, 4, &b);
  code += s21_create_matrix(4, 4, &e);
  ck_assert_int_eq(code, 0);
  double content_a[4][4] = {{1.80377, 3.93870, 3.13429, 2.28155},
                            {1.39307, 1.05586, 2.21357, 2.20440},
                            {2.74323, 2.41325, 3.86805, 2.73013},
                            {2.74323, 2.41325, 3.86805, 2.73013}};
  double content_b[4][4] = {{1.26273, 1.04840, 3.52904, 2.43282},
                            {3.77110, 3.91306, 2.02829, 2.98469},
                            {1.57829, 1.88621, 1.51431, 2.45186},
                            {3.68725, 2.39301, 1.84984, 2.48786}};
  double content_e[4][4] = {{30.4903699, 28.6751430, 23.3211914, 29.5050635},
                            {17.3626542, 15.0425472, 14.4876085, 17.4521057},
                            {28.7361424, 26.1483774, 25.4834697, 30.1526862},
                            {28.7361424, 26.1483774, 25.4834697, 30.1526862}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_mult_matrix(&a, &b, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&r, &e), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test4_mult_matr) {
  matrix_t a, b, r, e;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &b);
  code += s21_create_matrix(3, 3, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{
                                1.,
                                2.,
                                3.,
                            },
                            {2., 4., 6.},
                            {7., 5., 2.}};
  double content_b[3][3] = {{
                                1.,
                                2.,
                                3.,
                            },
                            {4., 5., 6.},
                            {7., 8., 9.}};
  double content_e[3][3] = {{30, 36, 42}, {60, 72, 84}, {41, 55, 69}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_mult_matrix(&a, &b, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&r, &e), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test5_mult_matr) {
  matrix_t a, b, r, e;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &b);
  code += s21_create_matrix(3, 3, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{1., 2., 3.}, {4., 5., 6.}, {7., 8., 9.}};
  double content_b[3][3] = {{1., 2., 3.}, {3., 2., 1.}, {7., 5., 2.}};
  double content_e[3][3] = {{28, 21, 11}, {61, 48, 29}, {94, 75, 47}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_mult_matrix(&a, &b, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&r, &e), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test6_mult_matr) {
  matrix_t a, b, r, e;
  int code = code = s21_create_matrix(2, 5, &a);
  code += s21_create_matrix(5, 2, &b);
  code += s21_create_matrix(2, 2, &e);
  ck_assert_int_eq(code, 0);
  double content_a[2][5] = {{2.15746, 1.61630, 2.02538, 1.24788, 1.55167},
                            {3.91035, 1.25229, 3.80819, 1.16017, 3.14779}};
  double content_b[5][2] = {{1.55365, 3.68359},
                            {3.58831, 3.84431},
                            {1.41244, 1.80059},
                            {2.20100, 3.95030},
                            {1.89133, 2.32189}};
  double content_e[2][2] = {{17.6937548103, 26.3399427289},
                            {24.4548037217, 37.9671476326}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_mult_matrix(&a, &b, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&r, &e), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test7_mult_matr) {
  matrix_t a, b, r, e;
  int code = s21_create_matrix(5, 2, &a);
  code += s21_create_matrix(2, 4, &b);
  code += s21_create_matrix(5, 4, &e);
  ck_assert_int_eq(code, 0);
  double content_a[5][2] = {{1.55365, 3.68359},
                            {3.58831, 3.84431},
                            {1.41244, 1.80059},
                            {2.20100, 3.95030},
                            {1.89133, 2.32189}};
  double content_b[2][4] = {{2.19891, 2.44875, 3.21633, 1.14803},
                            {2.44390, 3.74607, 2.08689, 3.85980}};
  double content_e[5][4] = {
      {12.4186621225, 17.6034864288, 12.6842982396, 16.0015574915},
      {17.2854799511, 23.1879284742, 19.5638411982, 18.9577552673},
      {7.5062903414, 10.2038486313, 8.3005064103, 8.5714407752},
      {14.4939390800, 20.1877990710, 15.3229838970, 17.7741819700},
      {9.8333314213, 13.3293568098, 10.9286704410, 11.1333346019}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_mult_matrix(&a, &b, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&r, &e), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test8_mult_matr) {
  matrix_t a, b, r, e;
  int code = s21_create_matrix(3, 4, &a);
  code += s21_create_matrix(4, 3, &b);
  code += s21_create_matrix(3, 3, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][4] = {{3.78308, 2.33718, 2.59181, 3.94461},
                            {3.40176, 2.38731, 1.51887, 1.09706},
                            {2.68414, 1.05042, 1.42217, 1.54185}};
  double content_b[4][3] = {{3.00266, 3.60228, 2.78362},
                            {2.52415, 1.90470, 2.74344},
                            {1.95798, 3.50581, 2.10471},
                            {1.93363, 1.23257, 2.47293}};
  double content_e[3][3] = {{29.9608243, 32.0277415, 32.1523231},
                            {21.3354824, 23.4782742, 21.9283824},
                            {16.4769253, 18.5560547, 17.1595326}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_mult_matrix(&a, &b, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&r, &e), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test9_mult_matr) {
  matrix_t a, b, r;
  int code = s21_create_matrix(3, 4, &a);
  code += s21_create_matrix(3, 4, &b);
  ck_assert_int_eq(code, 0);

  code = s21_mult_matrix(&a, &b, &r);
  ck_assert_int_eq(code, CALC_ERROR);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(test10_mult_matr) {
  matrix_t a, b, r;
  int code = s21_create_matrix(5, 2, &a);
  code += s21_create_matrix(4, 3, &b);
  ck_assert_int_eq(code, 0);

  code = s21_mult_matrix(&a, &b, &r);
  ck_assert_int_eq(code, CALC_ERROR);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(test11_mult_matr) {
  matrix_t a, b;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &b);
  ck_assert_int_eq(code, 0);
  code = s21_mult_matrix(&a, &b, NULL);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(test12_mult_matr) {
  matrix_t a, b, r;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &b);
  a.rows = -1;
  ck_assert_int_eq(code, 0);
  code = s21_mult_matrix(&a, &b, &r);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(test13_mult_matr) {
  matrix_t a, b, r;
  int code = s21_create_matrix(3, 3, &a);
  b.matrix = NULL;
  ck_assert_int_eq(code, 0);
  code = s21_mult_matrix(&a, &b, &r);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
  s21_remove_matrix(&a);
}
END_TEST

//! test s21_transpose

START_TEST(test1_transpose) {
  matrix_t a, r, e;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{
                                1.,
                                2.,
                                3.,
                            },
                            {3., 2., 1.},
                            {7., 5., 2.}};
  double content_e[3][3] = {{1., 3., 7.}, {2., 2., 5.}, {3., 1., 2.}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_transpose(&a, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test2_transpose) {
  matrix_t a, r, e;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{0.13807, 4.10035, 7.04436},
                            {5.32393, 1.70957, 5.99774},
                            {3.47567, 6.88200, 0.32512}};
  double content_e[3][3] = {{0.13807, 5.32393, 3.47567},
                            {4.10035, 1.70957, 6.882},
                            {7.04436, 5.99774, 0.32512}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_transpose(&a, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST
START_TEST(test3_transpose) {
  matrix_t a, r, e;
  int code = s21_create_matrix(4, 4, &a);
  code += s21_create_matrix(4, 4, &e);
  ck_assert_int_eq(code, 0);
  double content_a[4][4] = {{1.80377, 3.93870, 3.13429, 2.28155},
                            {1.39307, 1.05586, 2.21357, 2.20440},
                            {2.74323, 2.41325, 3.86805, 2.73013},
                            {2.74323, 2.41325, 3.86805, 2.73013}};
  double content_e[4][4] = {{1.80377, 1.39307, 2.74323, 2.74323},
                            {3.9387, 1.05586, 2.41325, 2.41325},
                            {3.13429, 2.21357, 3.86805, 3.86805},
                            {2.28155, 2.2044, 2.73013, 2.73013}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_transpose(&a, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test4_transpose) {
  matrix_t a, r, e;
  int code = s21_create_matrix(3, 4, &a);
  code += s21_create_matrix(4, 3, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][4] = {{1.80377, 3.93870, 3.13429, 2.28155},
                            {1.39307, 1.05586, 2.21357, 2.20440},
                            {2.74323, 2.41325, 3.86805, 2.73013}};
  double content_e[4][3] = {{1.80377, 1.39307, 2.74323},
                            {3.9387, 1.05586, 2.41325},
                            {3.13429, 2.21357, 3.86805},
                            {2.28155, 2.2044, 2.73013}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_transpose(&a, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test5_transpose) {
  matrix_t a, r;
  int code = s21_create_matrix(3, 4, &a);
  ck_assert_int_eq(code, 0);
  a.columns = -1;
  code = s21_transpose(&a, &r);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test6_transpose) {
  ck_assert_int_eq(s21_transpose(NULL, NULL), INCORRECT_MATRIX);
}
END_TEST

//! s21_calc_complements

START_TEST(test1_complement) {
  matrix_t a, r, e;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{1., 2., 3.}, {3., 2., 1.}, {7., 5., 2.}};
  double content_e[3][3] = {{-1., 1., 1.}, {11., -19., 9.}, {-4., 8., -4.}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_calc_complements(&a, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test2_complement) {
  matrix_t a, r, e;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{0.13807, 4.10035, 7.04436},
                            {5.32393, 1.70957, 5.99774},
                            {3.47567, 6.88200, 0.32512}};
  double content_e[3][3] = {{-40.7206312816, 19.1152488642, 30.6973850981},
                            {47.1461797280, -24.4389814028, 13.3012657445},
                            {12.5500066838, 36.6755715730, -21.5939360456}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_calc_complements(&a, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test3_complement) {
  matrix_t a, r, e;
  int code = s21_create_matrix(4, 4, &a);
  code += s21_create_matrix(4, 4, &e);
  ck_assert_int_eq(code, 0);
  double content_a[4][4] = {{1.80377, 3.93870, 3.13429, 2.28155},
                            {1.39307, 1.05586, 2.21357, 2.20440},
                            {2.74323, 2.41325, 3.86805, 2.73013},
                            {2.74323, 2.41325, 3.86805, 2.73013}};
  double content_e[4][4] = {
      {0., 0., 0., 0.},
      {0., 0., 0., 0.},
      {-5.0123523428, -0.9933255993, 5.5038169258, -1.8833757880},
      {5.0123523428, 0.9933255993, -5.5038169258, 1.8833757880}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_calc_complements(&a, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test4_complement) {
  matrix_t a, r, e;
  int code = s21_create_matrix(4, 4, &a);
  code += s21_create_matrix(4, 4, &e);
  ck_assert_int_eq(code, 0);
  double content_a[4][4] = {{1.80377, 3.93870, 3.13429, 2.28155},
                            {1.39307, 1.05586, 2.21357, 2.20440},
                            {2.74323, 2.41325, 3.86805, 2.73013},
                            {2.29065, 3.09765, 1.84139, 3.86339}};
  double content_e[4][4] = {
      {-8.0642664633, 4.1987149757, 3.1661056480, -0.0941589509},
      {-19.1443430067, -4.4198224214, 8.7731760020, 10.7131854857},
      {15.1040957594, -1.3457695400, -1.9412358558, -6.9511236616},
      {5.0123523428, 0.9933255993, -5.5038169258, 1.8833757880}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_calc_complements(&a, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test5_complement) {
  matrix_t a, r;
  int code = s21_create_matrix(3, 4, &a);
  ck_assert_int_eq(code, 0);
  double content_a[3][4] = {{1.80377, 3.93870, 3.13429, 2.28155},
                            {1.39307, 1.05586, 2.21357, 2.20440},
                            {2.74323, 2.41325, 3.86805, 2.73013}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];

  code = s21_calc_complements(&a, &r);
  ck_assert_int_eq(code, CALC_ERROR);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test6_complement) {
  matrix_t a, r;
  int code = s21_create_matrix(3, 4, &a);
  ck_assert_int_eq(code, 0);
  a.columns = -1;
  code = s21_calc_complements(&a, &r);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test7_complement) {
  ck_assert_int_eq(s21_calc_complements(NULL, NULL), INCORRECT_MATRIX);
}
END_TEST

//! test s21_determinant

START_TEST(test1_det) {
  matrix_t a;
  double d, e = 4;
  int code = s21_create_matrix(3, 3, &a);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{1., 2., 3.}, {3., 2., 1.}, {7., 5., 2.}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];

  code = s21_determinant(&a, &d);
  ck_assert_int_eq(code, 0);
  ck_assert_double_eq_tol(d, e, 1e-7);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test2_det) {
  matrix_t a;
  double d, e = 289.000344808923674;
  int code = s21_create_matrix(3, 3, &a);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{0.13807, 4.10035, 7.04436},
                            {5.32393, 1.70957, 5.99774},
                            {3.47567, 6.88200, 0.32512}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];

  code = s21_determinant(&a, &d);
  ck_assert_int_eq(code, 0);
  ck_assert_double_eq_tol(d, e, 1e-7);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test3_det) {
  matrix_t a;
  double d, e = 0;
  int code = s21_create_matrix(4, 4, &a);
  ck_assert_int_eq(code, 0);
  double content_a[4][4] = {{1.80377, 3.93870, 3.13429, 2.28155},
                            {1.39307, 1.05586, 2.21357, 2.20440},
                            {2.74323, 2.41325, 3.86805, 2.73013},
                            {2.74323, 2.41325, 3.86805, 2.73013}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];

  code = s21_determinant(&a, &d);
  ck_assert_int_eq(code, 0);
  ck_assert_double_eq_tol(d, e, 1e-7);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test4_det) {
  matrix_t a;
  double d, e = 11.70006167326680176888;
  int code = s21_create_matrix(4, 4, &a);
  ck_assert_int_eq(code, 0);
  double content_a[4][4] = {{1.80377, 3.93870, 3.13429, 2.28155},
                            {1.39307, 1.05586, 2.21357, 2.20440},
                            {2.74323, 2.41325, 3.86805, 2.73013},
                            {2.29065, 3.09765, 1.84139, 3.86339}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];

  code = s21_determinant(&a, &d);
  ck_assert_int_eq(code, 0);
  ck_assert_double_eq_tol(d, e, 1e-7);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test5_det) {
  matrix_t a;
  double d;
  int code = s21_create_matrix(3, 4, &a);
  ck_assert_int_eq(code, 0);
  double content_a[3][4] = {{1.80377, 3.93870, 3.13429, 2.28155},
                            {1.39307, 1.05586, 2.21357, 2.20440},
                            {2.74323, 2.41325, 3.86805, 2.73013}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];

  code = s21_determinant(&a, &d);
  ck_assert_int_eq(code, CALC_ERROR);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test6_det) {
  matrix_t a;
  double d;
  int code = s21_create_matrix(3, 4, &a);
  ck_assert_int_eq(code, 0);
  a.columns = -1;
  code = s21_determinant(&a, &d);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test7_det) {
  ck_assert_int_eq(s21_determinant(NULL, NULL), INCORRECT_MATRIX);
}
END_TEST

START_TEST(test8_det) {
  matrix_t a;
  double d, e = 24.11167307304728580683610306381957237;
  int code = s21_create_matrix(7, 7, &a);
  ck_assert_int_eq(code, 0);
  double content_a[7][7] = {
      {3.54155, 2.53027, 2.52268, 3.32609, 1.74077, 1.84826, 2.31548},
      {1.79850, 1.03137, 3.21930, 2.23851, 3.69014, 1.86757, 2.58197},
      {3.12373, 2.50464, 2.81140, 3.95159, 3.93592, 2.55369, 2.85939},
      {2.53200, 2.17887, 3.89360, 2.57050, 1.35048, 2.86216, 2.85716},
      {2.45656, 2.44057, 3.60225, 2.02151, 2.66313, 3.54608, 1.99800},
      {2.73763, 3.62892, 3.16649, 1.46655, 1.63051, 3.30205, 1.16198},
      {2.99739, 1.10405, 3.75781, 1.69789, 2.66463, 2.54331, 1.13451}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];

  code = s21_determinant(&a, &d);
  ck_assert_int_eq(code, 0);
  ck_assert_double_eq_tol(d, e, 1e-7);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test9_det) {
  matrix_t a;
  double d, e = 0;
  int code = s21_create_matrix(3, 3, &a);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{1., 2., 3.}, {1., 2., 3.}, {7., 8., 9.}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];

  code = s21_determinant(&a, &d);
  ck_assert_int_eq(code, 0);
  ck_assert_double_eq_tol(d, e, 1e-7);
  s21_remove_matrix(&a);
}

//! test s21_inverse_matrix

START_TEST(test1_inverse) {
  matrix_t a, r, e;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{1., 2., 3.}, {3., 2., 1.}, {7., 5., 2.}};
  double content_e[3][3] = {
      {-0.25, 2.75, -1.}, {0.25, -4.75, 2.}, {0.25, 2.25, -1.}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_inverse_matrix(&a, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test2_inverse) {
  matrix_t a, r, e;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{0.13807, 4.10035, 7.04436},
                            {5.32393, 1.70957, 5.99774},
                            {3.47567, 6.88200, 0.32512}};
  double content_e[3][3] = {{-0.1409016702, 0.1631353754, 0.0434255769},
                            {0.0661426507, -0.0845638486, 0.1269049405},
                            {0.1062191989, 0.0460250861, -0.0747194127}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_inverse_matrix(&a, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test3_inverse) {
  matrix_t a, r;
  int code = s21_create_matrix(4, 4, &a);
  ck_assert_int_eq(code, 0);
  double content_a[4][4] = {{1.80377, 3.93870, 3.13429, 2.28155},
                            {1.39307, 1.05586, 2.21357, 2.20440},
                            {2.74323, 2.41325, 3.86805, 2.73013},
                            {2.74323, 2.41325, 3.86805, 2.73013}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];

  code = s21_inverse_matrix(&a, &r);
  ck_assert_int_eq(code, CALC_ERROR);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test4_inverse) {
  matrix_t a, r, e;
  int code = s21_create_matrix(4, 4, &a);
  code += s21_create_matrix(4, 4, &e);
  ck_assert_int_eq(code, 0);
  double content_a[4][4] = {{1.80377, 3.93870, 3.13429, 2.28155},
                            {1.39307, 1.05586, 2.21357, 2.20440},
                            {2.74323, 2.41325, 3.86805, 2.73013},
                            {2.29065, 3.09765, 1.84139, 3.86339}};
  double content_e[4][4] = {
      {-0.6892499107, -1.6362600080, 1.2909415507, 0.4284039249},
      {0.3588626362, -0.3777606089, -0.1150224313, 0.0848991764},
      {0.2706058939, 0.7498401502, -0.1659167199, -0.4704092234},
      {-0.0080477312, 0.9156520525, -0.5941100018, 0.1609714411}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_inverse_matrix(&a, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test5_inverse) {
  matrix_t a, r;
  int code = s21_create_matrix(3, 4, &a);
  ck_assert_int_eq(code, 0);
  double content_a[3][4] = {{1.80377, 3.93870, 3.13429, 2.28155},
                            {1.39307, 1.05586, 2.21357, 2.20440},
                            {2.74323, 2.41325, 3.86805, 2.73013}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];

  code = s21_inverse_matrix(&a, &r);
  ck_assert_int_eq(code, CALC_ERROR);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test6_inverse) {
  matrix_t a, r;
  int code = s21_create_matrix(3, 4, &a);
  ck_assert_int_eq(code, 0);
  a.columns = -1;
  code = s21_inverse_matrix(&a, &r);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test7_inverse) {
  ck_assert_int_eq(s21_inverse_matrix(NULL, NULL), INCORRECT_MATRIX);
}
END_TEST

START_TEST(test8_inverse) {
  matrix_t a, r, e;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{1., 2., 3.}, {1., 2., 4.}, {7., 5., 2.}};
  double content_e[3][3] = {{-1.7777777778, 1.2222222222, 0.2222222222},
                            {2.8888888889, -2.1111111111, -0.1111111111},
                            {-1., 1., 0.}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_inverse_matrix(&a, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

Suite *tests(void) {
  Suite *s = suite_create("\033[43m-=matrix=-\033[0m");
  TCase *tc = tcase_create("matrix_rc");

  //! общие тесты

  tcase_add_test(tc, compliment_test_1);  // compliments
  tcase_add_test(tc, compliment_test_2);
  tcase_add_test(tc, compliment_test_not_square);
  tcase_add_test(tc, compliment_test_1x1);
  tcase_add_test(tc, null_compliments);
  tcase_add_test(tc, create_test);  // create
  tcase_add_test(tc, create_test_incorrect);
  tcase_add_test(tc, determinant_test_1);  // determinant
  tcase_add_test(tc, determinant_test_2);
  tcase_add_test(tc, determinant_test_3x3_1);
  tcase_add_test(tc, determinant_test_3x3_2);
  tcase_add_test(tc, determinant_test_3x3_3);
  tcase_add_test(tc, determinant_test_3x3_4);
  tcase_add_test(tc, determinant_test_4x4);
  tcase_add_test(tc, determinant_test_4x4_2);
  tcase_add_test(tc, determinant_test_5x5);
  tcase_add_test(tc, determinant_not_square);
  tcase_add_test(tc, null_determinate);
  tcase_add_test(tc, eq_test_1);  // eq
  tcase_add_test(tc, eq_test_2);
  tcase_add_test(tc, eq_test_diff_size);
  tcase_add_test(tc, test_normal);  // inverse
  tcase_add_test(tc, test_not_sqare);
  tcase_add_test(tc, null_inverse);
  tcase_add_test(tc, zero_det);
  tcase_add_test(tc, incorrect_matrix_1);  // mult_matrix
  tcase_add_test(tc, incorrect_matrix_2);
  tcase_add_test(tc, mult_matrix_test_1);
  tcase_add_test(tc, mult_matrix_test_2);
  tcase_add_test(tc, mult_matrix_test_3);
  tcase_add_test(tc, null_mult_mat);
  tcase_add_test(tc, mult_number_test_1);  // mult_number
  tcase_add_test(tc, mult_number_test_2);
  tcase_add_test(tc, mult_number_test_3);
  tcase_add_test(tc, null_mult_num);
  tcase_add_test(tc, remove_test);  // remove
  tcase_add_test(tc, sub_test_1);   // sub
  tcase_add_test(tc, sub_test_2);
  tcase_add_test(tc, sub_test_incorrect_matrix);
  tcase_add_test(tc, null_sub);
  tcase_add_test(tc, sum_test_1);  // sum
  tcase_add_test(tc, sum_test_2);
  tcase_add_test(tc, sum_test_incorrect_matrix);
  tcase_add_test(tc, null_sum);
  tcase_add_test(tc, transpose_test_1);  // transpose
  tcase_add_test(tc, transpose_test_2);
  tcase_add_test(tc, transpose_incorrect);
  tcase_add_test(tc, null_transpose);

  //! s21_create_matrix

  tcase_add_test(tc, test1_create);
  tcase_add_test(tc, test2_create);
  tcase_add_test(tc, test3_create);
  tcase_add_test(tc, test4_create);
  tcase_add_test(tc, test5_create);
  tcase_add_test(tc, test6_create);
  tcase_add_test(tc, test7_create);
  tcase_add_test(tc, test8_create);
  tcase_add_test(tc, test9_create);

  //! test s21_eq_matrix

  tcase_add_test(tc, test1_eq);
  tcase_add_test(tc, test2_eq);
  tcase_add_test(tc, test3_eq);
  tcase_add_test(tc, test4_eq);
  tcase_add_test(tc, test5_eq);
  tcase_add_test(tc, test6_eq);
  tcase_add_test(tc, test7_eq);
  tcase_add_test(tc, test8_eq);
  tcase_add_test(tc, test9_eq);
  tcase_add_test(tc, test10_eq);
  tcase_add_test(tc, test11_eq);
  tcase_add_test(tc, test12_eq);
  tcase_add_test(tc, test13_eq);

  //! test s21_sum_matrix

  tcase_add_test(tc, test1_sum);
  tcase_add_test(tc, test2_sum);
  tcase_add_test(tc, test3_sum);
  tcase_add_test(tc, test4_sum);
  tcase_add_test(tc, test5_sum);
  tcase_add_test(tc, test6_sum);
  tcase_add_test(tc, test7_sum);
  tcase_add_test(tc, test8_sum);
  tcase_add_test(tc, test9_sum);
  tcase_add_test(tc, test10_sum);

  //! test s21_sub_matrix

  tcase_add_test(tc, test1_sub);
  tcase_add_test(tc, test2_sub);
  tcase_add_test(tc, test3_sub);
  tcase_add_test(tc, test4_sub);
  tcase_add_test(tc, test5_sub);
  tcase_add_test(tc, test6_sub);
  tcase_add_test(tc, test7_sub);
  tcase_add_test(tc, test8_sub);
  tcase_add_test(tc, test9_sub);
  tcase_add_test(tc, test10_sub);

  //! test s21_mult_number

  tcase_add_test(tc, test1_mul_num);
  tcase_add_test(tc, test2_mul_num);
  tcase_add_test(tc, test3_mul_num);
  tcase_add_test(tc, test4_mul_num);
  tcase_add_test(tc, test5_mul_num);
  tcase_add_test(tc, test6_mul_num);
  tcase_add_test(tc, test7_mul_num);

  //! test s21_mult_matrix

  tcase_add_test(tc, test1_mult_matr);
  tcase_add_test(tc, test2_mult_matr);
  tcase_add_test(tc, test3_mult_matr);
  tcase_add_test(tc, test4_mult_matr);
  tcase_add_test(tc, test5_mult_matr);
  tcase_add_test(tc, test6_mult_matr);
  tcase_add_test(tc, test7_mult_matr);
  tcase_add_test(tc, test8_mult_matr);
  tcase_add_test(tc, test9_mult_matr);
  tcase_add_test(tc, test10_mult_matr);
  tcase_add_test(tc, test11_mult_matr);
  tcase_add_test(tc, test12_mult_matr);
  tcase_add_test(tc, test13_mult_matr);

  //! test s21_transpose

  tcase_add_test(tc, test1_transpose);
  tcase_add_test(tc, test2_transpose);
  tcase_add_test(tc, test3_transpose);
  tcase_add_test(tc, test4_transpose);
  tcase_add_test(tc, test5_transpose);
  tcase_add_test(tc, test6_transpose);

  //! s21_calc_complements

  tcase_add_test(tc, test1_complement);
  tcase_add_test(tc, test2_complement);
  tcase_add_test(tc, test3_complement);
  tcase_add_test(tc, test4_complement);
  tcase_add_test(tc, test5_complement);
  tcase_add_test(tc, test6_complement);
  tcase_add_test(tc, test7_complement);

  //! test s21_determinant

  tcase_add_test(tc, test1_det);
  tcase_add_test(tc, test2_det);
  tcase_add_test(tc, test3_det);
  tcase_add_test(tc, test4_det);
  tcase_add_test(tc, test5_det);
  tcase_add_test(tc, test6_det);
  tcase_add_test(tc, test7_det);
  tcase_add_test(tc, test8_det);
  tcase_add_test(tc, test9_det);

  //! test s21_inverse_matrix

  tcase_add_test(tc, test1_inverse);
  tcase_add_test(tc, test2_inverse);
  tcase_add_test(tc, test3_inverse);
  tcase_add_test(tc, test4_inverse);
  tcase_add_test(tc, test5_inverse);
  tcase_add_test(tc, test6_inverse);
  tcase_add_test(tc, test7_inverse);
  tcase_add_test(tc, test8_inverse);

  suite_add_tcase(s, tc);
  return s;
}

int main(void) {
  int failed = 0;
  Suite *matrix_t_test[] = {tests(), NULL};

  for (int i = 0; matrix_t_test[i] != NULL; i++) {  // (&& failed == 0)
    SRunner *sr = srunner_create(matrix_t_test[i]);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  printf("========= FAILED: %d =========\n", failed);

  return failed == 0 ? 0 : 1;
}
