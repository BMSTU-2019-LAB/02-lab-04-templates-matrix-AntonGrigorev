// Copyright 2018 Your Name <your_email>
#include <cmath>
#include <type_traits>
#include <iostream>
#ifndef INCLUDE_MATRIX_HPP_
#define INCLUDE_MATRIX_HPP_

template <typename T>
class Matrix {
  static_assert(std:: is_arithmetic<T>::value, "Non-arithmetic type");
  int n;
  int m;
  T** M;

 public:
  Matrix() {
    n = 0;
    m = 0;
    M = nullptr;
  }

  Matrix(int a, int b) {
    n = a;
    m = b;
    M = new T*[n];
    for (int i = 0; i < n; i++) {
      M[i] = new T[m];
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        M[i][j] = 0;
      }
    }
  }

  Matrix(const Matrix& C) {
    n = C.n;
    m = C.m;
    M = new T*[n];
    for (int i = 0; i < n; i++) {
      M[i] = new T[m];
    }
    for (int i = 0; i < n; i++) {
       for (int j = 0; j < m; j++) {
         M[i][j] = C.M[i][j];
       }
    }
  }

  Matrix operator=(const Matrix& R) {
    n = R.n;
    m = R.m;
    for (int i = 0; i < R.n; i++) {
      for (int j = 0; j < R.m; j++) {
        M[i][j] = R.M[i][j];
      }
    }
    return *this;
  }

  Matrix operator+(const Matrix& M1) const {
    if (n != M1.n || m != M1.m) {
      Matrix<T> Zero;
      return Zero;
    }
    Matrix<T> add(n, m);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        add.M[i][j] = M[i][j] + M1.M[i][j];
      }
    }
    return add;
  }

  Matrix operator-(Matrix& M1) const {
    if (n != M1.n || m != M1.m) {
      Matrix<T> Zero;
      return Zero;
    }
    Matrix<T> sub(n, m);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        sub.M[i][j] = M[i][j] - M1.M[i][j];
      }
    }
    return sub;
  }

  Matrix operator*(Matrix& M1) const {
    if (m != M1.n) {
      Matrix<T> Zero;
      return Zero;
    }
    Matrix<T> Mult(n, M1.m);
    for (int i = 0; i < Mult.n; i++) {
      for (int j = 0; j < Mult.m; j++) {
        for (int k = 0; k < m; k++) {
          Mult.M[i][j] += M[i][k] * M1.M[k][j];
        }
      }
    }
    return Mult;
  }

  Matrix Inverse() const {
    Matrix<T> A(n, 2 * n);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        A.M[i][j] = M[i][j];
      }
    }
    for (int i = 0; i < n; i++) {
      A.M[i][n + i] = 1;
    }

    for (int i = 0; i < n; i++) {
      double maxEl = abs(A.M[i][i]);
      int maxRow = i;
      for (int k = i + 1; k < n; k++) {
        if (abs(A.M[k][i]) > maxEl) {
          maxEl = A.M[k][i];
          maxRow = k;
        }
      }

      for (int k = i; k < 2 * n; k++) {
        double tmp = A.M[maxRow][k];
        A.M[maxRow][k] = A.M[i][k];
        A.M[i][k] = tmp;
      }

      for (int k = i + 1; k < n; k++) {
        double c = -A.M[k][i] / A.M[i][i];
        for (int j = i; j < 2 * n; j++) {
          if (i == j) {
            A.M[k][j] = 0;
          } else {
            A.M[k][j] += c * A.M[i][j];
          }
        }
      }
    }

    for (int i = n - 1; i >= 0; i--) {
      for (int k = n; k < 2 * n; k++) {
        A.M[i][k] /= A.M[i][i];
      }
      for (int rowMod = i - 1; rowMod >= 0; rowMod--) {
        for (int columMod = n; columMod < 2 * n; columMod++) {
          A.M[rowMod][columMod] -= A.M[i][columMod] * A.M[rowMod][i];
        }
      }
    }

    Matrix<T> Inv(n, n);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        Inv.M[i][j] = A.M[i][j + n];
      }
    }
    return Inv;
  }

   T* operator[](int index) const { return M[index]; }

  int get_rows() const { return n; }

  int get_columns() const { return m; }

  bool operator==(const Matrix<T>& op2) const {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (M[i][j] == op2.M[i][j]) {
          return true;
        } else {
          return false;
        }
      }
    }
  }

  bool operator!=(const Matrix<T>& op2) const {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (M[i][j] != op2.M[i][j]) {
          return true;
        } else {
          return false;
        }
      }
    }
  }

  ~Matrix() {
    for (int i = 0; i < n; i++) delete[] M[i];
    delete[] M;
  }
};

#endif  // INCLUDE_MATRIX_HPP_
