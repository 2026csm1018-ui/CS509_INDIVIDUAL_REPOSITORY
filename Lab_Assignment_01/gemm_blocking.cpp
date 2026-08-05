#include <iostream>
#include <chrono>
#include "matrix.h"

using namespace std;
using namespace std::chrono;

long long blocking_multiplication(matrix m1, matrix m2, matrix &m3)
{
    const int BLOCK_SIZE = 32;

    auto start = high_resolution_clock::now();

    for (int ii = 0; ii < m1.rows; ii += BLOCK_SIZE)
    {
        for (int jj = 0; jj < m1.cols; jj += BLOCK_SIZE)
        {
            for (int kk = 0; kk < m2.cols; kk += BLOCK_SIZE)
            {
                int i_end = min(ii + BLOCK_SIZE, m1.rows);
                int j_end = min(jj + BLOCK_SIZE, m1.cols);
                int k_end = min(kk + BLOCK_SIZE, m2.cols);

                for (int i = ii; i < i_end; i++)
                {
                    for (int j = jj; j < j_end; j++)
                    {
                        for (int k = kk; k < k_end; k++)
                        {
                            m3.mat[i][k] +=
                                m1.mat[i][j] * m2.mat[j][k];
                        }
                    }
                }
            }
        }
    }

    auto end = high_resolution_clock::now();

    return duration_cast<microseconds>(end - start).count();
}