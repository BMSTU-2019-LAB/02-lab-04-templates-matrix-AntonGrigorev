// Copyright 2018 Your Name <your_email>
#include "matrix.hpp"
#include <iostream>
#include <string>
using namespace std;

int main() {
  Matrix<string> m(5, 5);

  for (size_t i = 0; i < 5; ++i) {
    for (size_t j = 0; j < 5; ++j) {
      m[i][j] = 1 + (i * j) % 7;
    }
  }
  Matrix<double> I(5, 5);
  for (size_t i = 0; i < 5; ++i) {
    I[i][i] = 1.;
  }


 for (size_t i = 0; i <5; ++i) {
    for (size_t j = 0; j < 5; ++j) {
      cout << m[i][j] << " ";
    }
    cout << endl;
  }
 cout << endl;
  return 0;
}