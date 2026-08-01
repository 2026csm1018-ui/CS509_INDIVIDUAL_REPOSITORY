#include <iostream>
#include <chrono>
#include "matrix.h"
using namespace std;
using namespace std::chrono;


long long simple_multiplication(matrix m1, matrix m2,matrix &m3)
{
  auto start = high_resolution_clock::now();
  for (int i = 0; i < m1.rows; i++)
    for (int k = 0; k < m2.cols; k++)
      for (int j = 0; j < m1.cols; j++)
      {
        m3.mat[i][k] += m1.mat[i][j] * m2.mat[j][k];
      }
   auto end = high_resolution_clock::now();
  return duration_cast<microseconds>(end - start).count();
}







