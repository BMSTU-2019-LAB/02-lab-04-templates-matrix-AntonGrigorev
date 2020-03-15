// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_MATRIX_HPP_
#define INCLUDE_MATRIX_HPP_
template <class T>
class Matrix {
  int n;
  int m;
  T** M;

 public:
  Matrix() {
    n = m = 0;
    M = nullptr;
  }

  Matrix(int size n, int size m) {
    this->n = n;
    this->m = m;
    M = (T**)new T[n];
    for (int i = 0; i < n; i++) {
      M[i] = (T*)new T[m];
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        M[i][j] = 0;
      }
    }
  }

  Matrix(const& Matrix C) {
    n = C.n;
    m = C.m;
    M = (T**)new T[n];
    for (int i = 0; i < n; i++) {
      M[i] = (T*)new T[m];
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        M[i][j] = C.M[i][j];
      }
    }
  }

 
  Matrix& operator =(const& Matrix R) {
    n = R.n;
    m = R.m;
    M = (T**)new T[n];
    for (int i = 0; i < n; i++) {
      M[i] = (T*)new T[m];
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        M[i][j] = R.M[i][j];
      }
    }
    return R;
  }

  Matrix& operator+(Matrix& M) {
    if (m != M.m || n != M.n) 
        return Matrix();
    Matrix M1(m, n);
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        M1.p[i][j] = M.p[i][j] + p[i][j];
      };
    };
    return M1;
  }

  Matrix operator-(Matrix& M) {
    if (m != M.m || n != M.n) 
        return Matrix();
    Matrix M1(m, n);
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        M1.p[i][j] = M.p[i][j] - p[i][j];
      }
    }
    return M1;
  }

  Matrix operator*(Matrix& M) { 
      if (m != M.n) {
      return Matrix();
    }
    Matrix Mult;
    Mult.n = n;
    Mult.m = M.m;
    for (int i = 0; i < Mult.n; i++) {
      for (int j = 0; j < n; j++) {
        for (int k =0; k < )
      }
    }
  }

  ~Matrix() {
    for (int i = 0; i < n; i++) {
      delete M[i];
    }
    delete[] M;
  }
};

#endif // INCLUDE_MATRIX_HPP_
