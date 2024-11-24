#include <gtest/gtest.h>

#include "s21_matrix_oop.hpp"

TEST(S21MatrixTest, DefaultConstructor) {
  S21Matrix m;
  EXPECT_EQ(m.GetRows(), 0);
  EXPECT_EQ(m.GetCols(), 0);
}

TEST(S21MatrixTest, ParamConstructor) {
  S21Matrix m(2, 3);
  EXPECT_EQ(m.GetRows(), 2);
  EXPECT_EQ(m.GetCols(), 3);
}

TEST(S21MatrixTest, CopyConstructor) {
  S21Matrix m1(2, 3);
  m1(0, 0) = 1.0;
  m1(1, 2) = 3.0;

  S21Matrix m2(m1);
  EXPECT_EQ(m2.GetRows(), 2);
  EXPECT_EQ(m2.GetCols(), 3);
  EXPECT_DOUBLE_EQ(m2(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(m2(1, 2), 3.0);
}

TEST(S21MatrixTest, MoveConstructor) {
  S21Matrix m1(2, 3);
  m1(0, 0) = 1.0;
  m1(1, 2) = 3.0;

  S21Matrix m2(std::move(m1));
  EXPECT_EQ(m2.GetRows(), 2);
  EXPECT_EQ(m2.GetCols(), 3);
  EXPECT_DOUBLE_EQ(m2(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(m2(1, 2), 3.0);
}

TEST(S21MatrixTest, AssignmentOperator) {
  S21Matrix m1(2, 3);
  m1(0, 0) = 1.0;
  m1(1, 2) = 3.0;

  S21Matrix m2 = m1;
  EXPECT_EQ(m2.GetRows(), 2);
  EXPECT_EQ(m2.GetCols(), 3);
  EXPECT_DOUBLE_EQ(m2(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(m2(1, 2), 3.0);
}

TEST(S21MatrixTest, SumMatrix) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);

  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  m1(1, 0) = 3.0;
  m1(1, 1) = 4.0;

  m2(0, 0) = 5.0;
  m2(0, 1) = 6.0;
  m2(1, 0) = 7.0;
  m2(1, 1) = 8.0;

  S21Matrix result = m1 + m2;

  EXPECT_DOUBLE_EQ(result(0, 0), 6.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 8.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 10.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 12.0);
}

TEST(S21MatrixTest, SubMatrix) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);

  m1(0, 0) = 5.0;
  m1(0, 1) = 6.0;
  m1(1, 0) = 7.0;
  m1(1, 1) = 8.0;

  m2(0, 0) = 1.0;
  m2(0, 1) = 2.0;
  m2(1, 0) = 3.0;
  m2(1, 1) = 4.0;

  S21Matrix result = m1 - m2;

  EXPECT_DOUBLE_EQ(result(0, 0), 4.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 4.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 4.0);
}

TEST(S21MatrixTest, MulNumber) {
  S21Matrix m1(2, 2);

  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  m1(1, 0) = 3.0;
  m1(1, 1) = 4.0;

  m1.MulNumber(2.0);

  EXPECT_DOUBLE_EQ(m1(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(m1(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(m1(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(m1(1, 1), 8.0);
}

TEST(S21MatrixTest, MulMatrix) {
  S21Matrix m1(2, 3);
  S21Matrix m2(3, 2);

  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  m1(0, 2) = 3.0;
  m1(1, 0) = 4.0;
  m1(1, 1) = 5.0;
  m1(1, 2) = 6.0;

  m2(0, 0) = 7.0;
  m2(0, 1) = 8.0;
  m2(1, 0) = 9.0;
  m2(1, 1) = 10.0;
  m2(2, 0) = 11.0;
  m2(2, 1) = 12.0;

  S21Matrix result = m1 * m2;

  EXPECT_EQ(result.GetRows(), 2);
  EXPECT_EQ(result.GetCols(), 2);
  EXPECT_DOUBLE_EQ(result(0, 0), 58.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 64.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 139.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 154.0);
}

TEST(S21MatrixTest, Transpose) {
  S21Matrix m1(2, 3);

  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  m1(0, 2) = 3.0;
  m1(1, 0) = 4.0;
  m1(1, 1) = 5.0;
  m1(1, 2) = 6.0;

  S21Matrix result = m1.Transpose();

  EXPECT_EQ(result.GetRows(), 3);
  EXPECT_EQ(result.GetCols(), 2);
  EXPECT_DOUBLE_EQ(result(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 2.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 5.0);
  EXPECT_DOUBLE_EQ(result(2, 0), 3.0);
  EXPECT_DOUBLE_EQ(result(2, 1), 6.0);
}

TEST(S21MatrixTest, Determinant) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  m1(1, 0) = 3.0;
  m1(1, 1) = 4.0;

  double det = m1.Determinant();
  EXPECT_DOUBLE_EQ(det, -2.0);
}

TEST(S21MatrixTest, InvalidDimensions) {
  EXPECT_THROW(S21Matrix m(-1, 1), std::invalid_argument);
  EXPECT_THROW(S21Matrix m(1, -1), std::invalid_argument);
  S21Matrix m1(2, 2);
  S21Matrix m2(3, 2);
  EXPECT_THROW(m1 + m2, std::runtime_error);
  EXPECT_THROW(m1 - m2, std::runtime_error);
  EXPECT_THROW(m1.MulMatrix(m2), std::runtime_error);
}
