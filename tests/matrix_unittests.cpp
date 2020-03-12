// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>

#include <matrix.hpp>

TEST(Matrix, Init) {
    Matrix<int> m(2, 2);
    m[0][0] = 1;
    m[0][1] = 2;
    m[1][0] = 3;
    m[1][1] = 4;
    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[0][1], 2);
    EXPECT_EQ(m[1][0], 3);
    EXPECT_EQ(m[1][1], 4);
}

TEST(Matrix, CopyAssign) {
    Matrix<int> m(2, 2);
    Matrix<int> copy(m);
    EXPECT_EQ(m, copy);

    m[0][0] = 1;
    m[0][1] = 2;
    m[1][0] = 3;
    m[1][1] = 4;

    EXPECT_NE(m, copy);

    copy = m;
    EXPECT_EQ(m, copy);
}

TEST(Matrix, Add) {
    Matrix<int> m(2, 3);
    m[0][0] = 1;
    m[0][1] = 2;
    m[1][0] = 3;
    m[1][1] = 4;

    Matrix<int> c = m;

    Matrix<int> s = m + c;
    Matrix<int> s2 = c + c;
    EXPECT_EQ(s2, s);

    ASSERT_EQ(s.get_rows(), 2);
    ASSERT_EQ(s.get_columns(), 3);
    EXPECT_EQ(s[0][0], 2);
    EXPECT_EQ(s[0][1], 4);
    EXPECT_EQ(s[1][0], 6);
    EXPECT_EQ(s[1][1], 8);
    EXPECT_EQ(s[0][2], 0);
    EXPECT_EQ(s[1][2], 0);
}

TEST(Matrix, AddEmpty) {
    Matrix<float> m(2, 2);

    Matrix<float> c(3, 3);

    Matrix<float> s = m + c;

    EXPECT_EQ(s.get_rows(), 0);
    EXPECT_EQ(s.get_columns(), 0);
}

TEST(Matrix, Sub) {
    Matrix<int> m(2, 2);
    m[0][0] = 1;
    m[0][1] = 2;
    m[1][0] = 3;
    m[1][1] = 4;

    auto c = m;
    auto s = m - c;

    ASSERT_EQ(s.get_rows(), 2);
    ASSERT_EQ(s.get_columns(), 2);
    EXPECT_EQ(s[0][0], 0);
    EXPECT_EQ(s[0][1], 0);
    EXPECT_EQ(s[1][0], 0);
    EXPECT_EQ(s[1][1], 0);
}

TEST(Matrix, SubEmpty) {
    Matrix<double> m(2, 2);

    Matrix<double> c(3, 3);

    auto s = m - c;

    EXPECT_EQ(s.get_rows(), 0);
    EXPECT_EQ(s.get_columns(), 0);
}

TEST(Matrix, Mult) {
    Matrix<char> m(3, 2);
    /*
    2 0
    0 2
    1 1
    */
    // first colunm
    m[0][0] = 2;
    m[1][0] = 0;
    m[2][0] = 1;

    // second colunm
    m[0][1] = 0;
    m[1][1] = 2;
    m[2][1] = 1;

    Matrix<char> c(2, 2);
    /*
    1 0
    1 1
    */
    c[0][0] = 1;
    c[0][1] = 0;
    c[1][0] = 1;
    c[1][1] = 1;
    auto s = m * c;

    ASSERT_EQ(s.get_rows(), 3);
    ASSERT_EQ(s.get_columns(), 2);
    /*
    2 0
    2 2
    2 1
    */
    EXPECT_EQ(s[0][0], 2);
    EXPECT_EQ(s[1][0], 2);
    EXPECT_EQ(s[2][0], 2);
    EXPECT_EQ(s[0][1], 0);
    EXPECT_EQ(s[1][1], 2);
    EXPECT_EQ(s[2][1], 1);

    auto e = c * m;
    ASSERT_EQ(0, e.get_rows());
    ASSERT_EQ(0, e.get_columns());
}


TEST(Matrix, Inverse) {
  Matrix<double> m(5, 5);

  for (size_t i = 0; i < m.Rows(); ++i) {
    for (size_t j = 0; j < m.Rows(); ++j) {
      m[i][j] = 1 + (i*j)%7;
    }   
  }

  Matrix<double> I(5, 5);
  for (size_t i = 0; i < m.Rows(); ++i) {
    I[i][i] = 1.;
  }

  auto i = m.Inverse();
  EXPECT_EQ(I, i*m);
  EXPECT_EQ(I, m*i);
  EXPECT_EQ(m*i, i*m);
}
